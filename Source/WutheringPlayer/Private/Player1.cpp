// Fill out your copyright notice in the Description page of Project Settings.


#include "Player1.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "InputActionValue.h"
#include "GameFramework/CharacterMovementComponent.h"

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
	// 2단 점프
	JumpMaxCount = 2;
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

	PlayerMove();
}

// Called to bind functionality to input
void APlayer1::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	auto PlayerInput = CastChecked<UEnhancedInputComponent>(PlayerInputComponent);
	if (PlayerInput)
	{
		PlayerInput->BindAction(inp_Look, ETriggerEvent::Triggered, this, &APlayer1::Look);
		PlayerInput->BindAction(inp_Move, ETriggerEvent::Triggered, this, &APlayer1::Move);
		PlayerInput->BindAction(inp_Jump, ETriggerEvent::Started, this, &APlayer1::InputJump);
		PlayerInput->BindAction(inp_Dash, ETriggerEvent::Started, this, &APlayer1::InputDash);

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
	// 상하 입력 이벤트 처리
	direction.X = value.X;
	// 좌우 입력 이벤트 처리
	direction.Y = value.Y;
}

void APlayer1::InputJump(const struct FInputActionValue& inputValue)
{
	Jump();
}

void APlayer1::InputDash(const struct FInputActionValue& inputValue)
{
	if (inputValue.Get<float>() > 0)  // 대쉬 실행 조건 (키 입력 감지)
	{
		// 대쉬 거리 및 속도 설정
		const float AvoidDashSpeed = 1200.0f;  // 속도값 조정

		// 플레이어의 뒤쪽 방향 벡터 계산
		FVector BackwardDirection = -GetActorForwardVector();

		// CharacterMovementComponent를 사용하여 물리적인 대쉬 처리
		UCharacterMovementComponent* CharMovement = GetCharacterMovement();
		if (CharMovement)
		{
			CharMovement->BrakingFrictionFactor = 0.f;  // 브레이킹 마찰 감소
			LaunchCharacter(BackwardDirection * AvoidDashSpeed, true, true);  // 대쉬 실행
			CharMovement->BrakingFrictionFactor = 2.f;  // 원래대로 복구

			// 대쉬가 끝난 후 짧은 딜레이를 설정하여 자연스러운 흐름 유지
			FTimerHandle UnusedHandle;
			GetWorldTimerManager().SetTimer(UnusedHandle, this, &APlayer1::ResetAvoidDash, 0.5f, false);
		}
	}
}

void APlayer1::PlayerMove()
{
	// 플레이어 이동 처리
	// 등속 운동
	// P = P0 + vt (결과 위치)=(현재 위치)+(속도)*(시간)
	// 이동 방향 컨트롤 방향 기준으로 변환
	direction = FTransform(GetControlRotation()).TransformVector(direction);
	AddMovementInput(direction);
	//FVector P0 = GetActorLocation();
	//FVector vt = direction * walkSpeed * DeltaTime;
	//FVector P = P0 + vt;
	//SetActorLocation(P);
	direction = FVector::ZeroVector;
}

void APlayer1::ResetDash()
{
	UCharacterMovementComponent* CharMovement = GetCharacterMovement();
	if (CharMovement)
	{
		CharMovement->StopMovementImmediately();  // 즉시 멈추기
		CharMovement->BrakingFrictionFactor = 2.f;  // 마찰 복구
	}
}