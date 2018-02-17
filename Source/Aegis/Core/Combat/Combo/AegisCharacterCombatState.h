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
    FAegisCharacterCombatState() { }
    
	FORCEINLINE bool IsInAir() const { return bInAir; }
	FORCEINLINE bool IsInSuper() const { return bInSuper;  }
	FORCEINLINE bool IsInMelee() const { return bInMelee; }
	FORCEINLINE EAegisCharacterLockOnState GetLockOnState() const { return LockOnState; }
    FORCEINLINE bool IsInGuard() const { return bInGuard; }
    FORCEINLINE bool IsInRanged() const { return bInRanged; }
	

	/** Returns true if alk memberes besides Name and FName of this match Other */
	bool operator==(const FAegisCharacterCombatState& Other) const;
	
protected: 
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
    
    /** Guard state the character must be in to satisfy this Combat State c*/
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bInGuard = false;
    /** The Ranged Attack State the character must be in to satisfy this Combat State */
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bInRanged = false;
};

/**
* Combat state that allows for setting of values
*/
USTRUCT()
struct AEGIS_API FAegisCharacterComparisonCombatState : public FAegisCharacterCombatState
{
	GENERATED_BODY()
public:
    FAegisCharacterComparisonCombatState() { }
	FORCEINLINE void SetInAir(bool bInValue) { bInAir = bInValue; }
	FORCEINLINE void SetInSuper(bool bInValue) { bInSuper = bInValue; }
	FORCEINLINE void SetInMelee(bool bInValue) { bInMelee = bInValue; }
	FORCEINLINE void SetLockOnState(EAegisCharacterLockOnState InLockOnState) { LockOnState = InLockOnState; }
    FORCEINLINE void SetInGuard(bool bInValue) { bInGuard = bInValue; }
    FORCEINLINE void SetInRanged(bool bInValue) { bInRanged = bInValue; }
	
};
