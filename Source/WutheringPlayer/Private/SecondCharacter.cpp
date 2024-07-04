#include "SecondCharacter.h"

// Sets default values
ASecondCharacter::ASecondCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	// 권총 메쉬 컴포넌트 설정
	LeftGunMeshComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("LeftGunMeshComp"));
	LeftGunMeshComp->SetupAttachment(GetMesh(), TEXT("LeftHandSocket")); // 메쉬의 소켓에 부착

	RightGunMeshComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("RightGunMeshComp"));
	RightGunMeshComp->SetupAttachment(GetMesh(), TEXT("RightHandSocket")); // 메쉬의 소켓에 부착
}

// Called when the game starts or when spawned
void ASecondCharacter::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ASecondCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ASecondCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	auto PlayerInput = CastChecked<UEnhancedInputComponent>(PlayerInputComponent);
	if (PlayerInput)
	{
		// 부모 클래스의 입력 바인딩 호출
		Super::SetupPlayerInputComponent(PlayerInputComponent);

		// 연발 사격 바인딩 (Skill로 대체)
		PlayerInput->BindAction(inp_Skill, ETriggerEvent::Started, this, &ASecondCharacter::InputSkill);
		PlayerInput->BindAction(inp_Skill, ETriggerEvent::Completed, this, &ASecondCharacter::StopSkill);
	}
}

// 콤보 공격 메서드 구현
void ASecondCharacter::PerformFirstAttack()
{
	DisplayMessage("P2 First Attack!");

	LineTraceShoot(LeftGunMeshComp);
}

void ASecondCharacter::PerformSecondAttack()
{
	DisplayMessage("P2 Second Attack!");

	LineTraceShoot(RightGunMeshComp);
}

void ASecondCharacter::PerformThirdAttack()
{
	DisplayMessage("P2 Third Attack!");

	LineTraceShoot(LeftGunMeshComp);
	LineTraceShoot(RightGunMeshComp);
}

void ASecondCharacter::PerformFourthAttack()
{
	DisplayMessage("P2 Fourth Attack!");

	LineTraceShoot(LeftGunMeshComp, 2.0f); // 강한 공격
	LineTraceShoot(RightGunMeshComp, 2.0f); // 강한 공격
}

// 연발 사격 메서드 구현
void ASecondCharacter::InputSkill(const struct FInputActionValue& inputValue)
{
	DisplayMessage("P2 Skill Attack!");
	GetWorld()->GetTimerManager().SetTimer(AutoFireTimerHandle, this, &ASecondCharacter::AutoFire, 0.1f, true);
	PerformDash(GetActorForwardVector(), -3000.0f);
}

void ASecondCharacter::StopSkill(const struct FInputActionValue& inputValue)
{
	DisplayMessage("P2 Stop Skill!");
	GetWorld()->GetTimerManager().ClearTimer(AutoFireTimerHandle);

}
void ASecondCharacter::AutoFire()
{
	LineTraceShoot(LeftGunMeshComp);
	LineTraceShoot(RightGunMeshComp);
}

// 라인 트레이스 발사 메서드 구현
void ASecondCharacter::LineTraceShoot(USceneComponent* GunMeshComponent, float Strength)
{
	FVector Start = GunMeshComponent->GetComponentLocation(); // 시작 지점: 권총 메쉬 위치
	FVector ForwardVector = GetActorForwardVector(); // 캐릭터의 전방 벡터
	FVector End = ((ForwardVector * 5000.f * Strength) + Start); // 끝 지점: 전방으로 5000 유닛 거리 * 강도
	FHitResult HitResult;
	FCollisionQueryParams CollisionParams;

	bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_Visibility, CollisionParams); // 라인 트레이스 실행

	if (bHit)
	{
		if (HitResult.GetActor())
		{
			UE_LOG(LogTemp, Warning, TEXT("Hit Actor: %s"), *HitResult.GetActor()->GetName()); // 맞은 액터 이름 출력
		}

	}
	// 디버그 라인 그리기 (필요에 따라 제거 가능)
	DrawDebugLine(GetWorld(), Start, End, FColor::Green, false, 1, 0, 1);
}
