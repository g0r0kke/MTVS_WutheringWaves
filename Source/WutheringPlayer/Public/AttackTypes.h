// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttackTypes.generated.h"

/**
 * 
 */
class WUTHERINGPLAYER_API AttackTypes
{
public:
	AttackTypes();
	~AttackTypes();
};

UENUM(BlueprintType)
enum class EAttackType : uint8
{
    Attack1 UMETA(DisplayName = "FirstAttack"),
    Attack2 UMETA(DisplayName = "SecondAttack"),
    Attack3 UMETA(DisplayName = "ThirdAttack"),
    Attack4 UMETA(DisplayName = "FourthAttack"),
    StrongAttack UMETA(DisplayName = "Strong Attack"),
    AerialAttack UMETA(DisplayName = "Aerial Attack"),
    Skill UMETA(DisplayName = "Skill"),
    SkillDmg UMETA(DisplayName = "Skill Damage")
};
