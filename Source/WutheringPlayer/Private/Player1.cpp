// Fill out your copyright notice in the Description page of Project Settings.

#include "Player1.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "InputActionValue.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "PlayerMove.h"

// Sets default values
APlayer1::APlayer1()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// 1. SkeletalMesh 로드
	ConstructorHelpers::FObjectFinder<USkeletalMesh> TempMesh(TEXT("/Script/Engine.SkeletalMesh'/Game/KHJ/Characters/Mannequins/Meshes/SKM_Quinn_Simple.SKM_Quinn_Simple'"));

	// 만약 로드가 성공했다면
	if (TempMesh.Succeeded()) {
		// MeshFinder에 로드한 SkeletalMesh 설정
		GetMesh()->SetSkeletalMesh(TempMesh.Object);
		// 2. Mesh 컴포넌트 위치, 회전값 설정
		GetMesh()->SetRelativeLocationAndRotation(FVector(0, 0, -90), FRotator(0, -90, 0));
	}

	// TPS 카메라 붙이기
	// 3-1. SpringArm 컴포넌트 붙이기
	springArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComp"));
	springArmComp->SetupAttachment(RootComponent);
	springArmComp->SetRelativeLocation(FVector(0, 70, 90));
	springArmComp->TargetArmLength = 400;
	springArmComp->bUsePawnControlRotation = true;
	// 3-2. 카메라 컴포넌트 붙이기
	tpsCamComp = CreateDefaultSubobject<UCameraComponent>(TEXT("TpsCamComp"));
	tpsCamComp->SetupAttachment(springArmComp);
	tpsCamComp->bUsePawnControlRotation = false;

	bUseControllerRotationYaw = true;
	IsDashing = false;
	IsMoving = false;

	playerMove = CreateDefaultSubobject<UPlayerMove>(TEXT("PlayerMove"));
}

// Called when the game starts or when spawned
void APlayer1::BeginPlay()
{
	Super::BeginPlay();

	auto pc = Cast<APlayerController>(Controller);
	if (pc)
	{
		auto subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(pc->GetLocalPlayer());
		if (subsystem)
		{
			subsystem->AddMappingContext(imc_Player, 0);
		}
	}
}

// Called every frame
void APlayer1::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void APlayer1::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	auto PlayerInput = CastChecked<UEnhancedInputComponent>(PlayerInputComponent);
	if (PlayerInput)
	{
		// 컴포넌트에서 입력 바인딩 처리하도록 호출
		playerMove->SetupInputBinding(PlayerInput);

		PlayerInput->BindAction(inp_Look, ETriggerEvent::Triggered, this, &APlayer1::Look);
		PlayerInput->BindAction(inp_Move, ETriggerEvent::Triggered, this, &APlayer1::Move);
		PlayerInput->BindAction(inp_Jump, ETriggerEvent::Started, this, &APlayer1::InputJump);
		PlayerInput->BindAction(inp_Dash, ETriggerEvent::Started, this, &APlayer1::InputDash);
	}
}

void APlayer1::Look(const FInputActionValue& inputValue)
{
	FVector2D LookInput = inputValue.Get<FVector2D>();
	AddControllerPitchInput(LookInput.Y);  // 수직 입력 적용
	AddControllerYawInput(LookInput.X);    // 수평 입력 적용
}

void APlayer1::Move(const struct FInputActionValue& inputValue)
{
	FVector2D value = inputValue.Get<FVector2D>();
	// 방향키 입력값을 기반으로 방향 설정
	direction.X = value.X;
	direction.Y = value.Y;

	// 방향키가 눌린 상태면 IsMoving을 true로 설정, 아니면 false로 설정
	IsMoving = !value.IsZero();

	// 플레이어 이동 처리
	if (IsMoving)
	{
		FVector MoveDirection = FTransform(GetControlRotation()).TransformVector(direction);
		AddMovementInput(MoveDirection);
		UpdateRotation(MoveDirection); // 이동 방향으로 회전
	}
}

void APlayer1::InputJump(const struct FInputActionValue& inputValue)
{
	Jump();
	IsJumping = true;
}

void APlayer1::InputDash(const struct FInputActionValue& inputValue)
{
	if (inputValue.Get<float>() > 0 && !IsDashing)  // 대쉬 실행 조건 (키 입력 감지)
	{
		IsDashing = true;
		const float DashSpeed = 1200.0f;  // 속도값 조정
		FVector DashDirection;

		if (IsMoving)
		{
			// 플레이어가 이동 중인 방향으로 대쉬
			DashDirection = direction.GetSafeNormal();
		}
		else
		{
			// 플레이어가 이동 중이 아니면 뒤로 대쉬
			DashDirection = -GetActorForwardVector();
		}

		UCharacterMovementComponent* CharMovement = GetCharacterMovement();
		if (CharMovement)
		{
			CharMovement->BrakingFrictionFactor = 0.f;  // 브레이킹 마찰 감소
			LaunchCharacter(DashDirection * DashSpeed, true, true);  // 대쉬 실행
			CharMovement->BrakingFrictionFactor = 2.f;  // 원래대로 복구

			FTimerHandle UnusedHandle;
			GetWorldTimerManager().SetTimer(UnusedHandle, this, &APlayer1::ResetDash, 0.5f, false);
		}
	}

	// 대쉬 후에 IsMoving 초기화
	IsMoving = false;
	direction = FVector::ZeroVector;
}

void APlayer1::ResetDash()
{
	IsDashing = false;
	UCharacterMovementComponent* CharMovement = GetCharacterMovement();
	if (CharMovement)
	{
		CharMovement->StopMovementImmediately();  // 즉시 멈추기
		CharMovement->BrakingFrictionFactor = 2.f;  // 마찰 복구
	}
}

void APlayer1::PerformRoll(bool bForward)
{
	FString RollType = bForward ? TEXT("ROLL1") : TEXT("ROLL2");
	DisplayRollMessage(RollType);
}

void APlayer1::DisplayRollMessage(FString Message)
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 0.5f, FColor::Red, Message);
	}
}

// 착지 이벤트 처리
void APlayer1::Landed(const FHitResult& Hit)
{
	Super::Landed(Hit);
	IsJumping = false;
}

// UpdateRotation 함수 구현
void APlayer1::UpdateRotation(const FVector& MoveDirection)
{
	if (!MoveDirection.IsNearlyZero())
	{
		FRotator NewRotation = MoveDirection.Rotation();
		NewRotation.Pitch = 0.0f; // 피치 값은 유지
		NewRotation.Roll = 0.0f;  // 롤 값은 유지
		SetActorRotation(NewRotation);
	}
}