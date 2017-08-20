// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Core/Combat/Combo/AegisCharacterComboChain.h"
#include "AegisCharacterComboComponent.generated.h"

/**
* Handles solving for what Combo the Character advances to based on Character actions
* Builds a Combo Tree of unique Combo Tree Nodes.
* Character combo advances by traversing the Combo Tree
*/

UCLASS( Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class AEGIS_API UAegisCharacterComboComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UAegisCharacterComboComponent();

	/** Gets the Name Field from the ComparisonNode's ComboState */
	FName GetComboName() const; 
	bool IsInAir() const; 
	bool IsInSuperMode() const; 
	bool IsInMeleeAttack() const; 
	EAegisCharacterLockOnState GetLockOnState() const; 

	/** Sets IsInAir field of ComparisonNode's Combo State */
	void SetInAir(bool bInValue);
	void SetInSuperMode(bool bInValue); 
	void SetInMeleeAttack(bool bInValue);
	void SetLockOnState(EAegisCharacterLockOnState InLockOnState); 

	/** Builds a Combo Tree from AllCombos */
	void BuildComboTree();

	/** Function called to advance in the Combo Tree */
	void AdvanceCombo(); 

#if !UE_BUILD_SHIPPING
	/** For Debug Purposes */
	void PrintComboTree(); 
#endif
	/** Function called when the Component is registered */
	void OnRegister() override;
protected:
	/** All Combo Chains that the owner of this Combo Component can perform */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combos", meta = (AllowPrivateAccess = "true"))
	TArray<UAegisCharacterComboChain*> AllCombos;
private: 
	/** Adds a Combo Chain to the Combo Tree. Helper function to BuildComboTree() */
	void AddComboChainToComboTree(UAegisCharacterComboChain* ComboChain);


	/** Root Node of the Combo Tree. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly , Category = "Combos", meta = (AllowPrivateAccess = "true"))
	class UAegisCharacterComboTreeNode* ComboTreeRootNode = nullptr;

	/** Current node in the Combo Tree traversal */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combos", meta = (AllowPrivateAccess = "true"))
	class UAegisCharacterComboTreeNode* CurrentComboTreeNode = nullptr;

	/** Combo Tree Node the owner will update. To be used to compare with Children of CurrentComboTreeNode */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combos", meta = (AllowPrivateAccess = "true"))
	class UAegisCharacterComboTreeNode* ComparisonComboTreeNode = nullptr;
};