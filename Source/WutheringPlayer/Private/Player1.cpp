#include "Player1.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "InputActionValue.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Engine/Engine.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
APlayer1::APlayer1()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// 초기 체력 설정
	HP = 100;
	bIsAlive = true;
	IsDashing = false;
	IsMoving = false;
	IsJumping = false;
	direction = FVector::ZeroVector;

	bCanAttack = true; // 공격 가능 초기화
	bAerialAttack = false; // 공중 공격 초기화

	AttackStage = 0; // 공격 단계 초기화
	bIsStrongAttack = false; // 강한 공격 초기화

	// 1. SkeletalMesh 로드
	ConstructorHelpers::FObjectFinder<USkeletalMesh> TempMesh(TEXT("/Script/Engine.SkeletalMesh'/Game/Asset/Mixamo/Big_Rib_Hit__.Big_Rib_Hit__'"));

	// 만약 로드가 성공했다면
	if (TempMesh.Succeeded()) {
		// MeshFinder에 로드한 SkeletalMesh 설정
		GetMesh()->SetSkeletalMesh(TempMesh.Object);
		// 2. Mesh 컴포넌트 위치, 회전값 설정
		GetMesh()->SetRelativeLocationAndRotation(FVector(0, 0, -90), FRotator(0, -90, 0));
	}

	// Follow 카메라 붙이기
	// 3-1. SpringArm 컴포넌트 붙이기
	CameraArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraArm->SetupAttachment(RootComponent);
	CameraArm->SetRelativeLocation(FVector(0, 0, 70));
	CameraArm->TargetArmLength = 430;
	CameraArm->bUsePawnControlRotation = true;

	//// 카메라 랙 설정
	//CameraArm->bEnableCameraLag = true;
	//CameraArm->CameraLagSpeed = 10.0f; // 적절한 값으로 설정

	// 3-2. 카메라 컴포넌트 붙이기
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraArm);
	FollowCamera->bUsePawnControlRotation = false;

	// 콤보공격 몽타주 추가
	static ConstructorHelpers::FObjectFinder<UAnimMontage> TempMontage(TEXT("/Script/Engine.AnimMontage'/Game/KHJ/Animations/Montages/AM_ComboAttack.AM_ComboAttack'"));

	// 만약 로드가 성공했다면
	if (TempMontage.Succeeded()) {
		ComboActionMontage = TempMontage.Object;
	}
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

	// 카메라 줌아웃 설정
	InitialArmLength = 300.0f; // 초기 더 줌인된 상태로 설정
	TargetArmLength = 430.0f;  // 원래 설정된 상태로 되돌리기 위한 목표 거리
	ZoomDuration = 2.0f;       // 줌아웃 지속 시간 (2초)
	ElapsedTime = 0.0f;        // 경과 시간 초기화

	CameraArm->TargetArmLength = InitialArmLength;
}

// Called every frame
void APlayer1::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	UpdateCameraZoom(DeltaTime);
}

void APlayer1::UpdateCameraZoom(float DeltaTime)
{
	if (ElapsedTime < ZoomDuration)
	{
		ElapsedTime += DeltaTime;
		float Alpha = FMath::Clamp(ElapsedTime / ZoomDuration, 0.0f, 1.0f);
		CameraArm->TargetArmLength = FMath::Lerp(InitialArmLength, TargetArmLength, Alpha);
	}
	else
	{
		CameraArm->TargetArmLength = TargetArmLength;
	}
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
		PlayerInput->BindAction(inp_Attack, ETriggerEvent::Started, this, &APlayer1::InputAttackStart);
		PlayerInput->BindAction(inp_Attack, ETriggerEvent::Completed, this, &APlayer1::InputAttackStop);
		PlayerInput->BindAction(inp_Skill, ETriggerEvent::Started, this, &APlayer1::InputSkill);
		PlayerInput->BindAction(inp_Move, ETriggerEvent::Completed, this, &APlayer1::MoveComplete);
	}
}

void APlayer1::ProcessComboCommand()
{
	UAnimInstance* animInstance = GetMesh()->GetAnimInstance();
	animInstance->Montage_Play(ComboActionMontage);
}

void APlayer1::Look(const FInputActionValue& InputValue)
{
	FVector2D LookInput = InputValue.Get<FVector2D>();
	AddControllerPitchInput(LookInput.Y); // 수직 입력 적용
	AddControllerYawInput(LookInput.X); // 수평 입력 적용
}

void APlayer1::Move(const struct FInputActionValue& InputValue)
{
	FVector2D value = InputValue.Get<FVector2D>();
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
		UpdateRotation(MoveDirection);  // 이동 방향으로 회전
	}
}

void APlayer1::InputJump(const struct FInputActionValue& InputValue)
{
	Jump();
	UGameplayStatics::PlaySound2D(GetWorld(), JumpSound, 2.0f);
	IsJumping = true;
}


void APlayer1::InputDash(const struct FInputActionValue& InputValue) // 대쉬 실행 조건 (키 입력 감지)
{
	if (InputValue.Get<float>() > 0 && !IsDashing)
	{
		//HideWeapon();

		IsDashing = true;
		float DashSpeed = 2000.0f; // 속도값 조정

		if (IsMoving)
		{
			FVector DashDirection;
			DashDirection = FTransform(GetControlRotation()).TransformVector(direction).GetSafeNormal();
			// 플레이어가 이동 중인 방향으로 대쉬
			PerformDash(DashDirection, DashSpeed); // 로컬 좌표계에서 앞으로 대쉬
			//DisplayMessage("Dash");
			DashStart();
		}
		else
		{
			// 플레이어가 이동 중이 아니면 뒤로 대쉬
			PerformDash(GetActorForwardVector(), -DashSpeed); // 로컬 좌표계에서 뒤로 대쉬
			//DisplayMessage("Avoid");
			JustAvoidStart();
		}

		// Roll 메시지 출력 로직 추가
		if (IsJumping && IsMoving)
		{
			Roll1Start();
			PerformRoll(true); // ROLL1
		}
		else if (IsJumping && !IsMoving)
		{
			Roll2Start();
			PerformRoll(false); // ROLL2resetdash
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
		//CharMovement->StopMovementImmediately(); // 즉시 멈추기
		CharMovement->BrakingFrictionFactor = 2.f; // 마찰 복구
	}
}

void APlayer1::PerformRoll(bool bForward)
{
	//FString RollType = bForward ? TEXT("ROLL1") : TEXT("ROLL2");
	//DisplayMessage(RollType);
}

// 메시지 화면에 출력
void APlayer1::DisplayMessage(FString Message, float Duration)
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, Duration, FColor::Red, Message);
	}
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

// 착지 이벤트 처리
void APlayer1::Landed(const FHitResult& Hit)
{
	Super::Landed(Hit);
	IsJumping = false;

	if (bAerialAttack)
	{
		// 공중 공격 후 착지 시 일정 시간 동안 공격을 비활성화
		bCanAttack = false;
		GetWorldTimerManager().SetTimer(AttackDisableTimer, this, &APlayer1::EnableAttack, 0.2f, false);
		bAerialAttack = false; // 공중 공격 상태 초기화
	}
}

void APlayer1::EnableAttack()
{
	bCanAttack = true;
}

void APlayer1::InputAttackStart(const struct FInputActionValue& InputValue)
{
	if (!bCanAttack) return; // 공격이 비활성화된 경우 반환
	bIsStrongAttack = false;

	if (IsJumping)
	{
		InputAerialAttack();
		return;
	}

	// 1.5초 후에 강한 공격 트리거
	GetWorldTimerManager().SetTimer(StrongAttackTimer, this, &APlayer1::PerformStrongAttack, 1.5f, false);

}

void APlayer1::InputAttackStop(const struct FInputActionValue& InputValue)
{
	if (!bCanAttack || bIsStrongAttack || IsJumping)
	{
		// 강한 공격 또는 공중 공격이면 콤보 공격을 실행하지 않음
		return;
	}

	GetWorldTimerManager().ClearTimer(StrongAttackTimer); // 강한 공격 타이머 중지

	// 콤보 공격 처리
	switch (AttackStage)
	{
	case 0:
		PerformFirstAttack();
		Attack1Start();
		break;
	case 1:
		PerformSecondAttack();
		Attack2Start();
		break;
	case 2:
		PerformThirdAttack();
		Attack3Start();
		break;
	case 3:
		PerformFourthAttack();
		Attack4Start();
		break;
	default:
		ResetCombo();
		PerformFirstAttack();
		Attack1Start();
		break;
	}

	// 다음 단계로 전환
	AttackStage = (AttackStage + 1) % 4;

	// 콤보 타이머 재설정
	GetWorldTimerManager().ClearTimer(AttackComboTimer);
	GetWorldTimerManager().SetTimer(AttackComboTimer, this, &APlayer1::ResetCombo, 0.8f, false);
}

void APlayer1::InputAerialAttack()
{
	//DisplayMessage("Aerial Attack!");
	bAerialAttack = true; // 공중 공격 상태 설정
	const float FastFallSpeed = -1200.0f; // 빠른 낙하 속도 조정
	LaunchCharacter(FVector(0, 0, FastFallSpeed), true, true); // 빠르게 낙하
}

void APlayer1::PerformStrongAttack()
{
	if (bIsAttackHeld) // 공격 버튼이 눌린 상태에서만 강한 공격 실행
	{
		bIsStrongAttack = true;
		//DisplayMessage("Strong Attack!");
	}
}

void APlayer1::ResetCombo()
{
	AttackStage = 0;
}

void APlayer1::InputSkill(const struct FInputActionValue& InputValue)
{
	//DisplayMessage("Skill Attack!");
}

void APlayer1::PerformFirstAttack()
{
	//DisplayMessage("First Attack!");
}

void APlayer1::PerformSecondAttack()
{
	//DisplayMessage("Second Attack!");
}

void APlayer1::PerformThirdAttack()
{
	//DisplayMessage("Third Attack!");
}

void APlayer1::PerformFourthAttack()
{
	//DisplayMessage("Fourth Attack!");
}

void APlayer1::MoveComplete()
{
	IsMoving = false;
}

void APlayer1::PerformDash(const FVector& DashDirection, float DashSpeed)
{
	UCharacterMovementComponent* CharMovement = GetCharacterMovement();
	if (CharMovement)
	{
		CharMovement->BrakingFrictionFactor = 0.f;
		LaunchCharacter(DashDirection * DashSpeed, true, true);
		CharMovement->BrakingFrictionFactor = 2.f;

		FTimerHandle UnusedHandle;
		GetWorldTimerManager().SetTimer(UnusedHandle, this, &APlayer1::ResetDash, 0.5f, false);
	}
}

void APlayer1::OnHitEvent(int32 Damage)
{
	DisplayMessage("Damaged!!!!!");
	HP--;
	if (!bIsAlive)
	{
		return;
	}

	HP -= Damage;

	if (HP <= 0)
	{
		HP = 0;
		Die();
	}
}

void APlayer1::Die()
{
	// 사망 메시지 표시
	DisplayMessage(TEXT("You Died!"), 5.0f);
}

//void APlayer1::HideWeapon()
//{
//    // HideWeapon 함수의 로직을 추가하세요
//    if (P1Weapon)
//    {
//        P1Weapon->MeshComp->SetVisibility(false);
//    }
//    else
//    {
//        UE_LOG(LogTemp, Warning, TEXT("P1Weapon is not set"));
//    } 
//}