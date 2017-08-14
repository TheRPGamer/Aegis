// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Engine/DataAsset.h"
#include "AegisCharacterComboState.h"
#include "AegisCharacterComboChain.generated.h"

/**
 * A single instance of a Combo Chain that can be used for one character
 */
UCLASS()
class AEGIS_API UAegisCharacterComboChain : public UDataAsset
{
	GENERATED_BODY()
public: 
	TArray<FAegisCharacterComboState>& GetComboStates() { return ComboStates;  }

private: 
	/** Array of Combo States thta make up the Combo Chain */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combos", meta = (AllowPrivateAccess = "true"))
	TArray<FAegisCharacterComboState> ComboStates; 

	
	
	
};
