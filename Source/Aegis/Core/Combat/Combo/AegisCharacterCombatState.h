// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "Core/Combat/LockOn/AegisCharacterLockOnComponent.h"
#include "AegisCharacterCombatState.generated.h"

 

USTRUCT(BlueprintType)
struct AEGIS_API FAegisCharacterCombatState 
{
	GENERATED_BODY()
public: 
	FAegisCharacterCombatState() {}
	explicit FAegisCharacterCombatState(const FAegisCharacterCombatState& Other);
	
	FORCEINLINE bool IsInAir() const { return bInAir; }
	FORCEINLINE bool IsInSuper() const { return bInSuper;  }
	FORCEINLINE bool IsInMelee() const { return bInMelee; }
	FORCEINLINE EAegisCharacterLockOnState GetLockOnState() const { return LockOnState; }
	
	

	/** Returns true if alk memberes besides Name and FName of this match Other */
	bool operator==(const FAegisCharacterCombatState& Other) const;
	
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
	bool bInSuper = false; 

	/** Melee Attack State required to satisfy this Combo State */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Combo State")
    bool bInMelee = false;
	/** Lock On State the character must be in to satisfy this Combo state */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Combo State")
	EAegisCharacterLockOnState LockOnState = EAegisCharacterLockOnState::NotLockedOn;
};

/**
* Combo State used for the ComparisonComboTreeNode in ComboComponent. 
* Allows for Setting of the various requirements. 
*/
USTRUCT()
struct AEGIS_API FAegisCharacterCombatStateComparison : public FAegisCharacterCombatState
{
	GENERATED_BODY()
public: 
	FORCEINLINE void SetInAir(bool bInValue) { bInAir = bInValue; }
	FORCEINLINE void SetInSuper(bool bInValue) { bInSuper = bInValue; }
	FORCEINLINE void SetInMelee(bool bInValue) { bInMelee = bInValue; }
	FORCEINLINE void SetLockOnState(EAegisCharacterLockOnState InLockOnState) { LockOnState = InLockOnState; }
	
};
