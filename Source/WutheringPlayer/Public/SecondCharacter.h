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

	// 콤보 공격 메서드
	virtual void PerformFirstAttack() override;
	virtual void PerformSecondAttack() override;
	virtual void PerformThirdAttack() override;
	virtual void PerformFourthAttack() override;

	// 연발 사격 메서드
	virtual void InputSkill(const struct FInputActionValue& inputValue) override;
	virtual void StopSkill(const struct FInputActionValue& inputValue);
	void AutoFire();


	// 라인 트레이스 발사 메서드
	void LineTraceShoot(USceneComponent* GunComponent, float Strength = 1.0f);
		UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapon")
	class APlayer2WeaponL* P2WeaponL;

		UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapon")
	class APlayer2WeaponR* P2WeaponR;
	// 총알 공장
	UPROPERTY(EditDefaultsOnly, Category = BulletFactory)
	TSubclassOf<class ABullet>bulletFactroy;
	//충돌 파편 공장 
	UPROPERTY(EditAnywhere, Category=BulletEffect)
	class UParticleSystem* bulletEffectFactory;

	

private:
	//UPROPERTY(VisibleAnywhere, Category = "Components")
	//class APlayer2WeaponL* LeftGunMeshComp;

	//UPROPERTY(VisibleAnywhere, Category = "Components")
	//class APlayer2WeaponL* RightGunMeshComp;

	

	// 전역 변수 선언


	FTimerHandle AutoFireTimerHandle;
};
