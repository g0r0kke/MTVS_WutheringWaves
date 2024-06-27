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

	// 1. SkeletalMesh �ε�
	ConstructorHelpers::FObjectFinder<USkeletalMesh> TempMesh(TEXT("/Script/Engine.SkeletalMesh'/Game/KHJ/Characters/Mannequins/Meshes/SKM_Quinn_Simple.SKM_Quinn_Simple'"));

	// ���� �ε尡 �����ߴٸ�
	if (TempMesh.Succeeded()) {
		// MeshFinder�� �ε��� SkeletalMesh ����
		GetMesh()->SetSkeletalMesh(TempMesh.Object);
		// 2. Mesh ������Ʈ ��ġ, ȸ���� ����
		GetMesh()->SetRelativeLocationAndRotation(FVector(0, 0, -90), FRotator(0, -90, 0));
	}

	// TPS ī�޶� ���̱�
	// 3-1. SpringArm ������Ʈ ���̱�
	springArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComp"));
	springArmComp->SetupAttachment(RootComponent);
	springArmComp->SetRelativeLocation(FVector(0, 70, 90));
	springArmComp->TargetArmLength = 400;
	springArmComp->bUsePawnControlRotation = true;
	// 3-2. ī�޶� ������Ʈ ���̱�
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
		// ������Ʈ���� �Է� ���ε� ó���ϵ��� ȣ��
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
	AddControllerPitchInput(LookInput.Y);  // ���� �Է� ����
	AddControllerYawInput(LookInput.X);    // ���� �Է� ����
}

void APlayer1::Move(const struct FInputActionValue& inputValue)
{
	FVector2D value = inputValue.Get<FVector2D>();
	// ����Ű �Է°��� ������� ���� ����
	direction.X = value.X;
	direction.Y = value.Y;

	// ����Ű�� ���� ���¸� IsMoving�� true�� ����, �ƴϸ� false�� ����
	IsMoving = !value.IsZero();

	// �÷��̾� �̵� ó��
	if (IsMoving)
	{
		FVector MoveDirection = FTransform(GetControlRotation()).TransformVector(direction);
		AddMovementInput(MoveDirection);
		UpdateRotation(MoveDirection); // �̵� �������� ȸ��
	}
}

void APlayer1::InputJump(const struct FInputActionValue& inputValue)
{
	Jump();
	IsJumping = true;
}

void APlayer1::InputDash(const struct FInputActionValue& inputValue)
{
	if (inputValue.Get<float>() > 0 && !IsDashing)  // �뽬 ���� ���� (Ű �Է� ����)
	{
		IsDashing = true;
		const float DashSpeed = 1200.0f;  // �ӵ��� ����
		FVector DashDirection;

		if (IsMoving)
		{
			// �÷��̾ �̵� ���� �������� �뽬
			DashDirection = direction.GetSafeNormal();
		}
		else
		{
			// �÷��̾ �̵� ���� �ƴϸ� �ڷ� �뽬
			DashDirection = -GetActorForwardVector();
		}

		UCharacterMovementComponent* CharMovement = GetCharacterMovement();
		if (CharMovement)
		{
			CharMovement->BrakingFrictionFactor = 0.f;  // �극��ŷ ���� ����
			LaunchCharacter(DashDirection * DashSpeed, true, true);  // �뽬 ����
			CharMovement->BrakingFrictionFactor = 2.f;  // ������� ����

			FTimerHandle UnusedHandle;
			GetWorldTimerManager().SetTimer(UnusedHandle, this, &APlayer1::ResetDash, 0.5f, false);
		}
	}

	// �뽬 �Ŀ� IsMoving �ʱ�ȭ
	IsMoving = false;
	direction = FVector::ZeroVector;
}

void APlayer1::ResetDash()
{
	IsDashing = false;
	UCharacterMovementComponent* CharMovement = GetCharacterMovement();
	if (CharMovement)
	{
		CharMovement->StopMovementImmediately();  // ��� ���߱�
		CharMovement->BrakingFrictionFactor = 2.f;  // ���� ����
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

// ���� �̺�Ʈ ó��
void APlayer1::Landed(const FHitResult& Hit)
{
	Super::Landed(Hit);
	IsJumping = false;
}

// UpdateRotation �Լ� ����
void APlayer1::UpdateRotation(const FVector& MoveDirection)
{
	if (!MoveDirection.IsNearlyZero())
	{
		FRotator NewRotation = MoveDirection.Rotation();
		NewRotation.Pitch = 0.0f; // ��ġ ���� ����
		NewRotation.Roll = 0.0f;  // �� ���� ����
		SetActorRotation(NewRotation);
	}
}