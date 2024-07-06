#include "SecondCharacter.h"
#include "Player2WeaponL.h"
#include "EnhancedInputComponent.h"
#include "DrawDebugHelpers.h"
#include "TimerManager.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
ASecondCharacter::ASecondCharacter()
{
    PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ASecondCharacter::BeginPlay()
{
    Super::BeginPlay();

    // Set up left gun mesh component
    LeftGunMeshComp = GetWorld()->SpawnActor<APlayer2WeaponL>(FVector::ZeroVector, FRotator::ZeroRotator);
    if (LeftGunMeshComp)
    {
        LeftGunMeshComp->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, TEXT("LeftHandSocket"));
    }

    // Set up right gun mesh component
    RightGunMeshComp = GetWorld()->SpawnActor<APlayer2WeaponL>(FVector::ZeroVector, FRotator::ZeroRotator);
    if (RightGunMeshComp)
    {
        RightGunMeshComp->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, TEXT("RightHandSocket"));
    }
}

// Called every frame
void ASecondCharacter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ASecondCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    UEnhancedInputComponent* PlayerInput = CastChecked<UEnhancedInputComponent>(PlayerInputComponent);
    if (PlayerInput)
    {
        // Bind skill input actions
        PlayerInput->BindAction(inp_Skill, ETriggerEvent::Started, this, &ASecondCharacter::InputSkill);
        PlayerInput->BindAction(inp_Skill, ETriggerEvent::Completed, this, &ASecondCharacter::StopSkill);
    }
}

// Perform combo attacks
void ASecondCharacter::PerformFirstAttack()
{
    DisplayMessage("P2 First Attack!");
    LineTraceShoot(LeftGunMeshComp->GetMeshComponent()); // ¼öÁ¤µÊ
}

void ASecondCharacter::PerformSecondAttack()
{
    DisplayMessage("P2 Second Attack!");
    LineTraceShoot(RightGunMeshComp->GetMeshComponent()); // ¼öÁ¤µÊ
}

void ASecondCharacter::PerformThirdAttack()
{
    DisplayMessage("P2 Third Attack!");
    LineTraceShoot(LeftGunMeshComp->GetMeshComponent()); // ¼öÁ¤µÊ
    LineTraceShoot(RightGunMeshComp->GetMeshComponent()); // ¼öÁ¤µÊ
}

void ASecondCharacter::PerformFourthAttack()
{
    DisplayMessage("P2 Fourth Attack!");
    LineTraceShoot(LeftGunMeshComp->GetMeshComponent(), 2.0f); // Strong attack // ¼öÁ¤µÊ
    LineTraceShoot(RightGunMeshComp->GetMeshComponent(), 2.0f); // Strong attack // ¼öÁ¤µÊ
}

// Skill attack methods
void ASecondCharacter::InputSkill(const FInputActionValue& inputValue)
{
    DisplayMessage("P2 Skill Attack!");
    GetWorld()->GetTimerManager().SetTimer(AutoFireTimerHandle, this, &ASecondCharacter::AutoFire, 0.1f, true);
    PerformDash(GetActorForwardVector(), -3000.0f);
}

void ASecondCharacter::StopSkill(const FInputActionValue& inputValue)
{
    DisplayMessage("P2 Stop Skill!");
    GetWorld()->GetTimerManager().ClearTimer(AutoFireTimerHandle);
}

void ASecondCharacter::AutoFire()
{
    LineTraceShoot(LeftGunMeshComp->GetMeshComponent()); // ¼öÁ¤µÊ
    LineTraceShoot(RightGunMeshComp->GetMeshComponent()); // ¼öÁ¤µÊ
}

// Line trace shooting method
void ASecondCharacter::LineTraceShoot(USceneComponent* GunMeshComponent, float Strength)
{
    FVector Start = GunMeshComponent->GetComponentLocation(); // Start point: gun mesh location
    FVector ForwardVector = GetActorForwardVector(); // Character's forward vector
    FVector End = ((ForwardVector * 5000.f * Strength) + Start); // End point: 5000 units forward * strength
    FHitResult HitResult;
    FCollisionQueryParams CollisionParams;

    bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_Visibility, CollisionParams); // Execute line trace

    if (bHit)
    {
        if (HitResult.GetActor())
        {
            UE_LOG(LogTemp, Warning, TEXT("Hit Actor: %s"), *HitResult.GetActor()->GetName()); // Print hit actor name
        }
    }

    // Draw debug line (can be removed if not needed)
    DrawDebugLine(GetWorld(), Start, End, FColor::Green, false, 1, 0, 1);
}
