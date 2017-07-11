// Fill out your copyright notice in the Description page of Project Settings.

#include "Aegis.h"
#include "AegisPlayerCharacter.h"

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

AAegisPlayerCharacter::~AAegisPlayerCharacter()
{

}
void AAegisPlayerCharacter::BeginPlay()
{
	Super::BeginPlay(); 
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
	if (!CanUseMeleeAttack())
	{
		return; 
	}
	if (IsInLockOn() && IsInputDirectionTowardLockOnTarget())
	{
		if (IsInSuperMode() && IsInAir())
		{
			UE_LOG(AegisLog, Log, TEXT("Super Air Toward Melee Pressed")); 
		}
		else if (IsInSuperMode())
		{
			UE_LOG(AegisLog, Log, TEXT("Super Ground Toward Melee Pressed")); 
		}
		else if (IsInAir())
		{
			UE_LOG(AegisLog, Log, TEXT("Normal Air Toward Melee Pressed")); 
		}
		else if (!IsInSuperMode() && !IsInAir())
		{
			UE_LOG(AegisLog, Log, TEXT("Normal Ground Toward Melee Pressed")); 
		}
	}
	else if (IsInLockOn() && IsInputDirectionOppositeLockOnTarget())
	{
		if (IsInSuperMode() && IsInAir())
		{
			UE_LOG(AegisLog, Log, TEXT("Super Air Back Melee Pressed"));
		}
		else if (IsInSuperMode())
		{
			UE_LOG(AegisLog, Log, TEXT("Super Ground Back Melee Pressed"));
		}
		else if (IsInAir())
		{
			UE_LOG(AegisLog, Log, TEXT("Normal Air Back Melee Pressed"));
		}
		else if (!IsInSuperMode() && !IsInAir())
		{
			UE_LOG(AegisLog, Log, TEXT("Normal Ground Back Melee Pressed"));
		}
	}
	else
	{
		if (IsInSuperMode() && IsInAir())
		{
			UE_LOG(AegisLog, Log, TEXT("Super Air Neutral Melee Pressed"));
		}
		else if (IsInSuperMode())
		{
			UE_LOG(AegisLog, Log, TEXT("Super Ground Neutral Melee Pressed"));
		}
		else if (IsInAir())
		{
			UE_LOG(AegisLog, Log, TEXT("Normal Air Neutral Melee Pressed"));
		}
		else if (!IsInSuperMode() && !IsInAir())
		{
			UE_LOG(AegisLog, Log, TEXT("Normal Ground Neutral Melee Pressed"));
			bIsInGroundMeleeChargeUp = true; 
		}
	}

}

void AAegisPlayerCharacter::OnMeleeAttackReleased()
{
	bIsInGroundMeleeChargeUp = false; 
	if (!CanUseMeleeAttack())
	{
		return;
	}
	bIsInGroundMeleeAttack = true; 
	if (IsInLockOn() && IsInputDirectionTowardLockOnTarget())
	{
		if (IsInSuperMode() && IsInAir())
		{
			UE_LOG(AegisLog, Log, TEXT("Super Air Toward Melee Released"));
		}
		else if (IsInSuperMode())
		{
			UE_LOG(AegisLog, Log, TEXT("Super Ground Toward Melee Released"));
		}
		else if (IsInAir())
		{
			UE_LOG(AegisLog, Log, TEXT("Normal Air Toward Melee Released"));
		}
		else if (!IsInSuperMode() && !IsInAir())
		{
			UE_LOG(AegisLog, Log, TEXT("Normal Ground Toward Melee Released"));
		}
	}
	else if (IsInLockOn() && IsInputDirectionOppositeLockOnTarget())
	{
		if (IsInSuperMode() && IsInAir())
		{
			UE_LOG(AegisLog, Log, TEXT("Super Air Back Melee Released"));
		}
		else if (IsInSuperMode())
		{
			UE_LOG(AegisLog, Log, TEXT("Super Ground Back Melee Released"));
		}
		else if (IsInAir())
		{
			UE_LOG(AegisLog, Log, TEXT("Normal Air Back Melee Released"));
		}
		else if (!IsInSuperMode() && !IsInAir())
		{
			UE_LOG(AegisLog, Log, TEXT("Normal Ground Back Melee Released"));
		}
	}
	else
	{
		if (IsInSuperMode() && IsInAir())
		{
			UE_LOG(AegisLog, Log, TEXT("Super Air Neutral Melee Released"));
		}
		else if (IsInSuperMode())
		{
			UE_LOG(AegisLog, Log, TEXT("Super Ground Neutral Melee Released"));
		}
		else if (IsInAir())
		{
			UE_LOG(AegisLog, Log, TEXT("Normal Air Neutral Melee Released"));
		}
		else if (!IsInSuperMode() && !IsInAir())
		{
			float chargeTime = GetMeleeAttackInputTimeDown(); 
			if (chargeTime >= 2.0f && chargeTime < 2.3f)
			{
				UE_LOG(AegisLog, Log, TEXT("Perfect Charge Attack"));
			}
			else if (chargeTime >= 2.3f)
			{
				UE_LOG(AegisLog, Log, TEXT("Regular charge attack"))
			}
			UE_LOG(AegisLog, Log, TEXT("Normal Ground Neutral Melee Released"));
		}
	}  

}

void AAegisPlayerCharacter::OnLockOnPressed()
{
	UE_LOG(AegisLog, Log, TEXT("Lock On Pressed")); 
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

float AAegisPlayerCharacter::GetMeleeAttackInputTimeDown()
{
	auto playerController = Cast<APlayerController>(GetController()); 
	if (playerController)
	{
		return playerController->GetInputKeyTimeDown(FKey(FName("MeleeAttack"))); 
	}
	return -1.0f; 
}
