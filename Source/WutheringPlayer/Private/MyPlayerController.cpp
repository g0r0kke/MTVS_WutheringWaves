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

AMyPlayerController::AMyPlayerController()
{
	// ĳ���� �������Ʈ Ŭ���� �ε�
	static ConstructorHelpers::FClassFinder<APawn> Player1BP(TEXT("/Script/Engine.Blueprint'/Game/KHJ/Blueprints/BP_P1.BP_P1_C'"));
	if (Player1BP.Succeeded())
	{
		BP_P1 = Player1BP.Class;
		UE_LOG(LogTemp, Warning, TEXT("BP_P1 loaded successfully"));
		bIsP1Alive = true;
		P1Health = 6; // �ʱ� ü�� ����
	}

	static ConstructorHelpers::FClassFinder<APawn> Player2BP(TEXT("/Script/Engine.Blueprint'/Game/KHJ/Blueprints/BP_P2.BP_P2_C'"));
	if (Player2BP.Succeeded())
	{
		BP_P2 = Player2BP.Class;
		UE_LOG(LogTemp, Warning, TEXT("BP_P2 loaded successfully"));
		bIsP2Alive = true;
		P2Health = 10; // �ʱ� ü�� ����
	}
}

void AMyPlayerController::BeginPlay()
{
	Super::BeginPlay();
	CurrentPlayerInstance = GetPawn();

	// Enhanced Input �ý��� �ʱ�ȭ
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

	// ���� ĳ������ ü���� �����մϴ�.
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

	// ���� ������ ĳ������ ���⸦ ã�Ƽ� ����ϴ�.
	ACharacter* CurrentCharacter = Cast<ACharacter>(CurrentPlayerInstance);
	if (CurrentCharacter)
	{
		// ���Ⱑ ������ ���� �̸��� �����մϴ�.
		FName WeaponSocketName(TEXT("LeftHandSocket")); // ���� �̸��� ���ڿ��� ����

		// ���⸦ ���Ͽ��� ã�Ƽ� ����ϴ�.
		USkeletalMeshComponent* MeshComp = CurrentCharacter->GetMesh();
		if (MeshComp)
		{
			TArray<USceneComponent*> AttachedComponents;
			MeshComp->GetChildrenComponents(true, AttachedComponents);

			for (USceneComponent* Component : AttachedComponents)
			{
				if (Component && Component->GetAttachSocketName() == WeaponSocketName)
				{
					AActor* AttachedWeapon = Component->GetOwner();
					if (AttachedWeapon)
					{
						AttachedWeapon->SetActorHiddenInGame(true);
						AttachedWeapon->SetActorEnableCollision(false);
						AttachedWeapon->SetActorTickEnabled(false);
					}
				}
			}
		}
	}

	FTransform SpawnTransform = GetPawn()->GetActorTransform();
	APawn* NewCharacter = GetWorld()->SpawnActor<APawn>(NewCharacterClass, SpawnTransform);
	if (NewCharacter)
	{
		// ü�� ����
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

		// �� ĳ���� ����
		Possess(NewCharacter);
		CurrentPlayerInstance->Destroy();
		CurrentPlayerInstance = NewCharacter;
	}
}
