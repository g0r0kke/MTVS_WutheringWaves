// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Player1Weapon.generated.h"

UCLASS()
class WUTHERINGPLAYER_API APlayer1Weapon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APlayer1Weapon();

	// ���� ���̷�Ż�޽�
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=WeaponMesh)
	class USkeletalMeshComponent* weaponMeshComp;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UBoxComponent* BoxComp;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	//// �⺻ �� ��Ʈ ������Ʈ
	//UPROPERTY()
	//class USceneComponent* SceneComponent;
};
