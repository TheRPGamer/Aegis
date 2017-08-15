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

	FName GetName() const { return Name; }
	FText GetDisplayName() const { return DisplayName; }
	bool RequiresInAir() const { return bRequiresInAir; }
	bool RequiresSuperMode() const { return bRequiresSuperMode;  }
	EAegisCharacterLockOnState GetRequiredLockOnState() const { return RequiredLockOnState;  }

	void SetRequiresInAir(bool bInValue) { bRequiresInAir = bInValue; }
	void SetRequiresSuperMode(bool bInValue) { bRequiresSuperMode = bInValue; }
	void SetRequiredLockOnState(EAegisCharacterLockOnState InLockOnState) { RequiredLockOnState = InLockOnState; }
	
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
	bool bRequiresInAir = false; 

	/** Super Mode State required to satisfy this Combo State */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Combo State")
	bool bRequiresSuperMode = false; 

	/** Lock On State the character must be in to satisfy this Combo state */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Combo State")
	EAegisCharacterLockOnState RequiredLockOnState = EAegisCharacterLockOnState::NotLockedOn;
	
	
};
