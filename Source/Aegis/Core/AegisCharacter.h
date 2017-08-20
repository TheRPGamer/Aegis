// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Core/Combat/Combo/AegisCharacterComboComponent.h"
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
	/** Sets default values for this character's properties */
	AAegisCharacter();

protected:
	/** Called when the game starts or when spawned */
	virtual void BeginPlay() override;

public:
	/** Function called when AegisCharacter is damaged*/
	virtual float TakeDamage(float DamageAmount, const struct FDamageEvent& DamageEvent, AController* EventInstigagor, AActor* DamageCauser) override; 

	FORCEINLINE UFUNCTION(BlueprintCallable)
	float GetCurrentHP() const { return CurrentHP; }
	
	FORCEINLINE UFUNCTION(BlueprintCallable)
	void SetCurrentHP(float newValue) { CurrentHP = newValue; }

	/** Returns character's max HP*/
	FORCEINLINE UFUNCTION(BlueprintCallable)
	float GetMaxHP() const { return MaxHP; }

	/** Returns true if the character is currently in the air*/
	FORCEINLINE UFUNCTION(BlueprintCallable)
	bool IsInAir() const;
	

	/** Returns true if character is currently in Super Mode*/
	FORCEINLINE UFUNCTION(BlueprintCallable)
	bool IsInSuperMode() const { return bInSuperMode; }
	
	/** Returns true if character is in the lock on state*/
	FORCEINLINE UFUNCTION(BlueprintCallable)
	bool IsInLockOn() const { return bIsInLockOn;}
	
	/** Returns true if character is currently in Hit Stun State*/
	FORCEINLINE UFUNCTION(BlueprintCallable)
	bool IsInHitStun() const{	return bIsInHitStun; }
	
	/** Returns true if character is performing Melee Attack on the ground*/
	FORCEINLINE UFUNCTION(BlueprintCallable)
	bool IsInGroundMeleeAttack() const { return bIsInGroundMeleeAttack; }
	
	/** Returns true if character is performing Melee Attack in the air*/
	FORCEINLINE UFUNCTION(BlueprintCallable)
	bool IsInAirMeleeAttack() const { return bIsInAirMeleeAttack; }
	
	/** Returns true if character is Guarding on the ground*/
	FORCEINLINE UFUNCTION(BlueprintCallable)
	bool IsInGroundGuard() const { return bIsInGroundGuard; }
	
	/** Returns true if character is guarding in the air*/
	FORCEINLINE UFUNCTION(BlueprintCallable)
	bool IsInAirGuard() const { return bIsInAirGuard; }

	/** Returns true if character is in the Dead State*/
	FORCEINLINE UFUNCTION(BlueprintCallable)
	bool IsDead() const { return (CurrentHP <= 0.0f); }
	
	/** Returns true if the character's state allows for the character to perform Melee Attacks*/
	FORCEINLINE UFUNCTION(BlueprintCallable)
	bool CanUseMeleeAttack() const { return !bIsInHitStun && !bIsInGroundMeleeChargeUp && !bIsInGroundMeleeAttack;}
	
	/** Returns true if the character's state allows for the character to Guard*/
	FORCEINLINE UFUNCTION(BlueprintCallable)
	bool CanUseGuard() const { return !bIsInHitStun; }
	
	/** Returns true if the character's current state allows for any movement*/
	FORCEINLINE UFUNCTION(BlueprintCallable)
	bool CanMove() const;
	
	
	/** Resets Ground Charge Up and Melee Attack States to false*/
	FORCEINLINE UFUNCTION(BlueprintCallable)
	void ResetGroundMeleeAttackState();
	
	/** Resets GroundGuardState to false*/
	FORCEINLINE UFUNCTION(BlueprintCallable)
	void ResetGroundGuardState() { bIsInGroundGuard = false; }
	
	/** Resets character hit stun state to false */
	FORCEINLINE UFUNCTION(BlueprintCallable)
	void ResetHitStunState() { bIsInHitStun = false;  }
	
	/**
	* Function called while character is in the Idle State to reset
	* Melee Attack, Guard State and Hit Stun States.
	*/
	FORCEINLINE UFUNCTION(BlueprintCallable)
	void IdleStateReset();
	
	FORCEINLINE class AAegisWeapon* GetEquippedWeapon() const { return EquippedWeapon; }
	
	
protected: 
	/** Character's maximum HP. Must be > 0.0f*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "HP", meta = (AllowPrivateAccess = "true"))
	float MaxHP = 0.0f; 
	
	/** Character's current HP. Dies if < 0.0f*/
	float CurrentHP = 0.0f;

	/** True if character is in the lock on state*/
	bool bIsInLockOn = false;

	/** True if character is in Super Mode*/
	bool bInSuperMode = false;

	/** True if character is currently in hit stun*/
	bool bIsInHitStun = false;
	
	/** True if character is currently charging up a melee attack on ground*/
	bool bIsInGroundMeleeChargeUp = false; 

	/** True if character is performing a melee attack on the groun*/
	bool bIsInGroundMeleeAttack = false; 

	/** True if character is charging up Melee attack in the air*/
	bool bIsInAirMeleeChargeUp = false; 
	
	/** True if character is performing melee attack in the air*/
	bool bIsInAirMeleeAttack = false; 

	/** True if character is currently performing Guard on the ground*/
	bool bIsInGroundGuard = false; 

	/** True if character is performing Guard in the air*/
	bool bIsInAirGuard = false; 

	/** Class of weapon that the character will have equipped*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Equipped Weapon")
	TSubclassOf<class AAegisWeapon> EquippedWeaponClass = nullptr; 

	/** Character's currently equipped weapon */
	UPROPERTY()
	class AAegisWeapon* EquippedWeapon = nullptr;

	/** Character's Combo Component Class to be used. Must be set in editor  */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ComboCombponent")
		TSubclassOf<class UAegisCharacterComboComponent> ComboComponentClass = UAegisCharacterComboComponent::StaticClass();

	/** Character's Combo Component */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "ComboCombponent")
	class UAegisCharacterComboComponent* ComboComponent = nullptr;


	/** The left hand socket of the character */
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Sockets")
	FName LeftHandSocket = NAME_None;

	/** The right hand socket of the character */
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Sockets")
	FName RightHandSocket = NAME_None;

private: 
#if !UE_BUILD_SHIPPING
	/** Checks if sockets exist and logs missing ones */
	void ValidateSockets();
#endif

};
