// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Player2WeaponL.generated.h"

UCLASS()
class WUTHERINGPLAYER_API APlayer2WeaponL : public AActor
{
	GENERATED_BODY()
	
public:	
	USkeletalMeshComponent* GetMeshComponent() const { return MeshCompL; }
	
	// Sets default values for this actor's properties
	APlayer2WeaponL(const FObjectInitializer& ObjectInitializer);
	// ¹«±â ½ºÄÌ·¹Å»¸Þ½Ã
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=WeaponMesh)
	class USkeletalMeshComponent* MeshCompL;

	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UBoxComponent* BoxComp;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;



};
