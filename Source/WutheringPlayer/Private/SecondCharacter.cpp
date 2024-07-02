// Fill out your copyright notice in the Description page of Project Settings.


#include "SecondCharacter.h"

// Sets default values
ASecondCharacter::ASecondCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASecondCharacter::BeginPlay()
{
	Super::BeginPlay();
	
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

}

void ASecondCharacter::InputSkill(const struct FInputActionValue& inputValue)
{
	Super::DisplayMessage("P2 Skill Attack!");
	Super::PerformDash(GetActorForwardVector(), 1200.0f);
}

void ASecondCharacter::InputAerialAttack()
{
	Super::DisplayMessage("P2 Aerial Attack!");
	Super::bAerialAttack = true; // 공중 공격 상태 설정
	const float FastFallSpeed = -1200.0f; // 빠른 낙하 속도 조정
	Super::LaunchCharacter(FVector(0, 0, FastFallSpeed), true, true); // 빠르게 낙하
}

void ASecondCharacter::PerformStrongAttack()
{
	Super::bIsStrongAttack = true;
	Super::DisplayMessage("P2 Strong Attack!");
}

void ASecondCharacter::PerformFirstAttack()
{
	Super::DisplayMessage("P2 First Attack!");
	Super::PerformDash(GetActorForwardVector(), 1100.0f);
}

void ASecondCharacter::PerformSecondAttack()
{
	Super::DisplayMessage("P2 Second Attack!");
	Super::PerformDash(GetActorForwardVector(), 1200.0f);
}

void ASecondCharacter::PerformThirdAttack()
{
	Super::DisplayMessage("P2 Third Attack!");
	Super::PerformDash(GetActorForwardVector(), 1300.0f);
}

void ASecondCharacter::PerformFourthAttack()
{
	Super::DisplayMessage("P2 Fourth Attack!");
	Super::PerformDash(GetActorForwardVector(), 1400.0f);
}