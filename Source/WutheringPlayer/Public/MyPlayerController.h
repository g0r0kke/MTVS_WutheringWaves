// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "InputAction.h" // UInputAction�� ����ϱ� ���� �ʿ�
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
	class UInputAction* inp_SwitchTo1; // ĳ���� ���� 1������ ��ȯ
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	class UInputAction* inp_SwitchTo2; // ĳ���� ���� 2������ ��ȯ
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	class UInputMappingContext* InputMappingContext;

	// ĳ���� ���� ����
	bool bIsP1Alive;
	bool bIsP2Alive;

	// ĳ���� ü�� ����
	int32 P1HP;
	int32 P2HP;

	void SwitchToCharacter(TSubclassOf<APawn> NewCharacterClass);

private:
	APawn* CurrentPlayerInstance;

	void SwitchToCharacter1();
	void SwitchToCharacter2();
};