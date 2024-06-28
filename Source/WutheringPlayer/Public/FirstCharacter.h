// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Player1.h"
#include "GameFramework/Character.h"
#include "FirstCharacter.generated.h"

UCLASS()
class WUTHERINGPLAYER_API AFirstCharacter : public APlayer1
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AFirstCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
