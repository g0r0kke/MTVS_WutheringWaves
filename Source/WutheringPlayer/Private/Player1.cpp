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
	// 2�� ����
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
	AddControllerPitchInput(LookInput.Y);  // ���� �Է� ����
	AddControllerYawInput(LookInput.X);    // ���� �Է� ����
}

void APlayer1::Move(const struct FInputActionValue& inputValue)
{
	FVector2D value = inputValue.Get<FVector2D>();
	// ���� �Է� �̺�Ʈ ó��
	direction.X = value.X;
	// �¿� �Է� �̺�Ʈ ó��
	direction.Y = value.Y;
}

void APlayer1::InputJump(const struct FInputActionValue& inputValue)
{
	Jump();
}

void APlayer1::InputDash(const struct FInputActionValue& inputValue)
{
	if (inputValue.Get<float>() > 0)  // �뽬 ���� ���� (Ű �Է� ����)
	{
		// �뽬 �Ÿ� �� �ӵ� ����
		const float AvoidDashSpeed = 1200.0f;  // �ӵ��� ����

		// �÷��̾��� ���� ���� ���� ���
		FVector BackwardDirection = -GetActorForwardVector();

		// CharacterMovementComponent�� ����Ͽ� �������� �뽬 ó��
		UCharacterMovementComponent* CharMovement = GetCharacterMovement();
		if (CharMovement)
		{
			CharMovement->BrakingFrictionFactor = 0.f;  // �극��ŷ ���� ����
			LaunchCharacter(BackwardDirection * AvoidDashSpeed, true, true);  // �뽬 ����
			CharMovement->BrakingFrictionFactor = 2.f;  // ������� ����

			// �뽬�� ���� �� ª�� �����̸� �����Ͽ� �ڿ������� �帧 ����
			FTimerHandle UnusedHandle;
			GetWorldTimerManager().SetTimer(UnusedHandle, this, &APlayer1::ResetAvoidDash, 0.5f, false);
		}
	}
}

void APlayer1::PlayerMove()
{
	// �÷��̾� �̵� ó��
	// ��� �
	// P = P0 + vt (��� ��ġ)=(���� ��ġ)+(�ӵ�)*(�ð�)
	// �̵� ���� ��Ʈ�� ���� �������� ��ȯ
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
		CharMovement->StopMovementImmediately();  // ��� ���߱�
		CharMovement->BrakingFrictionFactor = 2.f;  // ���� ����
	}
}