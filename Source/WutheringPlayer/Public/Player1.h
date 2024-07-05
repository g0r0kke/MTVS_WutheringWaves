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

	// �Է� �̺�Ʈ ó�� �Լ�
	void Look(const struct FInputActionValue& inputValue);

	// �̵� �Լ� ����
	void Move(const struct FInputActionValue& inputValue);

	void InputJump(const struct FInputActionValue& inputValue);
	void InputDash(const struct FInputActionValue& inputValue);
	//void InputSkill(const struct FInputActionValue& inputValue);

	void ResetDash();

	// ���� �̺�Ʈ ó�� �Լ�
	virtual void Landed(const FHitResult& Hit) override;

	// ������ ó�� �Լ�
	void PerformRoll(bool bForward);

protected:
	FTimerHandle TimerHandle_RollMessage;
	FTimerHandle AttackDisableTimer; // ���� ��Ȱ��ȭ Ÿ�̸�
	bool bCanAttack; // ���� ���� ����
	bool bAerialAttack; // ���� ���� ����

	// �޽��� ��� �ð� ����
	void DisplayMessage(FString Message, float Duration = 1.0f);

	void UpdateRotation(const FVector& MoveDirection);

	void InputAttackStart(const FInputActionValue& inputValue);
	void InputAttackStop(const FInputActionValue& inputValue);
	//void InputAerialAttack();
	void EnableAttack(); // ���� Ȱ��ȭ �Լ�

	// ���� �ܰ� ����
	int AttackStage;
	FTimerHandle AttackComboTimer;
	FTimerHandle StrongAttackTimer;
	bool bIsStrongAttack;
	bool bIsAttackHeld;  // ���� ��ư�� ���� �������� Ȯ���ϴ� ����
	void ResetCombo();
	//void PerformStrongAttack();

	//void PerformFirstAttack();
	//void PerformSecondAttack();
	//void PerformThirdAttack();
	//void PerformFourthAttack();

	void PerformDash(const FVector& DashDirection, float DashSpeed);

	//// ĳ���� ��ȯ �Լ�
	//void SwitchToCharacter(int32 CharacterIndex);

	virtual void InputSkill(const struct FInputActionValue& inputValue);
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
