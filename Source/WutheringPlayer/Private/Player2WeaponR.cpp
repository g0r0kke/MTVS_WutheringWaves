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

    // ���� ����ƽ�޽� ������Ʈ ���
    MeshCompR = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WeaponMeshCompR"));
    // �θ� ������Ʈ�� Mesh ������Ʈ�� ����
    MeshCompR->SetupAttachment(BoxComp);
    MeshCompR->SetCollisionEnabled(ECollisionEnabled::NoCollision);

    // ����ƽ�޽� ������ �ε�
    ConstructorHelpers::FObjectFinder<USkeletalMesh> TempWeaponMesh(TEXT("/Script/Engine.SkeletalMesh'/Game/KKW/FPWeapon/Mesh/SK_FPGun.SK_FPGun'"));
    // ������ �ε尡 �����ߴٸ�
    if (TempWeaponMesh.Succeeded())
    {
        // ����ƽ�޽� ������ �Ҵ�
        MeshCompR->SetSkeletalMesh(TempWeaponMesh.Object);
        // ��ġ �����ϱ�
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

