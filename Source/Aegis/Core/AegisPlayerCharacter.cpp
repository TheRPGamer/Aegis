// Fill out your copyright notice in the Description page of Project Settings.

#include "Aegis.h"
#include "Core/AegisPlayerCharacter.h"
#include "Core/AegisWeapon.h"

AAegisPlayerCharacter::AAegisPlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = true; 
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
	ThirdPersonSpringArm = CreateDefaultSubobject<USpringArmComponent>("ThirdPersonSpringArm");
	if (ThirdPersonSpringArm)
	{
		ThirdPersonSpringArm->SetupAttachment(RootComponent); 
		ThirdPersonSpringArm->TargetArmLength = 300.0f; 
		ThirdPersonSpringArm->bUsePawnControlRotation = true; 
		ThirdPersonSpringArm->bAbsoluteRotation = false; 
		ThirdPersonSpringArm->bAbsoluteLocation = false; 
		ThirdPersonSpringArm->bInheritYaw = false;
		ThirdPersonSpringArm->SetRelativeLocation(FVector(0.0f, 0.0f, 250.0f)); 
	}
	ThirdPersonCamera = CreateDefaultSubobject<UCameraComponent>("ThirdPersonCamera"); 
	if (ThirdPersonCamera)
	{
		ThirdPersonCamera->SetupAttachment(ThirdPersonSpringArm, USpringArmComponent::SocketName); 
		ThirdPersonCamera->SetProjectionMode(ECameraProjectionMode::Perspective); 
		ThirdPersonCamera->bAbsoluteRotation = false; 
		ThirdPersonCamera->bUsePawnControlRotation = false; 
		ThirdPersonCamera->SetFieldOfView(120.0f); 
		ThirdPersonCamera->SetRelativeRotation(FRotator(-25.0f, 0.0f, 0.0f)); 
	}
	if (GetCharacterMovement())
	{
		GetCharacterMovement()->bOrientRotationToMovement = true; 
	}

}

void AAegisPlayerCharacter::BeginPlay()
{
	Super::BeginPlay(); 
	if (EquippedWeaponClass && GetMesh() && GetWorld())
	{
		FActorSpawnParameters weaponSpawnInfo;
		weaponSpawnInfo.Owner = this;


		EquippedWeapon = GetWorld()->SpawnActor<AAegisWeapon>(EquippedWeaponClass, weaponSpawnInfo);
		if (EquippedWeapon)
		{
			EquippedWeapon->SetOwner(this); 
			EquippedWeapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, RightHandSocket);
		}
	}
}

void AAegisPlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime); 
}

void AAegisPlayerCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent); 
	if (PlayerInputComponent)
	{
		PlayerInputComponent->BindAxis("MoveForward", this, &AAegisPlayerCharacter::MoveForward); 
		PlayerInputComponent->BindAxis("MoveRight", this, &AAegisPlayerCharacter::MoveRight); 
		
		PlayerInputComponent->BindAction("MeleeAttack", IE_Pressed, this, &AAegisPlayerCharacter::OnMeleeAttackPressed); 
		PlayerInputComponent->BindAction("MeleeAttack", IE_Released, this, &AAegisPlayerCharacter::OnMeleeAttackReleased); 
		
		PlayerInputComponent->BindAction("LockOn", IE_Pressed, this, &AAegisPlayerCharacter::OnLockOnPressed); 
		PlayerInputComponent->BindAction("LockOn", IE_Released, this, &AAegisPlayerCharacter::OnLockOnReleased); 
		
		PlayerInputComponent->BindAction("SuperMode", IE_Pressed, this, &AAegisPlayerCharacter::OnSuperModePressed);
		PlayerInputComponent->BindAction("SuperMode", IE_Released, this, &AAegisPlayerCharacter::OnSuperModeReleased); 


		PlayerInputComponent->BindAction("Guard", IE_Pressed, this, &AAegisPlayerCharacter::OnGuardPressed);
		PlayerInputComponent->BindAction("Guard", IE_Released, this, &AAegisPlayerCharacter::OnGuardReleased);

		PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump); 

	}
	else
	{
		UE_LOG(AegisLog, Warning, TEXT("Player has no input component!")); 
	}
}

void AAegisPlayerCharacter::MoveForward(float Value)
{
	if ((Value != 0.0f) && CanMove() && ThirdPersonCamera)
	{
		FVector charForwward = ThirdPersonCamera->GetForwardVector(); 
		charForwward.Z = 0.0f; 

		charForwward.Normalize(); 
		AddMovementInput(charForwward, Value); 
	}
}
void AAegisPlayerCharacter::MoveRight(float Value)
{
	if ((Value != 0.0f) && CanMove() && ThirdPersonCamera)
	{
		FVector charRight = ThirdPersonCamera->GetRightVector(); 
		charRight.Z = 0.0f;
		charRight.Normalize(); 
		AddMovementInput(charRight, Value); 
	}
}

void AAegisPlayerCharacter::OnMeleeAttackPressed()
{
	if (CanUseMeleeAttack())
	{
		bIsInGroundMeleeChargeUp = true;
		
	}
}

void AAegisPlayerCharacter::OnMeleeAttackReleased()
{
	bIsInGroundMeleeChargeUp = false; 
	if (CanUseMeleeAttack())
	{
		bIsInGroundMeleeAttack = true; 
		
	}

}

void AAegisPlayerCharacter::OnLockOnPressed()
{
	bIsInLockOn = true; 
	if (GetCharacterMovement())
	{
		GetCharacterMovement()->bOrientRotationToMovement = false;
	}
}
void AAegisPlayerCharacter::OnLockOnReleased()
{
	UE_LOG(AegisLog, Log, TEXT("Lock On Released")); 
	bIsInLockOn = false; 
	if (GetCharacterMovement())
	{
		GetCharacterMovement()->bOrientRotationToMovement = true; 
	}
}
void AAegisPlayerCharacter::OnSuperModePressed()
{
	UE_LOG(AegisLog, Log, TEXT("Super Mode Pressed")); 
}

void AAegisPlayerCharacter::OnSuperModeReleased()
{
	UE_LOG(AegisLog, Log, TEXT("Super Mode Released")); 
	if (bIsInSuperMode)
	{
		bIsInSuperMode = false; 
	}
	else
	{
		bIsInSuperMode = true; 
	}
}

void AAegisPlayerCharacter::OnGuardPressed()
{
	if (CanUseGuard())
	{
		bIsInGroundGuard = true; 
	}
}

void AAegisPlayerCharacter::OnGuardReleased()
{
	bIsInGroundGuard = false; 
}

bool AAegisPlayerCharacter::IsInputDirectionTowardLockOnTarget()
{
	float inputDirectionToTargetAngle = CalculateAngleBetweenInputDirectionAndLockOnTarget(); 
	if ((inputDirectionToTargetAngle >= 0.0f) && (inputDirectionToTargetAngle <= InputDirectionToLockOnTargetAngleTolerance))
	{
		return true; 
	}
	return false; 
	
}

bool AAegisPlayerCharacter::IsInputDirectionOppositeLockOnTarget()
{
	float inputDirectionToTargetAngle = CalculateAngleBetweenInputDirectionAndLockOnTarget();
	if ((inputDirectionToTargetAngle >= 180.0f - InputDirectionToLockOnTargetAngleTolerance) && 
		(inputDirectionToTargetAngle <= 180.0f))
	{
		return true;
	}
	return false;
}

float AAegisPlayerCharacter::CalculateAngleBetweenInputDirectionAndLockOnTarget()
{
	//Get the character's input direction in X-Y plane 
	FVector charVelocity = GetVelocity();
	charVelocity.Z = 0.0f;
	charVelocity.Normalize();

	//Get character's current forward vector which will be towards the lock on target
	FVector  charForward = GetActorForwardVector();
	charForward.Z = 0.0f;
	charForward.Normalize();

	float dotProduct = FVector::DotProduct(charVelocity, charForward);
	float angleInRadians = FMath::Acos(dotProduct); 
	
	return FMath::RadiansToDegrees(angleInRadians); 
}

float AAegisPlayerCharacter::GetMeleeAttackInputTimeDown() const
{
	auto playerController = Cast<APlayerController>(GetController()); 
	if (playerController)
	{
		return playerController->GetInputKeyTimeDown(FKey(FName("MeleeAttack"))); 
	}
	return -1.0f; 
}


float AAegisPlayerCharacter::GetGuardInputTimeDown() const
{
	auto playerController = Cast<APlayerController>(GetController());
	if (playerController)
	{
		return playerController->GetInputKeyTimeDown(FKey(FName("Guard")));
	}
	return -1.0f;
}

int32 AAegisPlayerCharacter::DetermineGuardLevel()
{
	float guardTimeDown = GetGuardInputTimeDown(); 
	auto world = GetWorld(); 
	if (world)
	{
		float deltaTime = world->GetDeltaSeconds(); 
		float framesFromBeginGuard = guardTimeDown / deltaTime; 
		if (framesFromBeginGuard <= Level3GuardFrameThreshold)
		{
			return 3; 
		}
		else if (framesFromBeginGuard > Level3GuardFrameThreshold && framesFromBeginGuard < Level1GuardFrameThreshold)
		{
			return 2;
		}
		else if (framesFromBeginGuard >= Level1GuardFrameThreshold)
		{
			return 1; 
		}
	}
	return 0; 
}


void AAegisPlayerCharacter::GuardLevel0(float OriginalDamageTaken)
{
	SetCurrentHP(GetCurrentHP() - OriginalDamageTaken);
	bIsInHitStun = true;
}

void AAegisPlayerCharacter::GuardLevel1(float OriginalDamageTaken)
{
	SetCurrentHP(GetCurrentHP() - OriginalDamageTaken / 2.0f); 
	UE_LOG(AegisLog, Log, TEXT("Level 1 Guard Performed"));

}


void AAegisPlayerCharacter::GuardLevel2(float OriginalDamageTaken)
{
	SetCurrentHP(GetCurrentHP() - OriginalDamageTaken / 4.0f); 
	UE_LOG(AegisLog, Log, TEXT("Level 2 Guard Performed"));

}


void AAegisPlayerCharacter::GuardLevel3()
{
	UE_LOG(AegisLog, Log, TEXT("Level 3 Guard Performed"));
}

float AAegisPlayerCharacter::TakeDamage(float DamageAmount, const struct FDamageEvent& DamageEvent,
	AController* EventInstigagor, AActor* DamageCauser)
{
	Super::TakeDamage(DamageAmount, DamageEvent, EventInstigagor, DamageCauser);
	if (IsInGroundGuard())
	{
		int32 guardLevel = DetermineGuardLevel();
		switch (guardLevel)
		{
			case 1: 
			{
				GuardLevel1(DamageAmount); 
				break; 
			}
			case 2: 
			{
				GuardLevel2(DamageAmount); 
				break;
			}
			case 3:
			{
				GuardLevel3(); 
				break; 
			}
		}
		GuardLevel0(DamageAmount); 
		return DamageAmount; 
	}
	
	return DamageAmount;
}

