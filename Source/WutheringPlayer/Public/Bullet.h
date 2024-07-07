// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Bullet.generated.h"

UCLASS()
class WUTHERINGPLAYER_API ABullet : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABullet();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
public:
	UPROPERTY(VisibleAnywhere, Category = Movement)
		class UProjectileMovementComponent* movementComp;
	UPROPERTY(VisibleAnyWhere, Category = Collision)
		class USphereComponent* collisionComp;
	UPROPERTY(VisibleAnyWhere, Category = BodyMesh)
		class UStaticMeshComponent* bodyMeshComp;
	//�Ѿ� ���� �Լ�
		void Die();
		


};
