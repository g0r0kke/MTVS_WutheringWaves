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

	//// �⺻ �� ������Ʈ ���
	//SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	//RootComponent = SceneComponent;

	// Box Collision ������Ʈ ��� �� ��Ʈ ������Ʈ�� ����
	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComp"));
	SetRootComponent(BoxComp);
    BoxComp->SetBoxExtent(FVector(55, 55, 55));

    BoxComp->SetGenerateOverlapEvents(true);
    BoxComp->SetCollisionProfileName(TEXT("P1Weapon"));

	// ���� ����ƽ�޽� ������Ʈ ���
	MeshComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("weaponMeshComp"));
	// �θ� ������Ʈ�� Mesh ������Ʈ�� ����
	MeshComp->SetupAttachment(BoxComp);
    MeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	// ����ƽ�޽� ������ �ε�
	ConstructorHelpers::FObjectFinder<USkeletalMesh> TempWeaponMesh(TEXT("/Script/Engine.SkeletalMesh'/Game/Asset/InfinityBladeWeapons/Weapons/Dual_Blade/Dual_Blade_WrappedDeath/SK_Dual_Blade_WrappedDeath.SK_Dual_Blade_WrappedDeath'"));

	// ������ �ε尡 �����ߴٸ�
	if (TempWeaponMesh.Succeeded())
	{
		// ����ƽ�޽� ������ �Ҵ�
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
    // �浹 ���� == true��� attacktype �˻�
    if (bIsOverlapping == true)
    {
        switch (AttackType)
        {
        case EAttackType::Attack1:
            P1Attack(1);
            if (GEngine)
            {
                GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("P1 FirstAttack"));
            }
            break;
        case EAttackType::Attack2:
            P1Attack(1);
            if (GEngine)
            {
                GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("P1 SecondAttack"));
            }
            break;
        case EAttackType::Attack3:
            P1Attack(1);
            if (GEngine)
            {
                GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("P1 ThirdAttack"));
            }
            break;
        case EAttackType::Attack4:
            P1Attack(1);
            if (GEngine)
            {
                GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("P1 FourthAttack"));
            }
            break;
        case EAttackType::StrongAttack:
            P1Attack(1);
            if (GEngine)
            {
                GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("P1 Strong Attack"));
            }
            break;
        case EAttackType::AerialAttack:
            P1Attack(1);
            if (GEngine)
            {
                GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("P1 AerialAttack"));
            }
            break;
        case EAttackType::Skill:
            P1Attack(1);
            if (GEngine)
            {
                GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("P1 Skill"));
            }
            break;
        default:
            // ���� ó��
            break;
        }
    }
}

void APlayer1Weapon::P1Attack_Implementation(int32 P1ATK)
{
    if (GEngine)
    {
        FString DamageStr = FString::Printf(TEXT("P1ATK: %d"), P1ATK);
        GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, DamageStr);
    }
}

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
        ACharacter* Character = Cast<ACharacter>(OtherActor);
        if (Character)
        {
            bIsOverlapping = true;  // �浹 ���� ����
            // �߰� ���� �ۼ�
        }
    }
}
void APlayer1Weapon::OnMyBoxEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
    if (OtherActor && OtherActor != this && OtherComp)
    {
        ACharacter* Character = Cast<ACharacter>(OtherActor);
        if (Character)
        {
            bIsOverlapping = false;  // �浹 ���� ����
            // �߰� ���� �ۼ�
        }
    }
}