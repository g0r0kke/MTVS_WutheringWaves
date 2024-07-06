// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AttackTypes.h"
#include "Player1Weapon.generated.h"

UCLASS()
class WUTHERINGPLAYER_API APlayer1Weapon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APlayer1Weapon();

	// 무기 스켈레탈메시
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=WeaponMesh)
	class USkeletalMeshComponent* MeshComp;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UBoxComponent* BoxComp;

	UFUNCTION()
	void OnMyBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnMyBoxEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	 // WeaponAttack 함수 선언
    UFUNCTION(Category = "PlayerAttack")
    void WeaponAttack(EAttackType AttackType);

	// P1Attack 함수 선언
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "PlayerAttack")
    void P1Attack(int32 P1ATK);
	virtual void P1Attack_Implementation(int32 P1ATK);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//UFUNCTION(BlueprintImplementableEvent, Category = "PlayerAttack")
	//void OnP1Attack(int32 P1ATK);

private:
	bool bIsOverlapping;
	//// 기본 씬 루트 컴포넌트
	//UPROPERTY()
	//class USceneComponent* SceneComponent;
};
