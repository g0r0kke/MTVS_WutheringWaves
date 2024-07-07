#include "SecondCharacter.h"
#include "Player2WeaponL.h"
#include "Player2WeaponR.h"
#include "EnhancedInputComponent.h"
#include "DrawDebugHelpers.h"
#include "TimerManager.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
ASecondCharacter::ASecondCharacter()
{
    PrimaryActorTick.bCanEverTick = true;
    P2WeaponL = nullptr; // 초기화
    P2WeaponR = nullptr; // 초기화
}

// Called when the game starts or when spawned
void ASecondCharacter::BeginPlay()
{
    Super::BeginPlay();

    // Set up left gun mesh component
    P2WeaponL = GetWorld()->SpawnActor<APlayer2WeaponL>(FVector::ZeroVector, FRotator::ZeroRotator);
    if (P2WeaponL)
    {
        P2WeaponL->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, TEXT("LeftHandSocket"));
    }

    // Set up right gun mesh component
    P2WeaponR = GetWorld()->SpawnActor<APlayer2WeaponR>(FVector::ZeroVector, FRotator::ZeroRotator);
    if (P2WeaponR)
    {
        P2WeaponR->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, TEXT("RightHandSocket"));
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
    if (P2WeaponL && P2WeaponL->GetMeshComponent()) // 널 체크 추가
    {
        LineTraceShoot(P2WeaponL->GetMeshComponent());
    }
}

void ASecondCharacter::PerformSecondAttack()
{
    DisplayMessage("P2 Second Attack!");
    if (P2WeaponR && P2WeaponR->GetMeshComponent()) // 널 체크 추가
    {
        LineTraceShoot(P2WeaponR->GetMeshComponent());
    }
}

void ASecondCharacter::PerformThirdAttack()
{
    DisplayMessage("P2 Third Attack!");
    if (P2WeaponL && P2WeaponL->GetMeshComponent()) // 널 체크 추가
    {
        LineTraceShoot(P2WeaponL->GetMeshComponent());
    }
    if (P2WeaponR && P2WeaponR->GetMeshComponent()) // 널 체크 추가
    {
        LineTraceShoot(P2WeaponR->GetMeshComponent());
    }
}

void ASecondCharacter::PerformFourthAttack()
{
    DisplayMessage("P2 Fourth Attack!");
    if (P2WeaponL && P2WeaponL->GetMeshComponent()) // 널 체크 추가
    {
        LineTraceShoot(P2WeaponL->GetMeshComponent(), 2.0f); // Strong attack
    }
    if (P2WeaponR && P2WeaponR->GetMeshComponent()) // 널 체크 추가
    {
        LineTraceShoot(P2WeaponR->GetMeshComponent(), 2.0f); // Strong attack
    }
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
    if (P2WeaponL && P2WeaponL->GetMeshComponent()) // 널 체크 추가
    {
        LineTraceShoot(P2WeaponL->GetMeshComponent());
    }
    if (P2WeaponR && P2WeaponR->GetMeshComponent()) // 널 체크 추가
    {
        LineTraceShoot(P2WeaponR->GetMeshComponent());
    }
}

// Line trace shooting method
void ASecondCharacter::LineTraceShoot(USceneComponent* GunMeshComponent, float Strength)
{
    if (!GunMeshComponent)
    {
        UE_LOG(LogTemp, Warning, TEXT("GunMeshComponent is null"));
        return;
    }

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
