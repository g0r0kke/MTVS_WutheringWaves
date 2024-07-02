// Fill out your copyright notice in the Description page of Project Settings.


#include "FirstCharacter_1.h"

// Sets default values
AFirstCharacter_1::AFirstCharacter_1()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// ���� ���̷�Ż�޽� ������Ʈ ���
	weaponMeshComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("weaponMeshComp"));
	// �θ� ������Ʈ�� Mesh ������Ʈ�� ����
	weaponMeshComp->SetupAttachment(GetMesh());
	// ���̷�Ż�޽� ������ �ε�
	ConstructorHelpers::FObjectFinder<USkeletalMesh> TempWeaponMesh(TEXT("/Script/Engine.SkeletalMesh'/Game/InfinityBladeWeapons/Weapons/Dual_Blade/Dual_Blade_WrappedDeath/SK_Dual_Blade_WrappedDeath.SK_Dual_Blade_WrappedDeath'"));
	// ������ �ε尡 �����ߴٸ�
	if (TempWeaponMesh.Succeeded())
	{
		// ���̷�Ż�޽� ������ �Ҵ�
		weaponMeshComp->SetSkeletalMesh(TempWeaponMesh.Object);
		// ��ġ �����ϱ�
		weaponMeshComp->SetRelativeLocation(FVector(-14, 52, 120));
	}
}

// Called when the game starts or when spawned
void AFirstCharacter_1::BeginPlay()
{
	Super::BeginPlay();
	
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
	Super::PerformDash(GetActorForwardVector(), 1200.0f);
}

void AFirstCharacter_1::InputAerialAttack()
{
	Super::DisplayMessage("P1 Aerial Attack!");
	Super::bAerialAttack = true; // ���� ���� ���� ����
	const float FastFallSpeed = -1200.0f; // ���� ���� �ӵ� ����
	Super::LaunchCharacter(FVector(0, 0, FastFallSpeed), true, true); // ������ ����
}

void AFirstCharacter_1::PerformStrongAttack()
{
	Super::bIsStrongAttack = true;
	Super::DisplayMessage("P1 Strong Attack!");
}

void AFirstCharacter_1::PerformFirstAttack()
{
	Super::DisplayMessage("P1 First Attack!");
	Super::PerformDash(GetActorForwardVector(), 1100.0f);
}

void AFirstCharacter_1::PerformSecondAttack()
{
	Super::DisplayMessage("P1 Second Attack!");
	Super::PerformDash(GetActorForwardVector(), 1200.0f);
}

void AFirstCharacter_1::PerformThirdAttack()
{
	Super::DisplayMessage("P1 Third Attack!");
	Super::PerformDash(GetActorForwardVector(), 1300.0f);
}

void AFirstCharacter_1::PerformFourthAttack()
{
	Super::DisplayMessage("P1 Fourth Attack!");
	Super::PerformDash(GetActorForwardVector(), 1400.0f);
}
