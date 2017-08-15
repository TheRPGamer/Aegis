// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Core/Combat/Combo/AegisCharacterComboChain.h"
#include "AegisCharacterComboComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class AEGIS_API UAegisCharacterComboComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	explicit UAegisCharacterComboComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	class UAegisCharacterComboChainNode* GetComparisonComboChainNode() const { return ComparisonComboChainNode; }
	class UAegisCharacterComboChainNode* GetComparisonComboChainNode() { return ComparisonComboChainNode; }
	
	/** Builds a Combo Tree from AllCombos */
	void BuildComboTree();

	/** Compares Comparison Node with CurrentCmboChainNode Children to advance combo */
	void AdvanceCurrentComboChainNode(); 
private:
	/** Helper function that builds the Combo Tree */
	void BuildComboTreeHelper(UAegisCharacterComboChain* ComboChain);

	/** All Combo Chains that the owner of this Combo Component can perform */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combos", meta = (AllowPrivateAccess = "true"))
	TArray<UAegisCharacterComboChain*> AllCombos;

	/**Root Node of the Combo Node Tree. Needs to be set in editor */
	UPROPERTY(EditAnywhere, BlueprintReadWrite , Category = "Combos", meta = (AllowPrivateAccess = "true"))
	class UAegisCharacterComboChainNode* ComboTreeRootNode = nullptr;

	/** Current node in the Combo Tree traversal */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combos", meta = (AllowPrivateAccess = "true"))
	class UAegisCharacterComboChainNode* CurrentComboChainNode = nullptr;

	/** Combo Chain Node the owner will update. To be used to compare with Children of CurrentComboTreeNode */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combos", meta = (AllowPrivateAccess = "true"))
	class UAegisCharacterComboChainNode* ComparisonComboChainNode = nullptr;
	
};