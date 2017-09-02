// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "AegisCharacterComboState.generated.h"

/**
* Enum for the various Lock ON States a Character can be in . 
*/
UENUM()
enum class EAegisCharacterLockOnState : uint8
{
	//Char Locked On && Velocity Vector Toward Target
	MovingTowardsTarget,
	//Char Locked On && Velocity Vector Away From Target
	MovingAwayFromTarget,
	//Char Locked On && Char not moving 
	NotMoving,
	//Char not locked on and not moving 
	NotLockedOn
};

/**
 * The building block for Combo Chains. Contains all requirements needed for this Combo State.
 */
USTRUCT(BlueprintType)
struct AEGIS_API FAegisCharacterComboState 
{
	GENERATED_BODY()
public: 
	FAegisCharacterComboState() {}
	explicit FAegisCharacterComboState(const FAegisCharacterComboState& Other); 

	FORCEINLINE FName GetName() const { return Name; }
	FORCEINLINE FText GetDisplayName() const { return DisplayName; }
	FORCEINLINE bool IsInAir() const { return bInAir; }
	FORCEINLINE bool IsInSuperMode() const { return bInSuperMode;  }
	FORCEINLINE bool IsInMeleeAttack() const { return bInMeleeAttack; }
	FORCEINLINE bool IsInPauseComboWindow() const {
		return bInPauseComboWindow
			;
	}
	FORCEINLINE EAegisCharacterLockOnState GetLockOnState() const { return LockOnState;  }
	FORCEINLINE UAnimSequence* GetAnimation() { return Animation; }
	FORCEINLINE UAnimSequence* GetAnimation() const { return Animation; }

	/** Returns true if alk memberes besides Name and FName of this match Other */
	bool operator==(const FAegisCharacterComboState& Other) const;
	
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

	/** If the combo requreies the  character to be in the pause combo state */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Combo State")
	bool bInPauseComboWindow = false;


	/** Lock On State the character must be in to satisfy this Combo state */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Combo State")
	EAegisCharacterLockOnState LockOnState = EAegisCharacterLockOnState::NotLockedOn;

	/** Animation asset to be played when this combo is performed */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Combo State")
	UAnimSequence* Animation = nullptr; 
	
};

/**
* Combo State used for the ComparisonComboTreeNode in ComboComponent. 
* Allows for Setting of the various requirements. 
*/
USTRUCT()
struct AEGIS_API FAegisCharacterComboStateComparison : public FAegisCharacterComboState
{
	GENERATED_BODY()
public: 
	FORCEINLINE void SetInAir(bool bInValue) { bInAir = bInValue; }
	FORCEINLINE void SetInSuperMode(bool bInValue) { bInSuperMode = bInValue; }
	FORCEINLINE void SetInMeleeAttack(bool bInValue) { bInMeleeAttack = bInValue; }
	FORCEINLINE void SetInPauseComboWindow(bool bInValue) { bInPauseComboWindow = bInValue; }
	FORCEINLINE void SetLockOnState(EAegisCharacterLockOnState InLockOnState) { LockOnState = InLockOnState; }
	
};