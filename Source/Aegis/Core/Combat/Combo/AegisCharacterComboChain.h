// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Engine/DataAsset.h"
#include "Core/Combat/Combo/AegisCharacterMove.h"
#include "AegisCharacterComboChain.generated.h"

/**
* A series of FAegisCharacterComboStates make up a Combo Chain.
* Declare in Editor and customise ComboStates to give the series of requirements for the Combo Chain
*/
UCLASS()
class AEGIS_API UAegisCharacterComboChain : public UDataAsset
{
	GENERATED_BODY()
public: 
	FORCEINLINE const TArray<FAegisCharacterMove>& GetMoves() const { return Moves;  }

private: 
	/** Array of  Moves that make up the Combo Chain */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combos", meta = (AllowPrivateAccess = "true"))
	TArray<FAegisCharacterMove> Moves;

	
	
	
};
