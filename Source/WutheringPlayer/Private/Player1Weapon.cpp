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

	//// 기본 씬 컴포넌트 등록
	//SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	//RootComponent = SceneComponent;

	// Box Collision 컴포넌트 등록 및 루트 컴포넌트로 설정
	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComp"));
	SetRootComponent(BoxComp);
    BoxComp->SetBoxExtent(FVector(55, 55, 55));

    BoxComp->SetGenerateOverlapEvents(true);
    BoxComp->SetCollisionProfileName(TEXT("P1Weapon"));

	// 무기 스태틱메시 컴포넌트 등록
	MeshComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("weaponMeshComp"));
	// 부모 컴포넌트를 Mesh 컴포넌트로 설정
	MeshComp->SetupAttachment(BoxComp);
    MeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	// 스태틱메시 데이터 로드
	ConstructorHelpers::FObjectFinder<USkeletalMesh> TempWeaponMesh(TEXT("/Script/Engine.SkeletalMesh'/Game/Asset/InfinityBladeWeapons/Weapons/Dual_Blade/Dual_Blade_WrappedDeath/SK_Dual_Blade_WrappedDeath.SK_Dual_Blade_WrappedDeath'"));

	// 데이터 로드가 성공했다면
	if (TempWeaponMesh.Succeeded())
	{
		// 스태틱메시 데이터 할당
        MeshComp->SetSkeletalMesh(TempWeaponMesh.Object);
		// 위치 조정하기
        MeshComp->SetRelativeLocation(FVector(0, 0, 0));
        MeshComp->SetRelativeRotation(FRotator(0.0f, 90.0f, 90.0f));
	}

    // 충돌 상태 초기화
    bIsOverlapping = false;
}

void APlayer1Weapon::WeaponAttack(EAttackType AttackType)
{
    // 충돌 변수 == true라면 attacktype 검사
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
            // 예외 처리
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

    // 충돌체야 너 누군가와 부딪히면 나도 좀 알려줘!!
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
            bIsOverlapping = true;  // 충돌 변수 설정
            // 추가 로직 작성
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
            bIsOverlapping = false;  // 충돌 변수 해제
            // 추가 로직 작성
        }
    }
}