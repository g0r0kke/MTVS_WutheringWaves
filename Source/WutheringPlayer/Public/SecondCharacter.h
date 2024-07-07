#pragma once

#include "CoreMinimal.h"
#include "Player1.h" 
#include "GameFramework/Character.h"
#include "Engine/TimerHandle.h"
#include "Components/SceneComponent.h"
#include "Components/InputComponent.h"
#include "EnhancedInputComponent.h"
#include "SecondCharacter.generated.h"


UCLASS()
class WUTHERINGPLAYER_API ASecondCharacter : public APlayer1
{
	GENERATED_BODY()

public:
	ASecondCharacter();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// �޺� ���� �޼���
	virtual void PerformFirstAttack() override;
	virtual void PerformSecondAttack() override;
	virtual void PerformThirdAttack() override;
	virtual void PerformFourthAttack() override;

	// ���� ��� �޼���
	virtual void InputSkill(const struct FInputActionValue& inputValue) override;
	virtual void StopSkill(const struct FInputActionValue& inputValue);
	void AutoFire();


	// ���� Ʈ���̽� �߻� �޼���
	void LineTraceShoot(USceneComponent* GunComponent, float Strength = 1.0f);
		UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapon")
	class APlayer2WeaponL* P2WeaponL;

		UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapon")
	class APlayer2WeaponR* P2WeaponR;
	// �Ѿ� ����
	UPROPERTY(EditDefaultsOnly, Category = BulletFactory)
	TSubclassOf<class ABullet>bulletFactroy;
	//�浹 ���� ���� 
	UPROPERTY(EditAnywhere, Category=BulletEffect)
	class UParticleSystem* bulletEffectFactory;

	

private:
	//UPROPERTY(VisibleAnywhere, Category = "Components")
	//class APlayer2WeaponL* LeftGunMeshComp;

	//UPROPERTY(VisibleAnywhere, Category = "Components")
	//class APlayer2WeaponL* RightGunMeshComp;

	

	// ���� ���� ����


	FTimerHandle AutoFireTimerHandle;
};
