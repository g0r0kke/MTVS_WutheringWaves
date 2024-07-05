#include "Player1.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "InputActionValue.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Engine/Engine.h"
//#include "GameFramework/GameModeBase.h"
//#include "Kismet/GameplayStatics.h"

// Sets default values
APlayer1::APlayer1()
{
    // Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;

    // 초기 체력 설정
    Health = 100;
    bIsAlive = true;

    // 1. SkeletalMesh 로드
    ConstructorHelpers::FObjectFinder<USkeletalMesh> TempMesh(TEXT("/Script/Engine.SkeletalMesh'/Game/Asset/Mixamo/Big_Rib_Hit__.Big_Rib_Hit__'"));

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

    IsDashing = false;
    IsMoving = false;
    bCanAttack = true; // 공격 가능 초기화
    bAerialAttack = false; // 공중 공격 초기화

    AttackStage = 0; // 공격 단계 초기화
    bIsStrongAttack = false; // 강한 공격 초기화
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

        PlayerInput->BindAction(inp_Look, ETriggerEvent::Triggered, this, &APlayer1::Look);
        PlayerInput->BindAction(inp_Move, ETriggerEvent::Triggered, this, &APlayer1::Move);
        PlayerInput->BindAction(inp_Jump, ETriggerEvent::Started, this, &APlayer1::InputJump);
        PlayerInput->BindAction(inp_Dash, ETriggerEvent::Started, this, &APlayer1::InputDash);
        PlayerInput->BindAction(inp_Attack, ETriggerEvent::Started, this, &APlayer1::InputAttackStart);
        PlayerInput->BindAction(inp_Attack, ETriggerEvent::Completed, this, &APlayer1::InputAttackStop);
        PlayerInput->BindAction(inp_Skill, ETriggerEvent::Started, this, &APlayer1::InputSkill);
    }
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
    IsJumping = true;
}

void APlayer1::InputDash(const struct FInputActionValue& InputValue) // 대쉬 실행 조건 (키 입력 감지)
{
    if (InputValue.Get<float>() > 0 && !IsDashing)
    {
        IsDashing = true;
        float DashSpeed = 1200.0f; // 속도값 조정
        if (IsMoving)
        {
            FVector DashDirection;
            DashDirection = FTransform(GetControlRotation()).TransformVector(direction).GetSafeNormal();
            // 플레이어가 이동 중인 방향으로 대쉬
            PerformDash(DashDirection, DashSpeed); // 로컬 좌표계에서 앞으로 대쉬
        }
        else
        {
            // 플레이어가 이동 중이 아니면 뒤로 대쉬
            PerformDash(GetActorForwardVector(), -DashSpeed); // 로컬 좌표계에서 뒤로 대쉬
        }

        // Roll 메시지 출력 로직 추가
        if (IsJumping && IsMoving)
        {
            PerformRoll(true); // ROLL1
        }
        else if (IsJumping)
        {
            PerformRoll(false); // ROLL2
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
        CharMovement->StopMovementImmediately(); // 즉시 멈추기
        CharMovement->BrakingFrictionFactor = 2.f; // 마찰 복구
    }
}

void APlayer1::PerformRoll(bool bForward)
{
    FString RollType = bForward ? TEXT("ROLL1") : TEXT("ROLL2");
    DisplayMessage(RollType);
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
    DisplayMessage("Aerial Attack!");
    bAerialAttack = true; // 공중 공격 상태 설정
    const float FastFallSpeed = -1200.0f; // 빠른 낙하 속도 조정
    LaunchCharacter(FVector(0, 0, FastFallSpeed), true, true); // 빠르게 낙하
}

void APlayer1::PerformStrongAttack()
{
    if (bIsAttackHeld) // 공격 버튼이 눌린 상태에서만 강한 공격 실행
    {
        bIsStrongAttack = true;
        DisplayMessage("Strong Attack!");
    }
}

void APlayer1::ResetCombo()
{
    AttackStage = 0;
}

void APlayer1::InputSkill(const struct FInputActionValue& InputValue)
{
    DisplayMessage("Skill Attack!");
    //PerformDash(GetActorForwardVector(), 1200.0f);
}

void APlayer1::PerformFirstAttack()
{
    DisplayMessage("First Attack!");
    //PerformDash(GetActorForwardVector(), 1100.0f);
}

void APlayer1::PerformSecondAttack()
{
    DisplayMessage("Second Attack!");
    //PerformDash(GetActorForwardVector(), 1200.0f);
}

void APlayer1::PerformThirdAttack()
{
    DisplayMessage("Third Attack!");
    //PerformDash(GetActorForwardVector(), 1300.0f);
}

void APlayer1::PerformFourthAttack()
{
    DisplayMessage("Fourth Attack!");
    //PerformDash(GetActorForwardVector(), 1400.0f);
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

void APlayer1::DecreaseHealth(int32 Damage)
{
    if (!bIsAlive)
    {
        return;
    }

    Health -= Damage;

    if (Health <= 0)
    {
        Die();
    }
}

void APlayer1::Die()
{
    // 사망 메시지 표시
    DisplayMessage(TEXT("You Died!"), 5.0f);
}

