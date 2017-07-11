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

	/*Function called when AegisCharacter is damaged*/
	virtual float TakeDamage(float DamageAmount, const struct FDamageEvent& DamageEvent,
		AController* EventInstigagor, AActor* DamageCauser) override; 
	UFUNCTION(BlueprintCallable)
		FORCEINLINE float GetCurrentHP() const { return CurrentHP; }
	
	FORCEINLINE UFUNCTION(BlueprintCallable)
	void SetCurrentHP(float newValue) { CurrentHP = newValue; }

	/*Returns character's max HP*/
	UFUNCTION(BlueprintCallable)
	FORCEINLINE float GetMaxHP() const { return MaxHP; }

	/*Returns true if the character is currently in the air*/
	UFUNCTION(BlueprintCallable)
	FORCEINLINE bool IsInAir() const
	{
		if (GetCharacterMovement())
		{
			return GetCharacterMovement()->IsFalling();
			
		}
		return false;
	}

	/*Returns true if character is currently in Super Mode*/
	UFUNCTION(BlueprintCallable)
	FORCEINLINE bool IsInSuperMode() const { return bIsInSuperMode; }
	
	/*Returns true if character is in the lock on state*/
	UFUNCTION(BlueprintCallable)
	FORCEINLINE bool IsInLockOn() const { return bIsInLockOn;}
	
	/*Returns true if character is currently in Hit Stun State*/
	UFUNCTION(BlueprintCallable)
	FORCEINLINE bool IsInHitStun() const{	return bIsInHitStun; }
	
	/*Returns true if character is performing Melee Attack on the ground*/
	UFUNCTION(BlueprintCallable)
	FORCEINLINE bool IsInGroundMeleeAttack() const { return bIsInGroundMeleeAttack; }
	
	/*Returns true if character is performing Melee Attack in the air*/
	UFUNCTION(BlueprintCallable)
	FORCEINLINE bool IsInAirMeleeAttack() const { return bIsInAirMeleeAttack; }
	
	/*Returns true if character is Guarding on the ground*/
	UFUNCTION(BlueprintCallable)
	FORCEINLINE bool IsInGroundGuard() const { return bIsInGroundGuard; }
	
	/*Returns true if character is guarding in the air*/
	UFUNCTION(BlueprintCallable)
	FORCEINLINE bool IsInAirGuard() const { return bIsInAirGuard; }

	/*Returns true if character is in the Dead State*/
	UFUNCTION(BlueprintCallable)
	FORCEINLINE bool IsDead() const { return (CurrentHP <= 0.0f); }
	
	/*Returns true if the character's state allows for the character to perform Melee Attacks*/
	UFUNCTION(BlueprintCallable)
	FORCEINLINE bool CanUseMeleeAttack() const { return !bIsInHitStun && !bIsInGroundMeleeChargeUp && !bIsInGroundMeleeAttack;}
	
	/*Returns true if the character's state allows for the character to Guard*/
	UFUNCTION(BlueprintCallable)
	FORCEINLINE bool CanUseGuard() const { return !bIsInHitStun && !CanUseMeleeAttack(); }
	
	/*Returns true if the character's current state allows for any movement*/
	UFUNCTION(BlueprintCallable)
	FORCEINLINE bool CanMove() const
	{
		return !bIsInHitStun && !bIsInGroundMeleeAttack && !bIsInAirMeleeAttack &&
			!bIsInGroundGuard && !bIsInAirGuard; 
	}
	
	/*Resets Ground Charge Up and Melee Attack States to false*/
	FORCEINLINE UFUNCTION(BlueprintCallable)
	void ResetGroundMeleeAttackState()
	{
		bIsInGroundMeleeAttack = false; 
		bIsInGroundMeleeChargeUp = false; 
	}
	
	/*Resets GroundGuardState to false*/
	FORCEINLINE UFUNCTION(BlueprintCallable)
	void ResetGroundGuardState() { bIsInGroundGuard = false; }
	
	/**
	* Function called while character is in the Idle State to reset
	* Melee Attack, Guard State and Hit Stun States.
	*/
	FORCEINLINE UFUNCTION(BlueprintCallable)
	void IdleStateReset()
	{
		ResetGroundMeleeAttackState(); 
		ResetGroundGuardState(); 
	}

	
	
protected: 
	/*Character's maximum HP. Must be > 0.0f*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "HP", meta = (AllowPrivateAccess = "true"))
	float MaxHP = 0.0f; 
	
	/*Character's current HP. Dies if < 0.0f*/
	float CurrentHP = 0.0f;

	/*True if character is in the lock on state*/
	bool bIsInLockOn = false;

	/*True if character is in Super Mode*/
	bool bIsInSuperMode = false;

	/*True if character is currently in hit stun*/
	bool bIsInHitStun = false;
	
	/*True if character is currently charging up a melee attack on ground*/
	bool bIsInGroundMeleeChargeUp = false; 

	/*True if character is performing a melee attack on the groun*/
	bool bIsInGroundMeleeAttack = false; 

	/*True if character is charging up Melee attack in the air*/
	bool bIsInAirMeleeChargeUp = false; 
	
	/*True if character is performing melee attack in the air*/
	bool bIsInAirMeleeAttack = false; 

	/*True if character is currently performing Guard on the ground*/
	bool bIsInGroundGuard = false; 

	/*True if character is performing Guard in the air*/
	bool bIsInAirGuard = false; 

	/*Class of weapon that the character will have equipped*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Equipped Weapon")
	TSubclassOf<class AAegisWeapon> EquippedWeaponClass = nullptr; 
};
