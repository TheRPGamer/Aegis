// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "AegisCharacter.generated.h"
/**
* AAegisCharacter is an ACharacter with the addition of an HP field.
* All characters from Aegis will inherit from this class. Be it NPCs
* Players or Enemies.
*/

UCLASS()
class AEGIS_API AAegisCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	/* Sets default values for this character's properties */
	AAegisCharacter();

protected:
	/* Called when the game starts or when spawned */
	virtual void BeginPlay() override;

public:	
	/*Called every frame*/
	virtual void Tick(float DeltaTime) override;

	/*Called to bind functionality to input*/
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual float TakeDamage(float DamageAmount, const struct FDamageEvent& DamageEvent,
		AController* EventInstigagor, AActor* DamageCauser) override; 
	
	FORCEINLINE float GetCurrentHP() const
	{
		return CurrentHP; 
	}

	FORCEINLINE void SetCurrentHP(float newValue)
	{
		CurrentHP = newValue; 
	}

	FORCEINLINE float GetMaxHP() const
	{
		return MaxHP; 
	}


	FORCEINLINE bool IsInAir() const
	{
		if (GetCharacterMovement())
		{
			return GetCharacterMovement()->IsFalling();
			
		}
		return false;
	}

	FORCEINLINE bool IsInSuperMode() const
	{
		return bIsInSuperMode;
	}
	FORCEINLINE bool IsInLockOn() const
	{
		return bIsInLockOn;
	}

	FORCEINLINE bool IsInHitStun() const
	{
		return bIsInHitStun; 
	}

	FORCEINLINE bool IsInGroundGuard() const
	{
		return bIsInGroundGuard; 
	}


	FORCEINLINE bool IsInAirGuard() const
	{
		return bIsInAirGuard; 
	}

	FORCEINLINE bool IsDead() const
	{
		return (CurrentHP <= 0.0f); 
	}
	FORCEINLINE bool CanUseMeleeAttack() const
	{
		return !bIsInHitStun && !bIsInGroundMeleeChargeUp && bIsInGroundMeleeAttack;
	}

	FORCEINLINE bool CanUseGuard() const
	{
		return !bIsInHitStun && !CanUseMeleeAttack(); 
	}

	FORCEINLINE void ResetGroundMeleeAttackState()
	{
		bIsInGroundMeleeAttack = false; 
		bIsInGroundMeleeChargeUp = false; 
	}

	FORCEINLINE void ResetGroundGuardState()
	{

	}

	
	
protected: 
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "HP", meta = (AllowPrivateAccess = "true"))
	float MaxHP = 0.0f; 
	
	float CurrentHP = 0.0f;


	bool bIsInLockOn = false;
	bool bIsInSuperMode = false;
	bool bIsInHitStun = false;
	
	bool bIsInGroundMeleeChargeUp = false; 
	bool bIsInGroundMeleeAttack = false; 
	bool bIsInAirMeleeChargeUp = false; 
	bool bIsInAirMeleeAttack = false; 

	bool bIsInGroundGuard = false; 
	bool bIsInAirGuard = false; 


};
