// Fill out your copyright notice in the Description page of Project Settings.


#include "Player2WeaponR.h"
#include "Components/SkeletalMeshComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/StaticMeshComponent.h"
// Sets default values
APlayer2WeaponR::APlayer2WeaponR(const FObjectInitializer& ObjectInitializer)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    // Set this actor to call Tick() every frame. You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;

    // Box Collision 컴포넌트 등록 및 루트 컴포넌트로 설정
    BoxComp = CreateDefaultSubobject<USceneComponent>(TEXT("BoxComp"));
    RootComponent = BoxComp;

    // 무기 스태틱메시 컴포넌트 등록
    weaponMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("weaponMeshComp"));
    // 부모 컴포넌트를 Mesh 컴포넌트로 설정
    weaponMeshComp->SetupAttachment(BoxComp);

    // 스태틱메시 데이터 로드
    ConstructorHelpers::FObjectFinder<UStaticMesh> TempWeaponMesh(TEXT("/Script/Engine.StaticMesh'/Game/KKW/TPS_HandGun/TPS_HandGun/Weapon/Mesh/SM_Revolver.SM_Revolver'"));
    // 데이터 로드가 성공했다면
    if (TempWeaponMesh.Succeeded())
    {
        // 스태틱메시 데이터 할당
        weaponMeshComp->SetStaticMesh(TempWeaponMesh.Object);
        // 위치 조정하기
        weaponMeshComp->SetRelativeLocation(FVector(0, 0, 0));
        weaponMeshComp->SetRelativeRotation(FRotator(0.0f, 90.0f, 90.0f));
    }

}

// Called when the game starts or when spawned
void APlayer2WeaponR::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlayer2WeaponR::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

