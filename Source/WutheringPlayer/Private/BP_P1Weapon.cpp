// Fill out your copyright notice in the Description page of Project Settings.


#include "BP_P1Weapon.h"

// Sets default values
ABP_P1Weapon::ABP_P1Weapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABP_P1Weapon::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABP_P1Weapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

