// Fill out your copyright notice in the Description page of Project Settings.


#include "FirstCharacter_1.h"
#include "Player1Weapon.h"
#include "MyPlayerController.h"

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

	// 초기 체력 설정
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
	Super::DisplayMessage("P1 Skill Attack!");
	SkillStart();
	Super::PerformDash(GetActorForwardVector(), 2000.0f);
}

void AFirstCharacter_1::InputAerialAttack()
{
	Super::DisplayMessage("P1 Aerial Attack!");
	Super::bAerialAttack = true; // 공중 공격 상태 설정
	AerialAttackStart();
	const float FastFallSpeed = -1200.0f; // 빠른 낙하 속도 조정
	Super::LaunchCharacter(FVector(0, 0, FastFallSpeed), true, true); // 빠르게 낙하
}

void AFirstCharacter_1::PerformStrongAttack()
{
	Super::bIsStrongAttack = true;
	Super::DisplayMessage("P1 Strong Attack!");
	StrongAttackStart();
}

void AFirstCharacter_1::PerformFirstAttack()
{
	Super::DisplayMessage("P1 First Attack!");
	//Super::PerformDash(GetActorForwardVector(), 1100.0f);
}

void AFirstCharacter_1::PerformSecondAttack()
{
	Super::DisplayMessage("P1 Second Attack!");
	//Super::PerformDash(GetActorForwardVector(), 1200.0f);
}

void AFirstCharacter_1::PerformThirdAttack()
{
	Super::DisplayMessage("P1 Third Attack!");
	//Super::PerformDash(GetActorForwardVector(), 1300.0f);
}

void AFirstCharacter_1::PerformFourthAttack()
{
	Super::DisplayMessage("P1 Fourth Attack!");
	//Super::PerformDash(GetActorForwardVector(), 1400.0f);
}

void AFirstCharacter_1::Die()
{
	// 사망 메시지 표시
	DisplayMessage(TEXT("P1 Died!"), 5.0f);
	// 캐릭터 1이 죽었음을 설정
	AMyPlayerController* PC = Cast<AMyPlayerController>(GetController());
	if (PC)
	{
		PC->bIsP1Alive = false;
		PC->SwitchToCharacter(PC->BP_P2); // 캐릭터 2로 전환
	}
}