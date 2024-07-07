// Fill out your copyright notice in the Description page of Project Settings.


#include "Player1Skill.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Actor.h"
#include "FirstCharacter_1.h"
#include "Kismet/KismetMathLibrary.h"
#include "Player1Weapon.h"

// Sets default values
APlayer1Skill::APlayer1Skill()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Sphere Collision 컴포넌트 등록 및 루트 컴포넌트로 설정
	SphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	SetRootComponent(SphereComp);
	SphereComp->SetSphereRadius(300.0f, true);
	SphereComp->SetRelativeScale3D(FVector(1.1f, 1.1f, 0.2f));

	SphereComp->SetGenerateOverlapEvents(true);
	SphereComp->SetCollisionProfileName(TEXT("P1Weapon"));

	// 무기 스태틱메시 컴포넌트 등록
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SkillMeshComp"));
	// 부모 컴포넌트를 Mesh 컴포넌트로 설정
	MeshComp->SetupAttachment(SphereComp);
	MeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	// 스태틱메시 데이터 로드
	ConstructorHelpers::FObjectFinder<UStaticMesh> TempSkillMesh(TEXT("/Script/Engine.StaticMesh'/Engine/BasicShapes/Sphere.Sphere'"));

	// 데이터 로드가 성공했다면
	if (TempSkillMesh.Succeeded())
	{
		// 스태틱메시 데이터 할당
		MeshComp->SetStaticMesh(TempSkillMesh.Object);
		// 위치 조정하기
		MeshComp->SetRelativeLocation(FVector(0, 0, 0));
		MeshComp->SetRelativeRotation(FRotator(0.0f, 0.0f, 0.0f));
	}

	// 충돌 상태 초기화
	bIsOverlapping = false;

	// Sill Plate 기본 설정
	Radius = 150.0f; // 기본 반지름 설정
	Speed = 270.0f;  // 기본 회전 속도 설정
	Angle = 0.0f;    // 초기 각도 설정

	// APlayer1Weapon 객체의 인스턴스 생성
	Player1Weapon = CreateDefaultSubobject<APlayer1Weapon>(TEXT("Player1Weapon"));
}

// Called when the game starts or when spawned
void APlayer1Skill::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("Player1Skill has been initialized"));

	SphereComp->OnComponentBeginOverlap.AddDynamic(this, &APlayer1Skill::OnMySphereBeginOverlap);
	SphereComp->OnComponentEndOverlap.AddDynamic(this, &APlayer1Skill::OnMySphereEndOverlap);

	// Player1Weapon 객체를 동적으로 생성
	Player1Weapon = GetWorld()->SpawnActor<APlayer1Weapon>(APlayer1Weapon::StaticClass());

	// Player1Weapon의 가시성과 콜리전 비활성화
	if (Player1Weapon)
	{
		// 가시성 비활성화
		Player1Weapon->SetActorHiddenInGame(true);

		// 콜리전 비활성화
		Player1Weapon->SetActorEnableCollision(false);
	}
}

// Called every frame
void APlayer1Skill::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//// 각도 업데이트
	//Angle += Speed * DeltaTime;

	//// 새로운 위치 계산
	//float RadAngle = FMath::DegreesToRadians(Angle);
	//FVector NewLocation = GetActorLocation();
	//NewLocation.X += Radius * FMath::Cos(RadAngle);
	//NewLocation.Y += Radius * FMath::Sin(RadAngle);

	//SetActorLocation(NewLocation);

	if (OrbitingCharacter)
	{
		// 각도 업데이트
		Angle += Speed * DeltaTime;

		float RadAngle = FMath::DegreesToRadians(Angle);
		FVector CenterLocation = OrbitingCharacter->GetActorLocation();
		FVector NewLocation = CenterLocation + FVector(Radius * FMath::Cos(RadAngle), Radius * FMath::Sin(RadAngle), 30);

		SetActorLocation(NewLocation);
	}

	Angle += Speed * DeltaTime;
	if (Angle >= 360.0f)
	{
		DestroySkill();
	}

	if (bIsOverlapping == true)
	{
		Player1Weapon->P1Attack(10);  // P1Attack 함수 호출
		if (GEngine)
		{
			FString DamageStr = FString::Printf(TEXT("P1 Skill-Plate"));
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, DamageStr);
		}
	}
}

void APlayer1Skill::InitOrbit(AFirstCharacter_1* Character)
{
	OrbitingCharacter = Character;
}

void APlayer1Skill::OnMySphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor != this && OtherComp)
	{
		ACharacter* Character = Cast<ACharacter>(OtherActor);
		if (Character)
		{
			bIsOverlapping = true;  // 충돌 변수 설정
			Player1Weapon->P1Attack(10);
			// 추가 로직 작성
		}
	}
}

void APlayer1Skill::OnMySphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
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

void APlayer1Skill::DestroySkill()
{

	Destroy();
}