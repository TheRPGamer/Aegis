// Fill out your copyright notice in the Description page of Project Settings.

#include "Aegis.h"
#include "Core/Input/AegisActionInputBufferComponent.h"
#include "Core/Weapons/AegisWeapon.h"
#include "Core/Characters/AegisCharacter.h"

// Sets default values
AAegisCharacter::AAegisCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	if (GetCapsuleComponent())
	{
		GetCapsuleComponent()->bGenerateOverlapEvents = true;
	}
    InputBufferComponent = CreateDefaultSubobject<UAegisActionInputBufferComponent>("Input Buffer ");
}

void AAegisCharacter::PostInitProperties()
{
    Super::PostInitProperties();
    //Creates components from TSubclassOf Properties set in Editor
    CreatePostInitComponents();

}

// Called when the game starts or when spawned
void AAegisCharacter::BeginPlay()
{
	Super::BeginPlay();	

	ValidateSockets();
    ValidateCharacterComponents();
    
    
    
    

}

float AAegisCharacter::TakeDamage(float DamageAmount, const struct FDamageEvent& DamageEvent,
	AController* EventInstigagor, AActor* DamageCauser)
{
	Super::TakeDamage(DamageAmount, DamageEvent, EventInstigagor, DamageCauser); 
	//SetCurrentHP(GetCurrentHP() - DamageAmount);
	//bIsInHitStun = true;
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

void AAegisCharacter::CreatePostInitComponents()
{
    if (ComboComponentClass)
    {
        ComboComponent = NewObject<UAegisCharacterComboComponent>(this, *ComboComponentClass);
        
    }
    else
    {
        
    }
    if(GuardComponentClass)
    {
        GuardComponent = NewObject<UAegisCharacterGuardComponent>(this, *GuardComponentClass);
        
    }
    else
    {
        
    }
}

void AAegisCharacter::ValidateCharacterComponents()
{
    checkf(ComboComponent, TEXT("ComboComponent for is null in AegisCharacter"));
    checkf(GuardComponent, TEXT("Guard Component s null in AegisCharacter"));
}

