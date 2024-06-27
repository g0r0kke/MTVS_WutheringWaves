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

	void Look(const struct FInputActionValue& inputValue);

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	class UInputAction* inp_Move;
	// �̵� �ӵ�
	UPROPERTY(EditAnywhere, Category = "PlayerSetting")
	float walkSpeed = 600;
	// �̵� ����
	FVector direction;

	void Move(const struct FInputActionValue& inputValue);

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	class UInputAction* inp_Jump;
	// ���� �Է� �̺�Ʈ ó�� �Լ�
	void InputJump(const struct FInputActionValue& inputValue);

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	class UInputAction* inp_Dash;
	// �뽬 �Է� �̺�Ʈ ó�� �Լ�
	void InputDash(const struct FInputActionValue& inputValue);
	void ResetDash();  // ���� �߰�

	// ���� �̺�Ʈ ó�� �Լ�
	virtual void Landed(const FHitResult& Hit) override;

	// ������ ó�� �Լ�
	void PerformRoll(bool bForward);

	UPROPERTY(VisibleAnywhere, Category = Component)
	class UPlayerBaseComponent* playerMove;

private:
	FTimerHandle TimerHandle_RollMessage;
	void DisplayRollMessage(FString Message);

	void UpdateRotation(const FVector& MoveDirection);
};
