// Fill out your copyright notice in the Description page of Project Settings.

#include "Aegis.h"
#include "AegisCharacter.h"
#include "AegisWeapon.h" 


// Sets default values
AAegisCharacter::AAegisCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	if (GetCapsuleComponent())
	{
		GetCapsuleComponent()->bGenerateOverlapEvents = true;
	}
}

// Called when the game starts or when spawned
void AAegisCharacter::BeginPlay()
{
	Super::BeginPlay();	

	
#if !UE_BUILD_SHIPPING
	ValidateSockets();
#endif
}

// Called every frame
void AAegisCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AAegisCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

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
