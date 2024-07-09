// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Player1Skill.generated.h"

class AFirstCharacter_1;
class APlayer1Weapon;

UCLASS()
class WUTHERINGPLAYER_API APlayer1Skill : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APlayer1Skill();

	// 원판 스켈레탈메시
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=SkillMesh)
	class UStaticMeshComponent* MeshComp;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class USphereComponent* SphereComp;

	void InitOrbit(AFirstCharacter_1* Character);

	UFUNCTION()
	void OnMySphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnMySphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	// 궤도를 도는 캐릭터를 저장할 변수
	AFirstCharacter_1* OrbitingCharacter;

	// 원 궤도의 반지름
	float Radius;

	// 회전 속도 (도/초)
	float Speed;

	// 회전 각도
	float Angle;

	// 스킬 파괴 함수
	void DestroySkill();

	bool bIsOverlapping;

	class APlayer1Weapon* P1Weapon;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class APlayer1Weapon> P1WeaponFactory;
};
