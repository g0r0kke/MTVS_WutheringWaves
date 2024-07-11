// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "InputAction.h" // UInputAction을 사용하기 위해 필요
#include "MyPlayerController.generated.h"

/**
 *
 */
UCLASS()
class WUTHERINGPLAYER_API AMyPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AMyPlayerController();

protected:
	virtual void BeginPlay() override;

public:
	virtual void SetupInputComponent() override;

	UPROPERTY(EditDefaultsOnly, Category = "Characters")
	TSubclassOf<APawn> BP_P1;
	UPROPERTY(EditDefaultsOnly, Category = "Characters")
	TSubclassOf<APawn> BP_P2;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	class UInputAction* inp_SwitchTo1; // 캐릭터 슬롯 1번으로 전환
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	class UInputAction* inp_SwitchTo2; // 캐릭터 슬롯 2번으로 전환
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	class UInputMappingContext* InputMappingContext;

	// 캐릭터 생존 여부
	bool bIsP1Alive;
	bool bIsP2Alive;

	// 캐릭터 체력 저장
	int32 P1HP;
	int32 P2HP;

	void SwitchToCharacter(TSubclassOf<APawn> NewCharacterClass);

private:
	APawn* CurrentPlayerInstance;

	void SwitchToCharacter1();
	void SwitchToCharacter2();
};