// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Core/AegisCharacter.h"
#include "AegisCharacterComboState.generated.h"

/**
 * The building block for Combo Chains. 
 */
USTRUCT(BlueprintType)
struct AEGIS_API FAegisCharacterComboState 
{
	GENERATED_BODY()
public: 
	FAegisCharacterComboState(); 
	explicit FAegisCharacterComboState(const FAegisCharacterComboState& Other); 

	FORCEINLINE FName GetName() const { return Name; }
	FORCEINLINE FText GetDisplayName() const { return DisplayName; }
	FORCEINLINE bool IsInAir() const { return bInAir; }
	FORCEINLINE bool IsInSuperMode() const { return bInSuperMode;  }
	FORCEINLINE bool IsInMeleeAttack() const { return bInMeleeAttack; }
	FORCEINLINE EAegisCharacterLockOnState GetLockOnState() const { return LockOnState;  }

	/** Returns true if alk memberes besides Name and FName of this match Other */
	bool operator==(const FAegisCharacterComboState& Other) const;
	
	/** Performs a shallow copy of all the member variables */
	FAegisCharacterComboState& operator=(const FAegisCharacterComboState& Other);

protected: 
	
	/** Name for this Combo State for quick comparisoms */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Combo Name")
	FName Name = NAME_None; 

	/** Display name for this Combo State */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Combo Name")
	FText DisplayName;

	/** Air State required to satisfy Combo State */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Combo State")
	bool bInAir = false; 

	/** Super Mode State required to satisfy this Combo State */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Combo State")
	bool bInSuperMode = false; 

	/** Melee Attack State required to satisfy this Combo State */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Combo State")
	bool bInMeleeAttack = false;


	/** Lock On State the character must be in to satisfy this Combo state */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Combo State")
	EAegisCharacterLockOnState LockOnState = EAegisCharacterLockOnState::NotLockedOn;
	
	
};

USTRUCT()
struct AEGIS_API FAegisCharacterComboStateComparison : public FAegisCharacterComboState
{
	GENERATED_BODY()
public: 
	FORCEINLINE void SetInAir(bool bInValue) { bInAir = bInValue; }
	FORCEINLINE void SetInSuperMode(bool bInValue) { bInSuperMode = bInValue; }
	FORCEINLINE void SetInMeleeAttack(bool bInValue) { bInMeleeAttack = bInValue; }
	FORCEINLINE void SetLockOnState(EAegisCharacterLockOnState InLockOnState) { LockOnState = InLockOnState; }
	
};