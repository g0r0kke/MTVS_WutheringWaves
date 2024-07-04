// Fill out your copyright notice in the Description page of Project Settings.


#include "FirstCharacter_1.h"
#include "Player1Weapon.h"

// Sets default values
AFirstCharacter_1::AFirstCharacter_1()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//// 무기 스태틱메시 컴포넌트 등록
	//weaponMeshComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("weaponMeshComp"));
	//// 부모 컴포넌트를 Mesh 컴포넌트로 설정
	//weaponMeshComp->SetupAttachment(GetMesh());
	//// 스태틱메시 데이터 로드
	//ConstructorHelpers::FObjectFinder<USkeletalMesh> TempWeaponMesh(TEXT("/Script/Engine.SkeletalMesh'/Game/Asset/InfinityBladeWeapons/Weapons/Dual_Blade/Dual_Blade_WrappedDeath/SK_Dual_Blade_WrappedDeath.SK_Dual_Blade_WrappedDeath'"));
	//// 데이터 로드가 성공했다면
	//if (TempWeaponMesh.Succeeded())
	//{
	//	// 스태틱메시 데이터 할당
	//	weaponMeshComp->SetSkeletalMesh(TempWeaponMesh.Object);
	//	// 위치 조정하기
	//	weaponMeshComp->SetRelativeLocation(FVector(-14, 52, 120));
	//}
}

// Called when the game starts or when spawned
void AFirstCharacter_1::BeginPlay()
{
	Super::BeginPlay();
	
	FName WeaponSocket(TEXT("LeftHandSocket"));
	auto CurWeapon = GetWorld()->SpawnActor<APlayer1Weapon>(FVector::ZeroVector, FRotator::ZeroRotator);
	if (nullptr != CurWeapon)
		CurWeapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, WeaponSocket);
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
