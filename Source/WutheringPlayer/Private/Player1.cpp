#include "Player1.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "InputActionValue.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Engine/Engine.h"
#include "GameFramework/GameModeBase.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
APlayer1::APlayer1()
{
    // Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;

    // 1. SkeletalMesh �ε�
    ConstructorHelpers::FObjectFinder<USkeletalMesh> TempMesh(TEXT("/Script/Engine.SkeletalMesh'/Game/Asset/Mixamo/Big_Rib_Hit__.Big_Rib_Hit__'"));

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
    bCanAttack = true; // ���� ���� �ʱ�ȭ
    bAerialAttack = false; // ���� ���� �ʱ�ȭ

    AttackStage = 0; // ���� �ܰ� �ʱ�ȭ
    bIsStrongAttack = false; // ���� ���� �ʱ�ȭ

    // ĳ���� �������Ʈ Ŭ���� �ε�
    ConstructorHelpers::FClassFinder<APawn> Player1BP(TEXT("/Game/KHJ/Blueprints/BP_P1.BP_P1_C"));
    if (Player1BP.Succeeded())
    {
        BP_Player1 = Player1BP.Class;
        GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("BP_Player1 loaded successfully"));
    }
    else
    {
        BP_Player1 = nullptr;
        GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Failed to load BP_Player1"));
    }

    ConstructorHelpers::FClassFinder<APawn> Player2BP(TEXT("/Game/KHJ/Blueprints/BP_P2.BP_P2_C"));
    if (Player2BP.Succeeded())
    {
        BP_Player2 = Player2BP.Class;
        GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("BP_Player2 loaded successfully"));
    }
    else
    {
        BP_Player2 = nullptr;
        GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Failed to load BP_Player2"));
    }

    CurrentPlayerInstance = this; // ���� �÷��̾� �ν��Ͻ� �ʱ�ȭ
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

        // ĳ���� ��ȯ ���ε�
        PlayerInput->BindAction(inp_SwitchTo1, ETriggerEvent::Started, this, &APlayer1::SwitchToCharacter, 1);
        PlayerInput->BindAction(inp_SwitchTo2, ETriggerEvent::Started, this, &APlayer1::SwitchToCharacter, 2);
    }
}

void APlayer1::Look(const FInputActionValue& inputValue)
{
    FVector2D LookInput = inputValue.Get<FVector2D>();
    AddControllerPitchInput(LookInput.Y); // ���� �Է� ����
    AddControllerYawInput(LookInput.X); // ���� �Է� ����
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
        UpdateRotation(MoveDirection);  // �̵� �������� ȸ��
    }
}

void APlayer1::InputJump(const struct FInputActionValue& inputValue)
{
    Jump();
    IsJumping = true;
}

void APlayer1::InputDash(const struct FInputActionValue& inputValue) // �뽬 ���� ���� (Ű �Է� ����)
{
    if (inputValue.Get<float>() > 0 && !IsDashing)
    {
        IsDashing = true;
        float DashSpeed = 1200.0f; // �ӵ��� ����
        if (IsMoving)
        {
            FVector DashDirection;
            DashDirection = FTransform(GetControlRotation()).TransformVector(direction).GetSafeNormal();
            // �÷��̾ �̵� ���� �������� �뽬
            PerformDash(DashDirection, DashSpeed); // ���� ��ǥ�迡�� ������ �뽬
        }
        else
        {
            // �÷��̾ �̵� ���� �ƴϸ� �ڷ� �뽬
            PerformDash(GetActorForwardVector(), -DashSpeed); // ���� ��ǥ�迡�� �ڷ� �뽬
        }

        // Roll �޽��� ��� ���� �߰�
        if (IsJumping && IsMoving)
        {
            PerformRoll(true); // ROLL1
        }
        else if (IsJumping)
        {
            PerformRoll(false); // ROLL2
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
        CharMovement->StopMovementImmediately(); // ��� ���߱�
        CharMovement->BrakingFrictionFactor = 2.f; // ���� ����
    }
}

void APlayer1::PerformRoll(bool bForward)
{
    FString RollType = bForward ? TEXT("ROLL1") : TEXT("ROLL2");
    DisplayMessage(RollType);
}

// �޽��� ȭ�鿡 ���
void APlayer1::DisplayMessage(FString Message, float Duration)
{
    if (GEngine)
    {
        GEngine->AddOnScreenDebugMessage(-1, Duration, FColor::Red, Message);
    }
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

// ���� �̺�Ʈ ó��
void APlayer1::Landed(const FHitResult& Hit)
{
    Super::Landed(Hit);
    IsJumping = false;

    if (bAerialAttack)
    {
        // ���� ���� �� ���� �� ���� �ð� ���� ������ ��Ȱ��ȭ
        bCanAttack = false;
        GetWorldTimerManager().SetTimer(AttackDisableTimer, this, &APlayer1::EnableAttack, 0.2f, false);
        bAerialAttack = false; // ���� ���� ���� �ʱ�ȭ
    }
}

void APlayer1::EnableAttack()
{
    bCanAttack = true;
}

void APlayer1::InputAttackStart(const struct FInputActionValue& inputValue)
{
    if (!bCanAttack) return; // ������ ��Ȱ��ȭ�� ��� ��ȯ
    bIsStrongAttack = false;

    if (IsJumping)
    {
        InputAerialAttack();
        return;
    }

    // 1.5�� �Ŀ� ���� ���� Ʈ����
    GetWorldTimerManager().SetTimer(StrongAttackTimer, this, &APlayer1::PerformStrongAttack, 1.5f, false);
}

void APlayer1::InputAttackStop(const struct FInputActionValue& inputValue)
{
    if (!bCanAttack || bIsStrongAttack || IsJumping)
    {
        // ���� ���� �Ǵ� ���� �����̸� �޺� ������ �������� ����
        return;
    }

    GetWorldTimerManager().ClearTimer(StrongAttackTimer); // ���� ���� Ÿ�̸� ����

    // �޺� ���� ó��
    switch (AttackStage)
    {
    case 0:
        PerformFirstAttack();
        break;
    case 1:
        PerformSecondAttack();
        break;
    case 2:
        PerformThirdAttack();
        break;
    case 3:
        PerformFourthAttack();
        break;
    default:
        ResetCombo();
        PerformFirstAttack();
        break;
    }

    // ���� �ܰ�� ��ȯ
    AttackStage = (AttackStage + 1) % 4;

    // �޺� Ÿ�̸� �缳��
    GetWorldTimerManager().ClearTimer(AttackComboTimer);
    GetWorldTimerManager().SetTimer(AttackComboTimer, this, &APlayer1::ResetCombo, 0.5f, false);
}

void APlayer1::InputAerialAttack()
{
    DisplayMessage("Aerial Attack!");
    bAerialAttack = true; // ���� ���� ���� ����
    const float FastFallSpeed = -1200.0f; // ���� ���� �ӵ� ����
    LaunchCharacter(FVector(0, 0, FastFallSpeed), true, true); // ������ ����
}

void APlayer1::PerformStrongAttack()
{
    bIsStrongAttack = true;
    DisplayMessage("Strong Attack!");
}

void APlayer1::ResetCombo()
{
    AttackStage = 0;
}

void APlayer1::InputSkill(const struct FInputActionValue& inputValue)
{
    DisplayMessage("Skill Attack!");
    PerformDash(GetActorForwardVector(), 1200.0f);
}

void APlayer1::PerformFirstAttack()
{
    DisplayMessage("First Attack!");
    PerformDash(GetActorForwardVector(), 1100.0f);
}

void APlayer1::PerformSecondAttack()
{
    DisplayMessage("Second Attack!");
    PerformDash(GetActorForwardVector(), 1200.0f);
}

void APlayer1::PerformThirdAttack()
{
    DisplayMessage("Third Attack!");
    PerformDash(GetActorForwardVector(), 1300.0f);
}

void APlayer1::PerformFourthAttack()
{
    DisplayMessage("Fourth Attack!");
    PerformDash(GetActorForwardVector(), 1400.0f);
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

//// ĳ���� ��ȯ �Լ� ����
//void APlayer1::SwitchToCharacter(int32 CharacterIndex)
//{
//    auto pc = Cast<APlayerController>(Controller);
//    if (pc)
//    {
//        TSubclassOf<APawn> NewCharacterClass = (CharacterIndex == 1) ? BP_Player1 : BP_Player2;
//        if (NewCharacterClass && GetClass() != NewCharacterClass)
//        {
//            FTransform SpawnTransform = GetActorTransform();
//            APawn* NewCharacter = GetWorld()->SpawnActor<APawn>(NewCharacterClass, SpawnTransform);
//            if (NewCharacter)
//            {
//                pc->UnPossess();
//                pc->Possess(NewCharacter);
//                Destroy(); // ���� ĳ���� ����
//            }
//        }
//    }
//}

void APlayer1::SwitchToCharacter(int32 CharacterIndex)
{
    auto pc = Cast<APlayerController>(Controller);
    if (pc)
    {
        TSubclassOf<APawn> NewCharacterClass = nullptr;
        if (CharacterIndex == 1)
        {
            NewCharacterClass = BP_Player1;
            GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("Switching to Player 1"));
        }
        else if (CharacterIndex == 2)
        {
            NewCharacterClass = BP_Player2;
            GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Switching to Player 2"));
        }

        if (!NewCharacterClass)
        {
            GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("NewCharacterClass is invalid"));
            return;
        }

        if (CurrentPlayerInstance && CurrentPlayerInstance->GetClass() == NewCharacterClass)
        {
            GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("NewCharacterClass is the same as the current class"));
            return;
        }

        FVector SpawnLocation = GetActorLocation() + FVector(100, -100, 0);
        FRotator SpawnRotation = GetActorRotation();
        FActorSpawnParameters SpawnParams;
        SpawnParams.Owner = this;
        APawn* NewCharacter = GetWorld()->SpawnActor<APawn>(NewCharacterClass, SpawnLocation, SpawnRotation, SpawnParams);
        if (NewCharacter)
        {
            GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Spawned new character successfully"));
            pc->UnPossess();
            pc->Possess(NewCharacter);
            CurrentPlayerInstance = NewCharacter;

            // ���� ĳ���� ��Ȱ��ȭ
            SetActorHiddenInGame(true);
            SetActorEnableCollision(false);
            SetActorTickEnabled(false);
        }
        else
        {
            GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Failed to spawn new character"));
        }
    }
}