// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Player1.generated.h"

UCLASS()
class WUTHERINGPLAYER_API APlayer1 : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayer1();
	bool IsMoving; // 움직임 상태 추적
	bool IsJumping; // 점프 상태 추적

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(VisibleAnywhere, Category = Camera)
	class USpringArmComponent* springArmComp;
	UPROPERTY(VisibleAnywhere, Category = Camera)
	class UCameraComponent* tpsCamComp;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	class UInputMappingContext* imc_Player;
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	class UInputAction* inp_Look;

	void Look(const struct FInputActionValue& inputValue);

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	class UInputAction* inp_Move;
	// 이동 속도
	UPROPERTY(EditAnywhere, Category = "PlayerSetting")
	float walkSpeed = 600;
	// 이동 방향
	FVector direction;
	
	void Move(const struct FInputActionValue& inputValue);
	// 플레이어 이동 처리
	void PlayerMove();

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	class UInputAction* inp_Jump;
	// 점프 입력 이벤트 처리 함수
	void InputJump(const struct FInputActionValue& inputValue);

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	class UInputAction* inp_Dash;
	// 대쉬 입력 이벤트 처리 함수
	void InputDash(const struct FInputActionValue& inputValue);
	void ResetDash();  // 선언 추가
};
