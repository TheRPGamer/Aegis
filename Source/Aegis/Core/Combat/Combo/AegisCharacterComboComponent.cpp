// Fill out your copyright notice in the Description page of Project Settings.

#include "Aegis.h"
#include "AegisCharacterComboComponent.h"
#include "AegisCharacterComboChainNode.h"

// Sets default values for this component's properties
UAegisCharacterComboComponent::UAegisCharacterComboComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
	
}

void UAegisCharacterComboComponent::BuildComboTree()
{
	for (auto& comboChain : AllCombos)
	{
		BuildComboTreeHelper(comboChain); 
	}
}

void UAegisCharacterComboComponent::BuildComboTreeHelper(UAegisCharacterComboChain* ComboChain)
{
	if (!ComboChain || !ComboTreeRootNode)
	{
		return; 
	}
	TArray<FAegisCharacterComboState>& comboStateArray = ComboChain->GetComboStates();
	UAegisCharacterComboChainNode* currentNode = ComboTreeRootNode;
	for (int i=0; i<comboStateArray.Num(); ++i)
	{
		auto node = NewObject<UAegisCharacterComboChainNode>(); 
		node->SetRequiredComboState(comboStateArray[i]); 
		currentNode->AddChildNode(node); 
		currentNode = currentNode->FindChildNode(node); 
	}
}

void UAegisCharacterComboComponent::AdvanceCurrentComboChainNode()
{
	if (CurrentComboChainNode && ComparisonComboChainNode)
	{
		//See if the comparison node matches any possible combos from CurrentComboChainNode
		auto nextComboNode = CurrentComboChainNode->FindChildNode(ComparisonComboChainNode);
		//If it does, set the CurrentComboChainNode to that ComboNode
		if (nextComboNode)
		{
			CurrentComboChainNode = nextComboNode; 
		}
		else
		{
			//If it does not, compare Comparison nodes against the possible combos form the ComboTreeRootNode
			nextComboNode = ComboTreeRootNode->FindChildNode(ComparisonComboChainNode);
			if (nextComboNode)
			{
				CurrentComboChainNode = nextComboNode; 
			}
		}
		UE_LOG(AegisLog, Log, TEXT("Current Combo Node Name: %s"), *(CurrentComboChainNode->GetRequiredComboState().GetName().ToString()) );
	}
}


FORCEINLINE FName UAegisCharacterComboComponent::GetComboName() const
{
	if (ComparisonComboChainNode)
	{
		return ComparisonComboChainNode->GetRequiredComboState().GetName(); 
	}
	return FName("Null"); 
}
FORCEINLINE bool UAegisCharacterComboComponent::IsInAir() const
{
	if (ComparisonComboChainNode)
	{
		return ComparisonComboChainNode->GetRequiredComboState().IsInAir(); 
	}
	return false; 
}

FORCEINLINE bool UAegisCharacterComboComponent::IsInSuperMode() const
{
	if (ComparisonComboChainNode)
	{
		ComparisonComboChainNode->GetRequiredComboState().IsInSuperMode(); 
	}
	return false; 
}

FORCEINLINE bool UAegisCharacterComboComponent::IsInMeleeAttack() const
{
	if (ComparisonComboChainNode)
	{
		ComparisonComboChainNode->GetRequiredComboState().IsInMeleeAttack();
	}
	return false;
}
FORCEINLINE EAegisCharacterLockOnState UAegisCharacterComboComponent::GetLockOnState() const
{
	if (ComparisonComboChainNode)
	{
		return ComparisonComboChainNode->GetRequiredComboState().GetLockOnState(); 
	}
	return EAegisCharacterLockOnState::NotLockedOn; 
}

FORCEINLINE void UAegisCharacterComboComponent::SetInAir(bool bInValue)
{
	if (ComparisonComboChainNode)
	{
		FAegisCharacterComboState* ptr = &(ComparisonComboChainNode->GetRequiredComboState());
		static_cast<FAegisCharacterComboStateComparison*>(ptr)->SetInAir(bInValue);
	}
}

FORCEINLINE void UAegisCharacterComboComponent::SetInSuperMode(bool bInValue)
{
	if(ComparisonComboChainNode)
	{
		FAegisCharacterComboState* ptr = &(ComparisonComboChainNode->GetRequiredComboState());
		static_cast<FAegisCharacterComboStateComparison*>(ptr)->SetInSuperMode(bInValue);
	}
}


FORCEINLINE void UAegisCharacterComboComponent::SetInMeleeAttack(bool bInValue)
{
	if (ComparisonComboChainNode)
	{
		FAegisCharacterComboState* ptr = &(ComparisonComboChainNode->GetRequiredComboState());
		static_cast<FAegisCharacterComboStateComparison*>(ptr)->SetInMeleeAttack(bInValue);
	}
}

FORCEINLINE void UAegisCharacterComboComponent::SetLockOnState(EAegisCharacterLockOnState InLockOnState)
{
	if (ComparisonComboChainNode)
	{
		FAegisCharacterComboState* ptr = &(ComparisonComboChainNode->GetRequiredComboState());
		static_cast<FAegisCharacterComboStateComparison*>(ptr)->SetLockOnState(InLockOnState);
	}
}

void UAegisCharacterComboComponent::PrintComboTree()
{
	TArray<UAegisCharacterComboChainNode*> queue; 
	if (!ComboTreeRootNode)
	{
		return; 
	}
	auto currentNode = ComboTreeRootNode; 
	queue.Emplace(currentNode); 
	for (int i=0; i<queue.Num(); ++i)
	{
		currentNode = queue[i];
		auto children = currentNode->GetChildren(); 
		if (children.Num() < 1)
		{
			continue; 
		}

		for (auto child : children)
		{
			if (child)
			{
				queue.Emplace(child);
			}
		}
	}

	for (auto node : queue)
	{
		UE_LOG(AegisLog, Log, TEXT("%s, "), *(node->GetRequiredComboState().GetName().ToString()));
	}
}

void UAegisCharacterComboComponent::Init()
{
	ComboTreeRootNode = NewObject<UAegisCharacterComboChainNode>();
	if (ComboTreeRootNode)
	{
		CurrentComboChainNode = ComboTreeRootNode;
	}
	ComparisonComboChainNode = NewObject<UAegisCharacterComboChainNode>();
	if (ComparisonComboChainNode)
	{
		ComparisonComboChainNode->SetRequiredComboState(FAegisCharacterComboStateComparison());
	}
}