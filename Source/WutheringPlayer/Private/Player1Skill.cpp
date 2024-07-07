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

	// Sphere Collision ������Ʈ ��� �� ��Ʈ ������Ʈ�� ����
	SphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	SetRootComponent(SphereComp);
	SphereComp->SetSphereRadius(300.0f, true);
	SphereComp->SetRelativeScale3D(FVector(1.1f, 1.1f, 0.2f));

	SphereComp->SetGenerateOverlapEvents(true);
	SphereComp->SetCollisionProfileName(TEXT("P1Weapon"));

	// ���� ����ƽ�޽� ������Ʈ ���
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SkillMeshComp"));
	// �θ� ������Ʈ�� Mesh ������Ʈ�� ����
	MeshComp->SetupAttachment(SphereComp);
	MeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	// ����ƽ�޽� ������ �ε�
	ConstructorHelpers::FObjectFinder<UStaticMesh> TempSkillMesh(TEXT("/Script/Engine.StaticMesh'/Engine/BasicShapes/Sphere.Sphere'"));

	// ������ �ε尡 �����ߴٸ�
	if (TempSkillMesh.Succeeded())
	{
		// ����ƽ�޽� ������ �Ҵ�
		MeshComp->SetStaticMesh(TempSkillMesh.Object);
		// ��ġ �����ϱ�
		MeshComp->SetRelativeLocation(FVector(0, 0, 0));
		MeshComp->SetRelativeRotation(FRotator(0.0f, 0.0f, 0.0f));
	}

	// �浹 ���� �ʱ�ȭ
	bIsOverlapping = false;

	// Sill Plate �⺻ ����
	Radius = 150.0f; // �⺻ ������ ����
	Speed = 270.0f;  // �⺻ ȸ�� �ӵ� ����
	Angle = 0.0f;    // �ʱ� ���� ����

	// APlayer1Weapon ��ü�� �ν��Ͻ� ����
	Player1Weapon = CreateDefaultSubobject<APlayer1Weapon>(TEXT("Player1Weapon"));
}

// Called when the game starts or when spawned
void APlayer1Skill::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("Player1Skill has been initialized"));

	SphereComp->OnComponentBeginOverlap.AddDynamic(this, &APlayer1Skill::OnMySphereBeginOverlap);
	SphereComp->OnComponentEndOverlap.AddDynamic(this, &APlayer1Skill::OnMySphereEndOverlap);

	// Player1Weapon ��ü�� �������� ����
	Player1Weapon = GetWorld()->SpawnActor<APlayer1Weapon>(APlayer1Weapon::StaticClass());

	// Player1Weapon�� ���ü��� �ݸ��� ��Ȱ��ȭ
	if (Player1Weapon)
	{
		// ���ü� ��Ȱ��ȭ
		Player1Weapon->SetActorHiddenInGame(true);

		// �ݸ��� ��Ȱ��ȭ
		Player1Weapon->SetActorEnableCollision(false);
	}
}

// Called every frame
void APlayer1Skill::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//// ���� ������Ʈ
	//Angle += Speed * DeltaTime;

	//// ���ο� ��ġ ���
	//float RadAngle = FMath::DegreesToRadians(Angle);
	//FVector NewLocation = GetActorLocation();
	//NewLocation.X += Radius * FMath::Cos(RadAngle);
	//NewLocation.Y += Radius * FMath::Sin(RadAngle);

	//SetActorLocation(NewLocation);

	if (OrbitingCharacter)
	{
		// ���� ������Ʈ
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
		Player1Weapon->P1Attack(10);  // P1Attack �Լ� ȣ��
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
			bIsOverlapping = true;  // �浹 ���� ����
			Player1Weapon->P1Attack(10);
			// �߰� ���� �ۼ�
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
			bIsOverlapping = false;  // �浹 ���� ����
			// �߰� ���� �ۼ�
		}
	}
}

void APlayer1Skill::DestroySkill()
{

	Destroy();
}