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

    // 무기 스태틱메시 컴포넌트 등록
    BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComp"));
    SetRootComponent(BoxComp);
    BoxComp->SetBoxExtent(FVector(10 , 10, 10));

    BoxComp->SetGenerateOverlapEvents(true);
    BoxComp->SetCollisionProfileName(UCollisionProfile::NoCollision_ProfileName);

    MeshCompL = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WeaponMeshCompL"));
    // 부모 컴포넌트를 Mesh 컴포넌트로 설정
    MeshCompL->SetupAttachment(BoxComp);
    MeshCompL->SetCollisionEnabled(ECollisionEnabled::NoCollision);


    // 스태틱메시 데이터 로드
    ConstructorHelpers::FObjectFinder<USkeletalMesh>TempWeaponMesh(TEXT("/Script/Engine.SkeletalMesh'/Game/KKW/FPWeapon/Mesh/SK_FPGun.SK_FPGun'"));
    // 데이터 로드가 성공했다면
    if (TempWeaponMesh.Succeeded())
    {
        // 스태틱메시 데이터 할당
        MeshCompL->SetSkeletalMesh(TempWeaponMesh.Object);
        // 위치 조정하기
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
