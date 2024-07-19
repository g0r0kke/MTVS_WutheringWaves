// Fill out your copyright notice in the Description page of Project Settings.


#include "FirstCharacter_1.h"
#include "Player1Weapon.h"
#include "MyPlayerController.h"
#include "Player1Skill.h"
#include "Kismet/GameplayStatics.h"
#include "EngineUtils.h" // TActorIterator 사용을 위해 추가
#include "TimerManager.h"

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
	// 1219
	HP = 4364;

	bIsAttack = false;

	//p1 = this;

	FName WeaponSocket(TEXT("LeftHandSocket"));
	P1Weapon = GetWorld()->SpawnActor<APlayer1Weapon>(P1WeaponFactory);
	if (nullptr != P1Weapon)
	{
		P1Weapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, WeaponSocket);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("P1Weapon is not set"));
	}

	//FName WeaponSocket(TEXT("LeftHandSocket"));
	//P1Weapon = GetWorld()->SpawnActor<APlayer1Weapon>(FVector::ZeroVector, FRotator::ZeroRotator);
	//if (nullptr != P1Weapon)
	//{
	//	P1Weapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, WeaponSocket);
	//}
	P1Weapon->MeshComp->SetVisibility(false);
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

ACharacter* AFirstCharacter_1::FindClosestBoss()
{
	ACharacter* ClosestBoss = nullptr;
	float MinDistance = FLT_MAX;

	for (TActorIterator<ACharacter> It(GetWorld()); It; ++It)
	{
		if (It->IsA(BossFactory))
		{
			float Distance = FVector::Dist(GetActorLocation(), It->GetActorLocation());
			if (Distance < MinDistance)
			{
				MinDistance = Distance;
				ClosestBoss = *It;
			}
		}
	}

	return ClosestBoss;
}

void AFirstCharacter_1::RotateTowardsClosestBoss()
{
	ACharacter* ClosestBoss = FindClosestBoss();
	if (ClosestBoss)
	{
		FRotator NewRotation = (ClosestBoss->GetActorLocation() - GetActorLocation()).Rotation();
		SetActorRotation(NewRotation);
	}
}

void AFirstCharacter_1::InputSkill(const struct FInputActionValue& inputValue)
{
	if (bIsSkillOnCooldown)
	{
		UE_LOG(LogTemp, Warning, TEXT("Skill is on cooldown!"));
		return; // 스킬이 쿨타임 중이면 스킬을 사용하지 않음
	}

	RotateTowardsClosestBoss();
	P1Weapon->MeshComp->SetVisibility(true);
	//Super::DisplayMessage("P1 Skill Attack!");
	SkillStart();
	Super::PerformDash(GetActorForwardVector(), 2000.0f);

	// 스킬 액터 스폰
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
		// 스킬 액터가 캐릭터 주위를 돌도록 설정
		SkillActor->InitOrbit(this);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to spawn Skill Actor"));
	}

	if (P1Weapon)
	{
		P1Weapon->WeaponAttack(EAttackType::Skill);
		//bIsAttack = true;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("P1Weapon is not set"));
	}

	bIsSkillOnCooldown = true; // 스킬이 쿨타임 중임을 표시
	GetWorldTimerManager().SetTimer(SkillCooldownTimerHandle, this, &AFirstCharacter_1::ResetSkillCooldown, 6.0f, false); // 6초 후 쿨타임 리셋
}

// 쿨타임 리셋 함수
void AFirstCharacter_1::ResetSkillCooldown()
{
	bIsSkillOnCooldown = false; // 쿨타임 해제
	UE_LOG(LogTemp, Log, TEXT("Skill cooldown reset!"));
}

void AFirstCharacter_1::InputAerialAttack()
{
	RotateTowardsClosestBoss();
	P1Weapon->MeshComp->SetVisibility(true);
	//Super::DisplayMessage("P1 Aerial Attack!");
	Super::bAerialAttack = true; // 공중 공격 상태 설정
	AerialAttackStart();
	if (P1Weapon)
	{
		P1Weapon->WeaponAttack(EAttackType::AerialAttack);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("P1Weapon is not set"));
	}
	const float FastFallSpeed = -1200.0f; // 빠른 낙하 속도 조정
	Super::LaunchCharacter(FVector(0, 0, FastFallSpeed), true, true); // 빠르게 낙하
}

void AFirstCharacter_1::PerformStrongAttack()
{
	RotateTowardsClosestBoss();
	P1Weapon->MeshComp->SetVisibility(true);
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
	RotateTowardsClosestBoss();
	P1Weapon->MeshComp->SetVisibility(true);
	//Super::DisplayMessage("P1 First Attack!");
	Super::PerformDash(GetActorForwardVector(), 1100.0f);
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
	RotateTowardsClosestBoss();
	P1Weapon->MeshComp->SetVisibility(true);
	//Super::DisplayMessage("P1 Second Attack!");
	if (P1Weapon)
	{
		P1Weapon->WeaponAttack(EAttackType::Attack2);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("P1Weapon is not set"));
	}
	Super::PerformDash(GetActorForwardVector(), 1200.0f);
}

void AFirstCharacter_1::PerformThirdAttack()
{
	RotateTowardsClosestBoss();
	P1Weapon->MeshComp->SetVisibility(true);
	//Super::DisplayMessage("P1 Third Attack!");
	if (P1Weapon)
	{
		P1Weapon->WeaponAttack(EAttackType::Attack3);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("P1Weapon is not set"));
	}
	Super::PerformDash(GetActorForwardVector(), 1300.0f);
}

void AFirstCharacter_1::PerformFourthAttack()
{
	RotateTowardsClosestBoss();
	P1Weapon->MeshComp->SetVisibility(true);
	//Super::DisplayMessage("P1 Fourth Attack!");
	if (P1Weapon)
	{
		P1Weapon->WeaponAttack(EAttackType::Attack4);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("P1Weapon is not set"));
	}
	Super::PerformDash(GetActorForwardVector(), 1400.0f);
}

void AFirstCharacter_1::Die()
{
	// 사망 메시지 표시
	//DisplayMessage(TEXT("P1 Died!"), 5.0f);
	P1Death();
	//// 캐릭터 1이 죽었음을 설정
	//AMyPlayerController* PC = Cast<AMyPlayerController>(GetController());
	//if (PC)
	//{
	//	PC->bIsP1Alive = false;
	//	PC->SwitchToCharacter(PC->BP_P2); // 캐릭터 2로 전환
	//}
}

//void AFirstCharacter_1::HideWeapon()
//{
//	P1Weapon->MeshComp->SetVisibility(false);
//}
