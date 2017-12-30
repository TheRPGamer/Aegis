// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Core/Combat/Combo/AegisCharacterMove.h"
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
    FAegisCharacterMove GetMove() const { return Move; }
	void SetMove(const FAegisCharacterMove& InMove)  { Move = InMove; }

	/** Returns true if RequiredComboStates are equal */
	bool operator==(const UAegisCharacterComboTreeNode& Other) const;
	
	/** Adds a Node to the Children Set */
	void AddUniqueChild(UAegisCharacterComboTreeNode* Child);
	
	/**
     * Return a child node that has all requirements satisfied by Character.
     * Else returns nullptr
     */
	UAegisCharacterComboTreeNode* FindSatisfiedChild(const class AAegisCharacter* Character) const;
	
	TArray<UAegisCharacterComboTreeNode*>& GetChildren() { return Children; }
private:
    /** Move associated with this Combo Tree Node*/
    FAegisCharacterMove Move;
    
	/** Set of child nodes of this Combo Node */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "PossibleCombos", meta = (AllowPrivateAccess = "true"))
	TArray<UAegisCharacterComboTreeNode*> Children; 
};
