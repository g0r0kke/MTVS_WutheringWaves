// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "Player2WeaponR.generated.h"

UCLASS()
class WUTHERINGPLAYER_API APlayer2WeaponR : public AActor
{
	GENERATED_BODY()
	
public:	
	USkeletalMeshComponent* GetMeshComponent() const { return MeshCompR; }
	// Sets default values for this actor's properties
	// Sets default values for this actor's properties
	APlayer2WeaponR(const FObjectInitializer& ObjectInitializer);
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UBoxComponent* BoxComp;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=WeaponMesh)
	class USkeletalMeshComponent* MeshCompR;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
