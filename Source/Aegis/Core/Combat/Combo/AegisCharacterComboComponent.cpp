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
	if (!ComboChain)
	{
		UE_LOG(AegisComboLog, Error, TEXT("Combo Chain invalid invalid in %s Combo Component."), *(GetOwner()->GetHumanReadableName()));
		return;
	}
	if (!ComboTreeRootNode)
	{
		UE_LOG(AegisComboLog, Error, TEXT("Combo Tree Root Node invalid in %s Combo Component."), *(GetOwner()->GetHumanReadableName()));
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


FName UAegisCharacterComboComponent::GetComboName() const
{
	if (ComparisonComboChainNode)
	{
		return ComparisonComboChainNode->GetRequiredComboState().GetName(); 
	}
	UE_LOG(AegisComboLog, Error, TEXT("Comparison Combo Node invalid in %s Combo Component."), *(GetOwner()->GetHumanReadableName()));
	return NAME_None;
}

bool UAegisCharacterComboComponent::IsInAir() const
{
	if (ComparisonComboChainNode)
	{
		return ComparisonComboChainNode->GetRequiredComboState().IsInAir(); 
	}
	UE_LOG(AegisComboLog, Error, TEXT("Comparison Combo Node invalid in %s Combo Component."), *(GetOwner()->GetHumanReadableName()));
	return false;
}

bool UAegisCharacterComboComponent::IsInSuperMode() const
{
	if (ComparisonComboChainNode)
	{
		ComparisonComboChainNode->GetRequiredComboState().IsInSuperMode(); 
	}
	UE_LOG(AegisComboLog, Error, TEXT("Comparison Combo Node invalid in %s Combo Component."), *(GetOwner()->GetHumanReadableName()));
	return false;
}

bool UAegisCharacterComboComponent::IsInMeleeAttack() const
{
	if (ComparisonComboChainNode)
	{
		ComparisonComboChainNode->GetRequiredComboState().IsInMeleeAttack();
	}
	UE_LOG(AegisComboLog, Error, TEXT("Comparison Combo Node invalid in %s Combo Component."), *(GetOwner()->GetHumanReadableName()));
	return false;
}

EAegisCharacterLockOnState UAegisCharacterComboComponent::GetLockOnState() const
{
	if (ComparisonComboChainNode)
	{
		return ComparisonComboChainNode->GetRequiredComboState().GetLockOnState(); 
	}
	UE_LOG(AegisComboLog, Error, TEXT("Comparison Combo Node invalid in %s Combo Component."), *(GetOwner()->GetHumanReadableName()));
	return EAegisCharacterLockOnState::NotLockedOn;
}

void UAegisCharacterComboComponent::SetInAir(bool bInValue)
{
	if (ComparisonComboChainNode)
	{
		FAegisCharacterComboState* ptr = &(ComparisonComboChainNode->GetRequiredComboState());
		static_cast<FAegisCharacterComboStateComparison*>(ptr)->SetInAir(bInValue);
	}
	else
	{
		UE_LOG(AegisComboLog, Error, TEXT("Comparison Combo Node invalid in %s Combo Component."), *(GetOwner()->GetHumanReadableName()));
	}
}

void UAegisCharacterComboComponent::SetInSuperMode(bool bInValue)
{
	if(ComparisonComboChainNode)
	{
		FAegisCharacterComboState* ptr = &(ComparisonComboChainNode->GetRequiredComboState());
		static_cast<FAegisCharacterComboStateComparison*>(ptr)->SetInSuperMode(bInValue);
	}
	else
	{
		UE_LOG(AegisComboLog, Error, TEXT("Comparison Combo Node invalid in %s Combo Component."), *(GetOwner()->GetHumanReadableName()));
	}
}


void UAegisCharacterComboComponent::SetInMeleeAttack(bool bInValue)
{
	if (ComparisonComboChainNode)
	{
		FAegisCharacterComboState* ptr = &(ComparisonComboChainNode->GetRequiredComboState());
		static_cast<FAegisCharacterComboStateComparison*>(ptr)->SetInMeleeAttack(bInValue);
	}
	else
	{
		UE_LOG(AegisComboLog, Error, TEXT("Comparison Combo Node invalid in %s Combo Component."), *(GetOwner()->GetHumanReadableName()));
	}
}

void UAegisCharacterComboComponent::SetLockOnState(EAegisCharacterLockOnState InLockOnState)
{
	if (ComparisonComboChainNode)
	{
		FAegisCharacterComboState* ptr = &(ComparisonComboChainNode->GetRequiredComboState());
		static_cast<FAegisCharacterComboStateComparison*>(ptr)->SetLockOnState(InLockOnState);
	}
	else
	{
		UE_LOG(AegisComboLog, Error, TEXT("Comparison Combo Node invalid in %s Combo Component."),*(GetOwner()->GetHumanReadableName()));
	}
}
#if !UE_BUILD_SHIPPING
void UAegisCharacterComboComponent::PrintComboTree()
{
	//Does a level order traversal using BFS and prints out results
	TArray<UAegisCharacterComboChainNode*> queue; 
	if (!ComboTreeRootNode)
	{
		UE_LOG(AegisComboLog, Error, TEXT("Combo Tree Root Node invalid in %s Combo Component."), *(GetOwner()->GetHumanReadableName()));
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
#endif
void UAegisCharacterComboComponent::OnRegister()
{
	Super::OnRegister(); 
	ComboTreeRootNode = CreateDefaultSubobject<UAegisCharacterComboChainNode>("Combo Tree Root Node");
	if (ComboTreeRootNode)
	{
		CurrentComboChainNode = ComboTreeRootNode;
	}
	else
	{
		UE_LOG(AegisComboLog, Error, TEXT("Failure to create Combo Tree Root Node in %s Combo Component."), *(GetOwner()->GetHumanReadableName()));
	}
	ComparisonComboChainNode = CreateDefaultSubobject<UAegisCharacterComboChainNode>("Combo Comparison Node");
	if (ComparisonComboChainNode)
	{
		ComparisonComboChainNode->SetRequiredComboState(FAegisCharacterComboStateComparison());
	}
	else
	{
		UE_LOG(AegisComboLog, Error, TEXT("Failed to initialise Comparison Combo Node in %s Combo Component."), *(GetOwner()->GetHumanReadableName()));
	}
	BuildComboTree(); 
	PrintComboTree(); 
}

