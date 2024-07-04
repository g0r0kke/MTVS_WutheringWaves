// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayerController.h"
#include "Engine/Engine.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "InputActionValue.h"

AMyPlayerController::AMyPlayerController()
{
    // 캐릭터 블루프린트 클래스 로드
    static ConstructorHelpers::FClassFinder<APawn> Player1BP(TEXT("/Script/Engine.Blueprint'/Game/KHJ/Blueprints/BP_P1.BP_P1_C'"));
    if (Player1BP.Succeeded())
    {
        BP_P1 = Player1BP.Class;
        UE_LOG(LogTemp, Warning, TEXT("BP_P1 loaded successfully"));
    }
    else
    {
        BP_P1 = nullptr;
        UE_LOG(LogTemp, Warning, TEXT("Failed to load BP_P1"));
    }

    static ConstructorHelpers::FClassFinder<APawn> Player2BP(TEXT("/Script/Engine.Blueprint'/Game/KHJ/Blueprints/BP_P2.BP_P2_C'"));
    if (Player2BP.Succeeded())
    {
        BP_P2 = Player2BP.Class;
        UE_LOG(LogTemp, Warning, TEXT("BP_P2 loaded successfully"));
    }
    else
    {
        BP_P2 = nullptr;
        UE_LOG(LogTemp, Warning, TEXT("Failed to load BP_P2"));
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
    SwitchToCharacter(BP_P1);
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

    FTransform SpawnTransform = GetPawn()->GetActorTransform();
    APawn* NewCharacter = GetWorld()->SpawnActor<APawn>(NewCharacterClass, SpawnTransform);
    if (NewCharacter)
    {
        Possess(NewCharacter);
        CurrentPlayerInstance->Destroy();
        CurrentPlayerInstance = NewCharacter;
    }
}
