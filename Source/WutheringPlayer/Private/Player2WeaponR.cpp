// Fill out your copyright notice in the Description page of Project Settings.


#include "Player2WeaponR.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Character.h"
#include "UObject/ConstructorHelpers.h"
// Sets default values
APlayer2WeaponR::APlayer2WeaponR(const FObjectInitializer& ObjectInitializer)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    // Set this actor to call Tick() every frame. You can turn this off to improve performance if you don't need it.
    BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComp"));
    SetRootComponent(BoxComp);
    BoxComp->SetBoxExtent(FVector(10,10,10));

    BoxComp->SetGenerateOverlapEvents(true);
    BoxComp->SetCollisionProfileName(UCollisionProfile::NoCollision_ProfileName);

    // 무기 스태틱메시 컴포넌트 등록
    MeshCompR = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WeaponMeshCompR"));
    // 부모 컴포넌트를 Mesh 컴포넌트로 설정
    MeshCompR->SetupAttachment(BoxComp);
    MeshCompR->SetCollisionEnabled(ECollisionEnabled::NoCollision);

    // 스태틱메시 데이터 로드
    ConstructorHelpers::FObjectFinder<USkeletalMesh> TempWeaponMesh(TEXT("/Script/Engine.SkeletalMesh'/Game/KKW/FPWeapon/Mesh/SK_FPGun.SK_FPGun'"));
    // 데이터 로드가 성공했다면
    if (TempWeaponMesh.Succeeded())
    {
        // 스태틱메시 데이터 할당
        MeshCompR->SetSkeletalMesh(TempWeaponMesh.Object);
        // 위치 조정하기
        MeshCompR->SetRelativeLocation(FVector(0, 0, 0));
        MeshCompR->SetRelativeRotation(FRotator(0.0f, 90.0f, 90.0f));
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

