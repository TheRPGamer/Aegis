// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Core/Combat/Combo/AegisCharacterComboState.h"
#include "AegisCharacterComboChainNode.generated.h"

/**
 * 
 */
UCLASS()
class AEGIS_API UAegisCharacterComboChainNode : public UObject
{
	GENERATED_BODY()
public: 
	const FAegisCharacterComboState& GetRequiredComboState() const { return RequiredComboState; }
	void SetRequiredComboState(const FAegisCharacterComboState& ComboState)  { RequiredComboState = ComboState; }

	/** Returns true if RequiredComboStates are equal */
	bool operator==(const UAegisCharacterComboChainNode& Other) const;
	
	/** Adds a Node to the Children Set */
	void AddChildNode(UAegisCharacterComboChainNode* Child);
	/** Returns the passed in node was found. Returns nullptr otherwise. */
	UAegisCharacterComboChainNode* FindChildNode(UAegisCharacterComboChainNode* Child); 
	
	/** Gets a unique hash of this Combo Node */
	uint32 GetTypeHash(const UAegisCharacterComboChainNode& Node);
private:
	/** Combo State character must be in to reach this Combo Node */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "PossibleCombos", meta = (AllowPrivateAccess = "true"))
	FAegisCharacterComboState RequiredComboState;
	
	/** Set of child nodes of this Combo Node */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "PossibleCombos", meta = (AllowPrivateAccess = "true"))
	TSet<UAegisCharacterComboChainNode*> Children; 
	
};
