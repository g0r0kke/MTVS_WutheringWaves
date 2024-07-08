#include "SecondCharacter.h"
#include "Player2WeaponL.h"
#include "Player2WeaponR.h"
#include "EnhancedInputComponent.h"
#include "DrawDebugHelpers.h"
#include "TimerManager.h"
#include "Components/SkeletalMeshComponent.h" // ½ºÄÌ·¹Åæ ¸Þ½¬ ÄÄÆ÷³ÍÆ®
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystem.h"
#include "Bullet.h"

// Sets default values
ASecondCharacter::ASecondCharacter()
{
    PrimaryActorTick.bCanEverTick = true;
    P2WeaponL = nullptr; // ÃÊ±âÈ­
    P2WeaponR = nullptr; // ÃÊ±âÈ­
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

    if (P2WeaponL && P2WeaponL->GetMeshComponent())
    {
        USkeletalMeshComponent* MeshCompL = P2WeaponL->GetMeshComponent();
        FTransform FirePosition = MeshCompL->GetSocketTransform(TEXT("fireposition"));
		GetWorld()->SpawnActor<ABullet>(*bulletFactory, FirePosition);
        
        LineTraceShoot(MeshCompL,TEXT("fireposition"));
    }
}

void ASecondCharacter::PerformSecondAttack()
{
    DisplayMessage("P2 Second Attack!");
    if (P2WeaponR && P2WeaponR->GetMeshComponent())
    {
        USkeletalMeshComponent* MeshCompR = P2WeaponR->GetMeshComponent();
        FTransform FirePosition = MeshCompR->GetSocketTransform(TEXT("fireposition"));


        GetWorld()->SpawnActor<ABullet>(*bulletFactory, FirePosition);

        LineTraceShoot(MeshCompR, TEXT("fireposition"));
    }

}

void ASecondCharacter::PerformThirdAttack()
{
    DisplayMessage("P2 Third Attack!");

    if (P2WeaponL && P2WeaponL->GetMeshComponent())
    {
        USkeletalMeshComponent* MeshCompL = P2WeaponL->GetMeshComponent();
        FTransform FirePosition = MeshCompL->GetSocketTransform(TEXT("fireposition"));


        GetWorld()->SpawnActor<ABullet>(*bulletFactory, FirePosition);

        LineTraceShoot(MeshCompL, TEXT("fireposition"));
    }


    if (P2WeaponR && P2WeaponR->GetMeshComponent())
    {
        USkeletalMeshComponent* MeshCompR = P2WeaponR->GetMeshComponent();
        FTransform FirePosition = MeshCompR->GetSocketTransform(TEXT("fireposition"));


        GetWorld()->SpawnActor<ABullet>(*bulletFactory, FirePosition);

        LineTraceShoot(MeshCompR, TEXT("fireposition"));
    }

}

void ASecondCharacter::PerformFourthAttack()
{
    DisplayMessage("P2 Fourth Attack!");

    if (P2WeaponL && P2WeaponL->GetMeshComponent())
    {
        USkeletalMeshComponent* MeshCompL = P2WeaponL->GetMeshComponent();
        FTransform FirePosition = MeshCompL->GetSocketTransform(TEXT("fireposition"));


        GetWorld()->SpawnActor<ABullet>(*bulletFactory, FirePosition);

        LineTraceShoot(MeshCompL, TEXT("fireposition"));
    }


    if (P2WeaponR && P2WeaponR->GetMeshComponent())
    {
        USkeletalMeshComponent* MeshCompR = P2WeaponR->GetMeshComponent();
        FTransform FirePosition = MeshCompR->GetSocketTransform(TEXT("fireposition"));


        GetWorld()->SpawnActor<ABullet>(*bulletFactory, FirePosition);

        LineTraceShoot(MeshCompR, TEXT("fireposition"));
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
    if (P2WeaponL && P2WeaponL->GetMeshComponent())
    {
        USkeletalMeshComponent* MeshCompL = P2WeaponL->GetMeshComponent();
        FTransform FirePosition = MeshCompL->GetSocketTransform(TEXT("fireposition"));


        GetWorld()->SpawnActor<ABullet>(*bulletFactory, FirePosition);

        LineTraceShoot(MeshCompL, TEXT("fireposition"));
    }

    if (P2WeaponR && P2WeaponR->GetMeshComponent())
    {
        USkeletalMeshComponent* MeshCompR = P2WeaponR->GetMeshComponent();
        FTransform FirePosition = MeshCompR->GetSocketTransform(TEXT("fireposition"));


        GetWorld()->SpawnActor<ABullet>(*bulletFactory, FirePosition);

        LineTraceShoot(MeshCompR, TEXT("fireposition"));
    }
}

// Line trace shooting method
void ASecondCharacter::LineTraceShoot(USkeletalMeshComponent* GunMeshComponent, const FName& SocketName, float Strength)
{
    if (!GunMeshComponent)
    {
        UE_LOG(LogTemp, Warning, TEXT("GunMeshComponent is null"));
        return;
    }

    FVector Start = GunMeshComponent->GetSocketLocation(SocketName); // Start point: socket location
    FVector ForwardVector = GunMeshComponent->GetSocketRotation(SocketName).Vector(); // Direction: socket rotation
    FVector End = ((ForwardVector * 5000.f * Strength) + Start); // End point: 5000 units forward * strength
    FHitResult HitResult;
    FCollisionQueryParams CollisionParams;
    CollisionParams.AddIgnoredActor(this);

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
