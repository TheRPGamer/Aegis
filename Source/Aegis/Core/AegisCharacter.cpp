// Fill out your copyright notice in the Description page of Project Settings.

#include "Aegis.h"
#include "Core/AegisCharacter.h"
#include "Core/AegisWeapon.h" 

// Sets default values
AAegisCharacter::AAegisCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	if (GetCapsuleComponent())
	{
		GetCapsuleComponent()->bGenerateOverlapEvents = true;
	}

	if (ComboComponentClass)
	{
		ComboComponent = CreateDefaultSubobject<UAegisCharacterComboComponent>("Combo Component");
        
	}
	else
	{
		UE_LOG(AegisComboLog, Error, TEXT("Combo Component Class is invalid in %s. Fix in eidotr."), *GetHumanReadableName());
	}

	if (GuardComponentClass)
	{
        GuardComponent = CreateDefaultSubobject<UAegisCharacterGuardComponent>("GuardComponent");
	}
	else
	{
		UE_LOG(AegisGuardLog, Error, TEXT("Guard Component Class is invalid in %s. Fix in editor."), *GetHumanReadableName());
	}
}

// Called when the game starts or when spawned
void AAegisCharacter::BeginPlay()
{
	Super::BeginPlay();	

	ValidateSockets();
    
    
    
    
    

}

float AAegisCharacter::TakeDamage(float DamageAmount, const struct FDamageEvent& DamageEvent,
	AController* EventInstigagor, AActor* DamageCauser)
{
	Super::TakeDamage(DamageAmount, DamageEvent, EventInstigagor, DamageCauser); 
	SetCurrentHP(GetCurrentHP() - DamageAmount);  
	bIsInHitStun = true; 
	UE_LOG(AegisLog, Log, TEXT("Character took damage")); 
	return DamageAmount; 
}


bool AAegisCharacter::CanMove() const
{
	if (ComboComponent)
	{
		return !ComboComponent->IsInCombo(); 
	}
	return false; 
}

bool AAegisCharacter::IsInAir() const
{
	if (GetCharacterMovement())
	{
		return GetCharacterMovement()->IsFalling();

	}
	return false;
}

#if !UE_BUILD_SHIPPING
void AAegisCharacter::ValidateSockets()
{
	if (!HasAnyFlags(RF_ClassDefaultObject) && GetMesh())
	{
		if (!GetMesh()->GetSocketByName(LeftHandSocket))
		{
			UE_LOG(AegisLog, Warning, TEXT("Missing Left Hand Socket for %s. Please specify one in the skeletal mesh and set it's name in the character's properties."), *GetHumanReadableName());
		}

		if (!GetMesh()->GetSocketByName(RightHandSocket))
		{
			UE_LOG(AegisLog, Warning, TEXT("Missing Right Hand Socket for %s. Please specify one in the skeletal mesh and set it's name in the character's properties."), *GetHumanReadableName());
		}
	}
	else if (!HasAnyFlags(RF_ClassDefaultObject))
	{
		UE_LOG(AegisLog, Error, TEXT("Unexpected, missing mesh for %s."), *GetHumanReadableName());
	}
}
#endif
