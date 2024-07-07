// Fill out your copyright notice in the Description page of Project Settings.


#include "FirstCharacter_1.h"
#include "Player1Weapon.h"
#include "MyPlayerController.h"
#include "Player1Skill.h"

// Sets default values
AFirstCharacter_1::AFirstCharacter_1()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AFirstCharacter_1::BeginPlay()
{
	Super::BeginPlay();

	// �ʱ� ü�� ����
	Health = 5;

	FName WeaponSocket(TEXT("LeftHandSocket"));
	P1Weapon = GetWorld()->SpawnActor<APlayer1Weapon>(FVector::ZeroVector, FRotator::ZeroRotator);
	if (nullptr != P1Weapon)
	{
		P1Weapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, WeaponSocket);
	}
	//FName WeaponSocket(TEXT("LeftHandSocket"));
	//auto CurWeapon = GetWorld()->SpawnActor<APlayer1Weapon>(FVector::ZeroVector, FRotator::ZeroRotator);
	//if (nullptr != CurWeapon)
	//	CurWeapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, WeaponSocket);
}

// Called every frame
void AFirstCharacter_1::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AFirstCharacter_1::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AFirstCharacter_1::InputSkill(const struct FInputActionValue& inputValue)
{
	//Super::DisplayMessage("P1 Skill Attack!");
	SkillStart();
	//Super::PerformDash(GetActorForwardVector(), 2000.0f);
	
	// ��ų ���� ����
	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;
	FVector SpawnLocation = GetActorLocation();
	FRotator SpawnRotation = FRotator::ZeroRotator;

	if (!P1SkillFactory)
	{
		UE_LOG(LogTemp, Error, TEXT("P1SkillFactory is not set"));
		return;
	}

	APlayer1Skill* SkillActor = GetWorld()->SpawnActor<APlayer1Skill>(P1SkillFactory, SpawnLocation, SpawnRotation, SpawnParams);
	if (SkillActor)
	{
		// ��ų ���Ͱ� ĳ���� ������ ������ ����
		SkillActor->InitOrbit(this);
		UE_LOG(LogTemp, Warning, TEXT("Skill Actor spawned successfully"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to spawn Skill Actor"));
	}

	if (P1Weapon)
	{
		P1Weapon->WeaponAttack(EAttackType::Skill);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("P1Weapon is not set"));
	}
}

void AFirstCharacter_1::InputAerialAttack()
{
	//Super::DisplayMessage("P1 Aerial Attack!");
	Super::bAerialAttack = true; // ���� ���� ���� ����
	AerialAttackStart();
	if (P1Weapon)
	{
		P1Weapon->WeaponAttack(EAttackType::AerialAttack);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("P1Weapon is not set"));
	}
	const float FastFallSpeed = -1200.0f; // ���� ���� �ӵ� ����
	Super::LaunchCharacter(FVector(0, 0, FastFallSpeed), true, true); // ������ ����
}

void AFirstCharacter_1::PerformStrongAttack()
{
	Super::bIsStrongAttack = true;
	//Super::DisplayMessage("P1 Strong Attack!");
	if (P1Weapon)
	{
		P1Weapon->WeaponAttack(EAttackType::StrongAttack);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("P1Weapon is not set"));
	}
	StrongAttackStart();
}

void AFirstCharacter_1::PerformFirstAttack()
{
	//Super::DisplayMessage("P1 First Attack!");
	//Super::PerformDash(GetActorForwardVector(), 1100.0f);
	if (P1Weapon)
	{
		P1Weapon->WeaponAttack(EAttackType::Attack1);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("P1Weapon is not set"));
	}
}

void AFirstCharacter_1::PerformSecondAttack()
{
	//Super::DisplayMessage("P1 Second Attack!");
	if (P1Weapon)
	{
		P1Weapon->WeaponAttack(EAttackType::Attack2);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("P1Weapon is not set"));
	}
	//Super::PerformDash(GetActorForwardVector(), 1200.0f);
}

void AFirstCharacter_1::PerformThirdAttack()
{
	//Super::DisplayMessage("P1 Third Attack!");
	if (P1Weapon)
	{
		P1Weapon->WeaponAttack(EAttackType::Attack3);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("P1Weapon is not set"));
	}
	//Super::PerformDash(GetActorForwardVector(), 1300.0f);
}

void AFirstCharacter_1::PerformFourthAttack()
{
	//Super::DisplayMessage("P1 Fourth Attack!");
	if (P1Weapon)
	{
		P1Weapon->WeaponAttack(EAttackType::Attack4);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("P1Weapon is not set"));
	}
	//Super::PerformDash(GetActorForwardVector(), 1400.0f);
}

void AFirstCharacter_1::Die()
{
	// ��� �޽��� ǥ��
	DisplayMessage(TEXT("P1 Died!"), 5.0f);
	// ĳ���� 1�� �׾����� ����
	AMyPlayerController* PC = Cast<AMyPlayerController>(GetController());
	if (PC)
	{
		PC->bIsP1Alive = false;
		PC->SwitchToCharacter(PC->BP_P2); // ĳ���� 2�� ��ȯ
	}
}