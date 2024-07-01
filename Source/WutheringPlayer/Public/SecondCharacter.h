// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Player1.h"
#include "GameFramework/Character.h"
#include "SecondCharacter.generated.h"

UCLASS()
class WUTHERINGPLAYER_API ASecondCharacter : public APlayer1
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASecondCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void InputSkill(const struct FInputActionValue& inputValue) override;
	virtual void InputAerialAttack() override;
	virtual void PerformStrongAttack() override;
	virtual void PerformFirstAttack() override;
	virtual void PerformSecondAttack() override;
	virtual void PerformThirdAttack() override;
	virtual void PerformFourthAttack() override;
};
