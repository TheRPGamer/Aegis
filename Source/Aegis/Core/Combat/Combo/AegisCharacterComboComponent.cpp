// Fill out your copyright notice in the Description page of Project Settings.

#include "Aegis.h"
#include "AegisCharacterComboComponent.h"
#include "AegisCharacterComboTreeNode.h"

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
		AddComboChainToComboTree(comboChain); 
	}
}

void UAegisCharacterComboComponent::AddComboChainToComboTree(UAegisCharacterComboChain* ComboChain)
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
	UAegisCharacterComboTreeNode* currentNode = ComboTreeRootNode;
	for (int i=0; i<comboStateArray.Num(); ++i)
	{
		auto node = NewObject<UAegisCharacterComboTreeNode>(); 
		node->SetRequiredComboState(comboStateArray[i]); 
		currentNode->AddUniqueChild(node);
		currentNode = currentNode->FindChild(node);
		if(!currentNode)
		{
			if (GetOwner())
			{
				UE_LOG(AegisComboLog, Fatal, TEXT("Cannot find child node that was just inserted in %s Combo Component Combo Tree."), *GetOwner()->GetHumanReadableName());
			}
			else
			{
				UE_LOG(AegisComboLog, Fatal, TEXT("Combo Component has no owner."));
			}
		}
	}
}

void UAegisCharacterComboComponent::AdvanceCombo()
{
	if (CurrentComboTreeNode && ComparisonComboTreeNode)
	{
		//See if the comparison node matches any possible combos from CurrentComboChainNode
		auto nextComboNode = CurrentComboTreeNode->FindChild(ComparisonComboTreeNode);
		//If it does, set the CurrentComboChainNode to that ComboNode
		if (nextComboNode)
		{
			CurrentComboTreeNode = nextComboNode; 
		}
		else
		{
			//If it does not, compare Comparison nodes against the possible combos form the ComboTreeRootNode
			nextComboNode = ComboTreeRootNode->FindChild(ComparisonComboTreeNode);
			if (nextComboNode)
			{
				CurrentComboTreeNode = nextComboNode; 
			}
		}
		//Reset the CurrentComboNode's Pause Combo Window State to false
		SetInPauseComboWindow(false); 
		
		UE_LOG(AegisLog, Log, TEXT("Current Combo Node Name: %s"), *(CurrentComboTreeNode->GetRequiredComboState().GetName().ToString()) );
	}
}


FName UAegisCharacterComboComponent::GetComboName() const
{
	if (ComparisonComboTreeNode)
	{
		return ComparisonComboTreeNode->GetRequiredComboState().GetName(); 
	}
	return NAME_None;
}

bool UAegisCharacterComboComponent::IsInAir() const
{
	if (ComparisonComboTreeNode)
	{
		return ComparisonComboTreeNode->GetRequiredComboState().IsInAir(); 
	}
	return false;
}

bool UAegisCharacterComboComponent::IsInSuperMode() const
{
	if (ComparisonComboTreeNode)
	{
		ComparisonComboTreeNode->GetRequiredComboState().IsInSuperMode(); 
	}
	return false;
}

bool UAegisCharacterComboComponent::IsInMeleeAttack() const
{
	if (ComparisonComboTreeNode)
	{
		ComparisonComboTreeNode->GetRequiredComboState().IsInMeleeAttack();
	}
	return false;
}

bool UAegisCharacterComboComponent::IsInPauseComboWindow() const
{
	if (ComparisonComboTreeNode)
	{
		return ComparisonComboTreeNode->GetRequiredComboState().IsInPauseComboWindow();
	}
	return false;
}

EAegisCharacterLockOnState UAegisCharacterComboComponent::GetLockOnState() const
{
	if (ComparisonComboTreeNode)
	{
		return ComparisonComboTreeNode->GetRequiredComboState().GetLockOnState(); 
	}
	return EAegisCharacterLockOnState::NotLockedOn;
}

UAnimSequence* UAegisCharacterComboComponent::GetAnimation()
{
	if (CurrentComboTreeNode)
	{
		return CurrentComboTreeNode->GetRequiredComboState().GetAnimation();
	}
	return nullptr; 
}

void UAegisCharacterComboComponent::SetInAir(bool bInValue)
{
	if (ComparisonComboTreeNode)
	{
		FAegisCharacterComboState* ptr = &(ComparisonComboTreeNode->GetRequiredComboState());
		static_cast<FAegisCharacterComboStateComparison*>(ptr)->SetInAir(bInValue);
	}
}

void UAegisCharacterComboComponent::SetInSuperMode(bool bInValue)
{
	if(ComparisonComboTreeNode)
	{
		FAegisCharacterComboState* ptr = &(ComparisonComboTreeNode->GetRequiredComboState());
		static_cast<FAegisCharacterComboStateComparison*>(ptr)->SetInSuperMode(bInValue);
	}
	
}

void UAegisCharacterComboComponent::SetInMeleeAttack(bool bInValue)
{
	if (ComparisonComboTreeNode)
	{
		FAegisCharacterComboState* ptr = &(ComparisonComboTreeNode->GetRequiredComboState());
		static_cast<FAegisCharacterComboStateComparison*>(ptr)->SetInMeleeAttack(bInValue);
	}
	
}

void UAegisCharacterComboComponent::SetInPauseComboWindow(bool bInValue)
{
	if (ComparisonComboTreeNode)
	{
		FAegisCharacterComboState* ptr = &(ComparisonComboTreeNode->GetRequiredComboState());
		static_cast<FAegisCharacterComboStateComparison*>(ptr)->SetInPauseComboWindow(bInValue);
	}
}

void UAegisCharacterComboComponent::SetLockOnState(EAegisCharacterLockOnState InLockOnState)
{
	if (ComparisonComboTreeNode)
	{
		FAegisCharacterComboState* ptr = &(ComparisonComboTreeNode->GetRequiredComboState());
		static_cast<FAegisCharacterComboStateComparison*>(ptr)->SetLockOnState(InLockOnState);
	}
	
}
#if !UE_BUILD_SHIPPING
void UAegisCharacterComboComponent::PrintComboTree()
{
	//Does a level order traversal using BFS and prints out results
	TArray<UAegisCharacterComboTreeNode*> queue; 
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
	ComboTreeRootNode = NewObject<UAegisCharacterComboTreeNode>();
	if (ComboTreeRootNode)
	{
		CurrentComboTreeNode = ComboTreeRootNode;
	}
	else
	{
		UE_LOG(AegisComboLog, Error, TEXT("Failure to create Combo Tree Root Node in %s Combo Component."), *(GetOwner()->GetHumanReadableName()));
	}
	ComparisonComboTreeNode = NewObject<UAegisCharacterComboTreeNode>();
	if (ComparisonComboTreeNode)
	{
		ComparisonComboTreeNode->SetRequiredComboState(FAegisCharacterComboStateComparison());
	}
	else
	{
		UE_LOG(AegisComboLog, Error, TEXT("Failed to initialise Comparison Combo Node in %s Combo Component."), *(GetOwner()->GetHumanReadableName()));
	}
	BuildComboTree(); 
	PrintComboTree(); 
}

