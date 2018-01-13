// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Core/Combat/Combo/AegisCharacterComboChain.h"
#include "Core/Combat/Combo/AegisCharacterCombatState.h"
#include "core/Combat/Combo/AegisCharacterMove.h"
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
	 
    FORCEINLINE bool IsInAir() const { return CurrentCombatState.IsInAir(); }
    FORCEINLINE bool IsInSuper() const { return CurrentCombatState.IsInSuper(); }
    FORCEINLINE bool IsInMelee() const { return CurrentCombatState.IsInMelee(); }
    FORCEINLINE EAegisCharacterLockOnState GetLockOnState() const { return CurrentCombatState.GetLockOnState(); }
	FORCEINLINE UFUNCTION(BlueprintCallable)
	bool IsInCombo() const { return bInCombo; }
    /** Get the Animation associated with the current Move*/
    UAnimSequenceBase* GetCurrentAnimation() const;
    
	/** Sets IsInAir field of ComparisonNode's Combat State */
	FORCEINLINE void SetInAir(bool bInValue);
    FORCEINLINE void SetInSuper(bool bInSuper) { CurrentCombatState.SetInSuper(bInSuper); }
    FORCEINLINE void SetInMelee(bool bInMelee) { CurrentCombatState.SetInMelee(bInMelee); }
    FORCEINLINE void SetLockOnState(EAegisCharacterLockOnState InLockOnState) { CurrentCombatState.SetLockOnState(InLockOnState); }
	
	FORCEINLINE UFUNCTION(BlueprintCallable)
	void SetInCombo(bool bInValue) { bInCombo = bInValue; }


	/** Function called when the Component is registered */
	void OnRegister() override;
    
    /** Updates the Current Combo State of the Owning Character*/
    void Update(); 
    
    /** Interrupts Current Combo */
    void Interrupt();
    /** Function called by AnimNotify at the start of a Combo Animation*/
    void OnComboAnimationBegin();
    
	/** Function called by Animation Notify when a combo animation has ended*/
	void OnComboAnimationEnd(); 
protected:
	/** All Combo Chains that the owner of this Combo Component can perform */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combos", meta = (AllowPrivateAccess = "true"))
	TArray<UAegisCharacterComboChain*> AllCombos;
private: 
	/** Constructs a tree from the Combo Chains in the owner */
	void BuildComboTree(); 

	void PrintComboTree(); 

	/** Adds a Combo Chain to the Combo Tree. Helper function to BuildComboTree() */
	void AddComboChainToComboTree(UAegisCharacterComboChain* ComboChain);

	/** Function called to advance in the Combo Tree */
	void AdvanceCombo(class UAegisCharacterComboTreeNode* InComboTreeNode);


	/** Tries to advance the current combo */
	void TryAdvanceCombo();
    
    /** Called to end an combo and transition back to other Char States*/
    void AbortCombo();
    
	/** Sets Current  Combo Node to Root*/
	void SetCurrentNodeToRoot();
    
	/** Resets the character's Comparison Combo State after a combo */
	void ResetComparisonComboState(); 
	
    /** Gets teh Aegis Character Owner */
    class AAegisCharacter* GetAegisOwner() const;
    
    /** Gets teh Aegis Owner's Input Buffer Component. Returns null if Aegis Owner is null */
    class UAegisActionInputBufferComponent* GetAegisOwnerInputBufferComponent() const;
    
	/** Root Node of the Combo Tree. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly , Category = "Combos", meta = (AllowPrivateAccess = "true"))
	class UAegisCharacterComboTreeNode* ComboTreeRootNode = nullptr;

	/** Current node in the Combo Tree traversal */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combos", meta = (AllowPrivateAccess = "true"))
	class UAegisCharacterComboTreeNode* CurrentComboTreeNode = nullptr;

	/** Combo Tree Node the owner will update. To be used to compare with Children of CurrentComboTreeNode */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combos", meta = (AllowPrivateAccess = "true"))
	class UAegisCharacterComboTreeNode* ComparisonComboTreeNode = nullptr;
    
    FAegisCharacterComparisonCombatState CurrentCombatState;
    
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combos", meta = (AllowPrivateAccess = "true"))
	bool bInCombo = false;

	/* Debug thing. See SetInMeleeAttack() to understand what it does at a glance*/
	bool bAcceptInput = true; 
};
