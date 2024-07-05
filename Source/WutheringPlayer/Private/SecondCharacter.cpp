#include "SecondCharacter.h"

// Sets default values
ASecondCharacter::ASecondCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	// ���� �޽� ������Ʈ ����
	LeftGunMeshComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("LeftGunMeshComp"));
	LeftGunMeshComp->SetupAttachment(GetMesh(), TEXT("LeftHandSocket")); // �޽��� ���Ͽ� ����

	RightGunMeshComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("RightGunMeshComp"));
	RightGunMeshComp->SetupAttachment(GetMesh(), TEXT("RightHandSocket")); // �޽��� ���Ͽ� ����
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
		// �θ� Ŭ������ �Է� ���ε� ȣ��
		Super::SetupPlayerInputComponent(PlayerInputComponent);

		// ���� ��� ���ε� (Skill�� ��ü)
		PlayerInput->BindAction(inp_Skill, ETriggerEvent::Started, this, &ASecondCharacter::InputSkill);
		PlayerInput->BindAction(inp_Skill, ETriggerEvent::Completed, this, &ASecondCharacter::StopSkill);
	}
}

// �޺� ���� �޼��� ����
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

	LineTraceShoot(LeftGunMeshComp, 2.0f); // ���� ����
	LineTraceShoot(RightGunMeshComp, 2.0f); // ���� ����
}

// ���� ��� �޼��� ����
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

// ���� Ʈ���̽� �߻� �޼��� ����
void ASecondCharacter::LineTraceShoot(USceneComponent* GunMeshComponent, float Strength)
{
	FVector Start = GunMeshComponent->GetComponentLocation(); // ���� ����: ���� �޽� ��ġ
	FVector ForwardVector = GetActorForwardVector(); // ĳ������ ���� ����
	FVector End = ((ForwardVector * 5000.f * Strength) + Start); // �� ����: �������� 5000 ���� �Ÿ� * ����
	FHitResult HitResult;
	FCollisionQueryParams CollisionParams;

	bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_Visibility, CollisionParams); // ���� Ʈ���̽� ����

	if (bHit)
	{
		if (HitResult.GetActor())
		{
			UE_LOG(LogTemp, Warning, TEXT("Hit Actor: %s"), *HitResult.GetActor()->GetName()); // ���� ���� �̸� ���
		}

	}
	// ����� ���� �׸��� (�ʿ信 ���� ���� ����)
	DrawDebugLine(GetWorld(), Start, End, FColor::Green, false, 1, 0, 1);
}
