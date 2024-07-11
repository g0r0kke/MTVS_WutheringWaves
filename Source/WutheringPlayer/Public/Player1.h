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
	bool IsDashing; // 대쉬 상태 추적

	//void HideWeapon();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Camera)
	class USpringArmComponent* CameraArm;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Camera)
	class UCameraComponent* FollowCamera;
	
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	class UInputMappingContext* imc_Player;
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	class UInputAction* inp_Look;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	class UInputAction* inp_Move;
	// 이동 속도
	UPROPERTY(EditAnywhere, Category = "PlayerSetting")
	float walkSpeed = 600;
	// 이동 방향
	FVector direction;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	class UInputAction* inp_Jump;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	class UInputAction* inp_Dash;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	class UInputAction* inp_Attack;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	class UInputAction* inp_Skill;

	// 콤보공격 몽타주
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation)
	TObjectPtr<class UAnimMontage> ComboActionMontage;
	void ProcessComboCommand();

	// 입력 이벤트 처리 함수
	void Look(const struct FInputActionValue& InputValue);

	// 이동 함수 선언
	void Move(const struct FInputActionValue& InputValue);

	void InputJump(const struct FInputActionValue& InputValue);
	void InputDash(const struct FInputActionValue& InputValue);

	void ResetDash();

	// 착지 이벤트 처리 함수
	virtual void Landed(const FHitResult& Hit) override;

	// 구르기 처리 함수
	void PerformRoll(bool bForward);

	// 플레이어 체력
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	int32 HP;

	// 생존 여부
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Health")
	bool bIsAlive;

	// 체력 감소 함수
	UFUNCTION(BlueprintCallable, Category = "Health")
	void OnHitEvent(int32 Damage);

	// 사망 처리 함수
	virtual void Die();

	//class AFirstCharacter_1* P1Weapon;

protected:
	FTimerHandle TimerHandle_RollMessage;
	FTimerHandle AttackDisableTimer; // 공격 비활성화 타이머
	bool bCanAttack; // 공격 가능 여부
	bool bAerialAttack; // 공중 공격 여부

	// 메시지 출력 시간 설정
	void DisplayMessage(FString Message, float Duration = 1.0f);

	void UpdateRotation(const FVector& MoveDirection);

	void InputAttackStart(const FInputActionValue& InputValue);
	void InputAttackStop(const FInputActionValue& InputValue);
	void EnableAttack(); // 공격 활성화 함수

	// 공격 단계 관리
	int AttackStage;
	FTimerHandle AttackComboTimer;
	FTimerHandle StrongAttackTimer;
	bool bIsStrongAttack;
	bool bIsAttackHeld;  // 공격 버튼이 눌린 상태인지 확인하는 변수
	void ResetCombo();

	void PerformDash(const FVector& DashDirection, float DashSpeed);

	virtual void InputSkill(const struct FInputActionValue& InputValue);
	virtual void InputAerialAttack();
	virtual void PerformStrongAttack();
	virtual void PerformFirstAttack();
	virtual void PerformSecondAttack();
	virtual void PerformThirdAttack();
	virtual void PerformFourthAttack();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "PlayerAttack")
	void Attack1Start();
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "PlayerAttack")
	void Attack2Start();
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "PlayerAttack")
	void Attack3Start();
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "PlayerAttack")
	void Attack4Start();

};
