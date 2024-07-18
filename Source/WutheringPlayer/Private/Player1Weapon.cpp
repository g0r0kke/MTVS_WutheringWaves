// Fill out your copyright notice in the Description page of Project Settings.

#include "Player1Weapon.h"
#include "Components/SkeletalMeshComponent.h"
//#include "Components/SceneComponent.h"
#include "Components/BoxComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "GameFramework/Character.h"

// Sets default values
APlayer1Weapon::APlayer1Weapon()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// �⺻ �� ������Ʈ ���
	SceneComp = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComp"));
	RootComponent = SceneComp;

	// ���� ���̷�Ż�޽� ������Ʈ ��� �� SceneComponent�� ����
	MeshComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WeaponMeshComp"));
	MeshComp->SetupAttachment(SceneComp);
	MeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	// Box Collision ������Ʈ ��� �� MeshComp�� ����
	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComp"));
	BoxComp->SetupAttachment(MeshComp);
	BoxComp->SetBoxExtent(FVector(30, 30, 70));
	BoxComp->SetRelativeLocation(FVector(0, 0, 50));

	BoxComp->SetGenerateOverlapEvents(true);
	BoxComp->SetCollisionProfileName(TEXT("P1Weapon"));

	// ���̷�Ż�޽� ������ �ε�
	ConstructorHelpers::FObjectFinder<USkeletalMesh> TempWeaponMesh(TEXT("/Script/Engine.SkeletalMesh'/Game/Asset/InfinityBladeWeapons/Weapons/Dual_Blade/Dual_Blade_WrappedDeath/SK_Dual_Blade_WrappedDeath.SK_Dual_Blade_WrappedDeath'"));

	// ������ �ε尡 �����ߴٸ�
	if (TempWeaponMesh.Succeeded())
	{
		// ���̷�Ż�޽� ������ �Ҵ�
		MeshComp->SetSkeletalMesh(TempWeaponMesh.Object);
		// ��ġ �����ϱ�
		MeshComp->SetRelativeLocation(FVector(0, 0, 0));
		MeshComp->SetRelativeRotation(FRotator(0.0f, 90.0f, 90.0f));
	}

	// �浹 ���� �ʱ�ȭ
	bIsOverlapping = false;
}

void APlayer1Weapon::WeaponAttack(EAttackType AttackType)
{
	if (AttackType == EAttackType::SkillDmg)
	{
		UE_LOG(LogTemp, Warning, TEXT("skill attack"));
		P1Attack(13);
		// �÷��̾�->���� �̺�Ʈ ���� �� ��
	}
	// �浹 ���� == true��� attacktype �˻�
	if (bIsOverlapping == true)
	{
		//UE_LOG(LogTemp, Warning, TEXT("WeaponAttack"));
		switch (AttackType)
		{
		case EAttackType::Attack1:
			P1Attack(40);
			break;
		case EAttackType::Attack2:
			P1Attack(51);
			break;
		case EAttackType::Attack3:
			P1Attack(36);
			P1Attack(36);
			break;
		case EAttackType::Attack4:
			P1Attack(85);
			break;
		case EAttackType::StrongAttack:
			P1Attack(77);
			break;
		case EAttackType::AerialAttack:
			P1Attack(87);
			//if (GEngine)
			//{
			//    GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("P1 AerialAttack"));
			//}
			break;
		case EAttackType::Skill:
			//if (GEngine)
			//{
			//    GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("P1 Skill-Sword"));
			//}
			break;
		default:
			// ���� ó��
			break;
		}
	}
}

//void APlayer1Weapon::P1Attack_Implementation(int32 P1ATK)
//{
//    if (GEngine)
//    {
//        FString DamageStr = FString::Printf(TEXT("P1ATK: %d"), P1ATK);
//        GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, DamageStr);
//    }
//}

// Called when the game starts or when spawned
void APlayer1Weapon::BeginPlay()
{
	Super::BeginPlay();

	// �浹ü�� �� �������� �ε����� ���� �� �˷���!!
	BoxComp->OnComponentBeginOverlap.AddDynamic(this, &APlayer1Weapon::OnMyBoxBeginOverlap);
	BoxComp->OnComponentEndOverlap.AddDynamic(this, &APlayer1Weapon::OnMyBoxEndOverlap);

}

// Called every frame
void APlayer1Weapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APlayer1Weapon::OnMyBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor != this && OtherComp)
	{
		if (OtherActor->IsA(BossInstance))
		{
			//UE_LOG(LogTemp, Warning, TEXT("OnMyBoxBeginOverlap"));
			bIsOverlapping = true;  // �浹 ���� ����
			// �߰� ���� �ۼ�

			// �޺�, ������ ���
		}
	}
}
void APlayer1Weapon::OnMyBoxEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor && OtherActor != this && OtherComp)
	{
		if (OtherActor->IsA(BossInstance))
		{
			//UE_LOG(LogTemp, Warning, TEXT("OnMyBoxEndOverlap"));
			bIsOverlapping = false;  // �浹 ���� ����
			// �߰� ���� �ۼ�
		}
	}
}