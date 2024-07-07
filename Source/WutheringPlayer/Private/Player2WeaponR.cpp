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

    // Box Collision ������Ʈ ��� �� ��Ʈ ������Ʈ�� ����
    BoxComp = CreateDefaultSubobject<USceneComponent>(TEXT("BoxComp"));
    RootComponent = BoxComp;

    // ���� ����ƽ�޽� ������Ʈ ���
    weaponMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("weaponMeshComp"));
    // �θ� ������Ʈ�� Mesh ������Ʈ�� ����
    weaponMeshComp->SetupAttachment(BoxComp);

    // ����ƽ�޽� ������ �ε�
    ConstructorHelpers::FObjectFinder<UStaticMesh> TempWeaponMesh(TEXT("/Script/Engine.StaticMesh'/Game/KKW/TPS_HandGun/TPS_HandGun/Weapon/Mesh/SM_Revolver.SM_Revolver'"));
    // ������ �ε尡 �����ߴٸ�
    if (TempWeaponMesh.Succeeded())
    {
        // ����ƽ�޽� ������ �Ҵ�
        weaponMeshComp->SetStaticMesh(TempWeaponMesh.Object);
        // ��ġ �����ϱ�
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

