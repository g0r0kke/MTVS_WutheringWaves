// Fill out your copyright notice in the Description page of Project Settings.

#include "Player1Weapon.h"
#include "Components/SkeletalMeshComponent.h"
//#include "Components/SceneComponent.h"
#include "Components/BoxComponent.h"
#include "UObject/ConstructorHelpers.h"

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
	RootComponent = BoxComp;

	// ���� ����ƽ�޽� ������Ʈ ���
	weaponMeshComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("weaponMeshComp"));
	// �θ� ������Ʈ�� Mesh ������Ʈ�� ����
	weaponMeshComp->SetupAttachment(BoxComp);

	// ����ƽ�޽� ������ �ε�
	ConstructorHelpers::FObjectFinder<USkeletalMesh> TempWeaponMesh(TEXT("/Script/Engine.SkeletalMesh'/Game/Asset/InfinityBladeWeapons/Weapons/Dual_Blade/Dual_Blade_WrappedDeath/SK_Dual_Blade_WrappedDeath.SK_Dual_Blade_WrappedDeath'"));

	// ������ �ε尡 �����ߴٸ�
	if (TempWeaponMesh.Succeeded())
	{
		// ����ƽ�޽� ������ �Ҵ�
		weaponMeshComp->SetSkeletalMesh(TempWeaponMesh.Object);
		// ��ġ �����ϱ�
		weaponMeshComp->SetRelativeLocation(FVector(0, 0, 0));
		weaponMeshComp->SetRelativeRotation(FRotator(0.0f, 90.0f, 90.0f));
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