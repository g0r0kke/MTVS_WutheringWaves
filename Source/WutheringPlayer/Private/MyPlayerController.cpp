// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayerController.h"
#include "Engine/Engine.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "InputActionValue.h"
#include "Player1.h"
#include "FirstCharacter_1.h"
#include "SecondCharacter.h"
#include "Player1Weapon.h"
#include "Player2WeaponL.h"
#include "Player2WeaponR.h"

AMyPlayerController::AMyPlayerController()
{
	// 캐릭터 블루프린트 클래스 로드
	static ConstructorHelpers::FClassFinder<APawn> Player1BP(TEXT("/Script/Engine.Blueprint'/Game/KHJ/Blueprints/BP_P1.BP_P1_C'"));
	if (Player1BP.Succeeded())
	{
		BP_P1 = Player1BP.Class;
		UE_LOG(LogTemp, Warning, TEXT("BP_P1 loaded successfully"));
		bIsP1Alive = true;
		P1Health = 6; // 초기 체력 설정
	}

	static ConstructorHelpers::FClassFinder<APawn> Player2BP(TEXT("/Script/Engine.Blueprint'/Game/KHJ/Blueprints/BP_P2.BP_P2_C'"));
	if (Player2BP.Succeeded())
	{
		BP_P2 = Player2BP.Class;
		UE_LOG(LogTemp, Warning, TEXT("BP_P2 loaded successfully"));
		bIsP2Alive = true;
		P2Health = 10; // 초기 체력 설정
	}
}

void AMyPlayerController::BeginPlay()
{
	Super::BeginPlay();
	CurrentPlayerInstance = GetPawn();

	// Enhanced Input 시스템 초기화
	if (this)
	{
		auto Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
		if (Subsystem && InputMappingContext)
		{
			Subsystem->AddMappingContext(InputMappingContext, 0);
		}
	}
}

void AMyPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	auto EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent);
	if (EnhancedInputComponent)
	{
		EnhancedInputComponent->BindAction(inp_SwitchTo1, ETriggerEvent::Started, this, &AMyPlayerController::SwitchToCharacter1);
		EnhancedInputComponent->BindAction(inp_SwitchTo2, ETriggerEvent::Started, this, &AMyPlayerController::SwitchToCharacter2);
	}
}

void AMyPlayerController::SwitchToCharacter1()
{
	if (bIsP1Alive)
	{
		SwitchToCharacter(BP_P1);
	}
	else
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("P1 is dead!"));
		}
	}
}

void AMyPlayerController::SwitchToCharacter2()
{
	SwitchToCharacter(BP_P2);
}

void AMyPlayerController::SwitchToCharacter(TSubclassOf<APawn> NewCharacterClass)
{
	if (!NewCharacterClass || GetPawn()->GetClass() == NewCharacterClass)
	{
		return;
	}

	// 현재 캐릭터의 체력을 저장합니다.
	APlayer1* CurrentBaseCharacter = Cast<APlayer1>(CurrentPlayerInstance);
	if (CurrentBaseCharacter)
	{
		if (CurrentBaseCharacter->GetClass() == BP_P1)
		{
			P1Health = CurrentBaseCharacter->Health;
		}
		else if (CurrentBaseCharacter->GetClass() == BP_P2)
		{
			P2Health = CurrentBaseCharacter->Health;
		}
	}

	// 현재 소유한 캐릭터의 무기를 찾아서 숨깁니다.
	APlayer1* CurrentCharacter = Cast<APlayer1>(CurrentPlayerInstance);
	if (CurrentCharacter->IsA<AFirstCharacter_1>())
	{
		AFirstCharacter_1* p1 = Cast<AFirstCharacter_1>(CurrentPlayerInstance);
		if (p1->IsValidLowLevel() && p1->P1Weapon)
		{
			p1->P1Weapon->SetActorHiddenInGame(true);
			p1->P1Weapon->SetActorEnableCollision(false);
			p1->P1Weapon->SetActorTickEnabled(false);
		}
	}
	else if (CurrentCharacter->IsA<ASecondCharacter>())
	{
		ASecondCharacter* p2 = Cast<ASecondCharacter>(CurrentPlayerInstance);
		if (p2->IsValidLowLevel() && p2->P2WeaponL)
		{
			p2->P2WeaponL->SetActorHiddenInGame(true);
			p2->P2WeaponL->SetActorEnableCollision(false);
			p2->P2WeaponL->SetActorTickEnabled(false);

		}
		if (p2->IsValidLowLevel() && p2->P2WeaponR)
		{
			p2->P2WeaponR->SetActorHiddenInGame(true);
			p2->P2WeaponR->SetActorEnableCollision(false);
			p2->P2WeaponR->SetActorTickEnabled(false);
		}
	}
	//else
	//{
	//	return;
	//}

	// 현재 위치에서 새로운 위치 계산
	FVector CurrentLocation = GetPawn()->GetActorLocation();
	FVector NewLocation = CurrentLocation;
	//NewLocation.X += 30.0f;
	//NewLocation.Y += 50.0f;

	FTransform SpawnTransform;
	SpawnTransform.SetLocation(NewLocation);
	SpawnTransform.SetRotation(GetPawn()->GetActorRotation().Quaternion());
	SpawnTransform.SetScale3D(GetPawn()->GetActorScale3D());

	APawn* NewCharacter = GetWorld()->SpawnActor<APawn>(NewCharacterClass, SpawnTransform);
	if (NewCharacter)
	{
		// 체력 설정
		APlayer1* NewBaseCharacter = Cast<APlayer1>(NewCharacter);
		if (NewBaseCharacter)
		{
			if (NewCharacterClass == BP_P1)
			{
				NewBaseCharacter->Health = P1Health;
			}
			else if (NewCharacterClass == BP_P2)
			{
				NewBaseCharacter->Health = P2Health;
			}
		}

		// 새 캐릭터 스폰
		Possess(NewCharacter);
		CurrentPlayerInstance->Destroy();
		CurrentPlayerInstance = NewCharacter;
	}
}
