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
	bool IsMoving; // ������ ���� ����
	bool IsJumping; // ���� ���� ����
	bool IsDashing; // �뽬 ���� ����

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
	// �̵� �ӵ�
	UPROPERTY(EditAnywhere, Category = "PlayerSetting")
	float walkSpeed = 600;
	// �̵� ����
	FVector direction;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	class UInputAction* inp_Jump;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	class UInputAction* inp_Dash;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	class UInputAction* inp_Attack;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	class UInputAction* inp_Skill;

	// �޺����� ��Ÿ��
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation)
	TObjectPtr<class UAnimMontage> ComboActionMontage;
	void ProcessComboCommand();

	// �Է� �̺�Ʈ ó�� �Լ�
	void Look(const struct FInputActionValue& InputValue);

	// �̵� �Լ� ����
	void Move(const struct FInputActionValue& InputValue);

	void InputJump(const struct FInputActionValue& InputValue);
	void InputDash(const struct FInputActionValue& InputValue);

	void ResetDash();

	// ���� �̺�Ʈ ó�� �Լ�
	virtual void Landed(const FHitResult& Hit) override;

	// ������ ó�� �Լ�
	void PerformRoll(bool bForward);

	// �÷��̾� ü��
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	int32 HP;

	// ���� ����
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Health")
	bool bIsAlive;

	// ü�� ���� �Լ�
	UFUNCTION(BlueprintCallable, Category = "Health")
	void OnHitEvent(int32 Damage);

	// ��� ó�� �Լ�
	virtual void Die();

	//class AFirstCharacter_1* P1Weapon;

protected:
	FTimerHandle TimerHandle_RollMessage;
	FTimerHandle AttackDisableTimer; // ���� ��Ȱ��ȭ Ÿ�̸�
	bool bCanAttack; // ���� ���� ����
	bool bAerialAttack; // ���� ���� ����

	// �޽��� ��� �ð� ����
	void DisplayMessage(FString Message, float Duration = 1.0f);

	void UpdateRotation(const FVector& MoveDirection);

	void InputAttackStart(const FInputActionValue& InputValue);
	void InputAttackStop(const FInputActionValue& InputValue);
	void EnableAttack(); // ���� Ȱ��ȭ �Լ�

	// ���� �ܰ� ����
	int AttackStage;
	FTimerHandle AttackComboTimer;
	FTimerHandle StrongAttackTimer;
	bool bIsStrongAttack;
	bool bIsAttackHeld;  // ���� ��ư�� ���� �������� Ȯ���ϴ� ����
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
