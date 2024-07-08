#include "Player2WeaponL.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Character.h"
#include "UObject/ConstructorHelpers.h"



// Sets default values
APlayer2WeaponL::APlayer2WeaponL(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
    // Set this actor to call Tick() every frame. You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;

    // ���� ����ƽ�޽� ������Ʈ ���
    BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComp"));
    SetRootComponent(BoxComp);
    BoxComp->SetBoxExtent(FVector(10 , 10, 10));

    BoxComp->SetGenerateOverlapEvents(true);
    BoxComp->SetCollisionProfileName(UCollisionProfile::NoCollision_ProfileName);

    MeshCompL = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WeaponMeshCompL"));
    // �θ� ������Ʈ�� Mesh ������Ʈ�� ����
    MeshCompL->SetupAttachment(BoxComp);
    MeshCompL->SetCollisionEnabled(ECollisionEnabled::NoCollision);


    // ����ƽ�޽� ������ �ε�
    ConstructorHelpers::FObjectFinder<USkeletalMesh>TempWeaponMesh(TEXT("/Script/Engine.SkeletalMesh'/Game/KKW/FPWeapon/Mesh/SK_FPGun.SK_FPGun'"));
    // ������ �ε尡 �����ߴٸ�
    if (TempWeaponMesh.Succeeded())
    {
        // ����ƽ�޽� ������ �Ҵ�
        MeshCompL->SetSkeletalMesh(TempWeaponMesh.Object);
        // ��ġ �����ϱ�
        MeshCompL->SetRelativeLocation(FVector(0, 0, 0));
        MeshCompL->SetRelativeRotation(FRotator(0.0f, 90.0f, 90.0f));
    }
}

// Called when the game starts or when spawned
void APlayer2WeaponL::BeginPlay()
{
    Super::BeginPlay();
}

// Called every frame
void APlayer2WeaponL::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}
