// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Player1.h"
#include "GameFramework/Character.h"
#include "Player1Weapon.h"
#include "FirstCharacter_1.generated.h"

UCLASS()
class WUTHERINGPLAYER_API AFirstCharacter_1 : public APlayer1
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AFirstCharacter_1();

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
	virtual void Die() override;

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Attack")
	void SkillStart();
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Attack")
	void AerialAttackStart();
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Attack")
	void StrongAttackStart();

	class APlayer1Weapon* P1Weapon;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class APlayer1Skill> P1SkillFactory;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon")
	TSubclassOf<class APlayer1Weapon> P1WeaponFactory;
};
