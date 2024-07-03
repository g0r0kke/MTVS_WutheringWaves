// Fill out your copyright notice in the Description page of Project Settings.


#include "Player1Weapon.h"

// Sets default values
APlayer1Weapon::APlayer1Weapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// 무기 스태틱메시 컴포넌트 등록
	weaponMeshComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("weaponMeshComp"));
	// 부모 컴포넌트를 Mesh 컴포넌트로 설정
	RootComponent = weaponMeshComp;

	// 스태틱메시 데이터 로드
	ConstructorHelpers::FObjectFinder<USkeletalMesh> TempWeaponMesh(TEXT("/Script/Engine.SkeletalMesh'/Game/Asset/InfinityBladeWeapons/Weapons/Dual_Blade/Dual_Blade_WrappedDeath/SK_Dual_Blade_WrappedDeath.SK_Dual_Blade_WrappedDeath'"));

	// 데이터 로드가 성공했다면
	if (TempWeaponMesh.Succeeded())
	{
		// 스태틱메시 데이터 할당
		weaponMeshComp->SetSkeletalMesh(TempWeaponMesh.Object);
		// 위치 조정하기
		weaponMeshComp->SetRelativeLocation(FVector(0, 0, 0));
		weaponMeshComp->SetWorldRotation(FRotator(0.0f, 90.0f, 90.0f));
	}
}

// Called when the game starts or when spawned
void APlayer1Weapon::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlayer1Weapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

