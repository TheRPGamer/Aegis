// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "AegisCharacter.h"
#include "AegisCharacterCombo.generated.h"

/**
 * A Combo State contains all the character states a Character needs to be in 
 * to perform a combo.  
 */
USTRUCT()
struct AEGIS_API FAegisCharacterComboState
{
	GENERATED_BODY()
public: 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combo State")
	FName Name = NAME_None; 
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combo State")
	FText DisplayName; 
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combo State")
	bool bIsInAir = false; 
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combo State")
	bool bIsInSuperMode = false; 
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combo State")
	EAegisCharacterLockOnState LockOnState = EAegisCharacterLockOnState::NotLockedOn;

	/** Returns true if the contents of this Combo State matches the contents of the Other Combo State */
	bool Matches(const FAegisCharacterComboState& Other) const
	{
		if (bIsInAir == Other.bIsInAir &&
			bIsInSuperMode == Other.bIsInSuperMode &&
			LockOnState == Other.LockOnState)
		{
			return true;
		}
		return false; 
	}
};

/**
 * Each Combo has a Combo State that represents the Combo State 
 * a character needs to be in to transition to this Combo. 
 * Each Combo also has a TMap that essentially holds all the possible Combos
 * This Combo can transition to provided the correct Player input
 */
UCLASS()
class AEGIS_API UAegisCharacterCombo : public UDataAsset
{
	GENERATED_BODY()
public: 
	explicit UAegisCharacterCombo(); 
	FAegisCharacterComboState& GetComboState() { return ComboState;  }
	TArray<UAegisCharacterCombo*> GetPossibleCombosFromInput(FName InputName) const;
private: 
	/** The Combo State that represents this particular Combo */
	FAegisCharacterComboState ComboState;
	
	/** Maps an input FName to a TArray of all corresponding possible combos relating to that input FName */
	TMap<FName, TArray<UAegisCharacterCombo*> > InputNameToPossibleComboMap; 
};
