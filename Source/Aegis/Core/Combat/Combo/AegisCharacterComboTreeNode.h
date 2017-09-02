// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Core/Combat/Combo/AegisCharacterComboState.h"
#include "AegisCharacterComboTreeNode.generated.h"

/**
 * A single Node of the Combo Tree. Root of the tree is found in AegisCharacterComboComponent
 * Each node contains a TArray of Childdren Nodes and you can Add/Find Nodes form the Children to build the treee. 
 * 
 */
UCLASS()
class AEGIS_API UAegisCharacterComboTreeNode : public UObject
{
	GENERATED_BODY()
public: 
	const FAegisCharacterComboState& GetRequiredComboState() const { return RequiredComboState; }
	FAegisCharacterComboState& GetRequiredComboState() { return RequiredComboState; }

	void	SetRequiredComboState(const FAegisCharacterComboState& ComboState)  { RequiredComboState = ComboState; }

	/** Returns true if RequiredComboStates are equal */
	bool operator==(const UAegisCharacterComboTreeNode& Other) const;
	
	/** Adds a Node to the Children Set */
	void AddUniqueChild(UAegisCharacterComboTreeNode* Child);
	
	/** Returns the passed in node was found. Returns nullptr otherwise. */
	UAegisCharacterComboTreeNode* FindChild(UAegisCharacterComboTreeNode* Child); 
	
	TArray<UAegisCharacterComboTreeNode*>& GetChildren() { return Children; }
private:
	/** Combo State character must be in to reach this Combo Node */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "PossibleCombos", meta = (AllowPrivateAccess = "true"))
	FAegisCharacterComboState RequiredComboState;
	
	/** Set of child nodes of this Combo Node */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "PossibleCombos", meta = (AllowPrivateAccess = "true"))
	TArray<UAegisCharacterComboTreeNode*> Children; 
};
