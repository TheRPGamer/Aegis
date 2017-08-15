// Fill out your copyright notice in the Description page of Project Settings.

#include "Aegis.h"
#include "AegisCharacterComboComponent.h"
#include "AegisCharacterComboChainNode.h"

// Sets default values for this component's properties
UAegisCharacterComboComponent::UAegisCharacterComboComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	ComboTreeRootNode = NewObject<UAegisCharacterComboChainNode>(); 
	if (ComboTreeRootNode)
	{
		ComboTreeRootNode->SetRequiredComboState(FAegisCharacterComboState());
		CurrentComboChainNode = ComboTreeRootNode; 
	}
	ComparisonComboChainNode = NewObject<UAegisCharacterComboChainNode>(); 
	if (ComparisonComboChainNode)
	{
		ComparisonComboChainNode->SetRequiredComboState(FAegisCharacterComboStateComparison()); 
	}
	// ...
}


// Called when the game starts
void UAegisCharacterComboComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UAegisCharacterComboComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
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
	auto comboStateArray = ComboChain->GetComboStates();
	UAegisCharacterComboChainNode* currentNode = ComboTreeRootNode;
	for (auto& comboState : comboStateArray)
	{
		auto node = NewObject<UAegisCharacterComboChainNode>(); 
		node->SetRequiredComboState(comboState); 
		currentNode->AddChildNode(node); 
		currentNode = currentNode->FindChildNode(currentNode); 
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
	return FName("Null"); 
}
bool UAegisCharacterComboComponent::IsInAir() const
{
	if (ComparisonComboChainNode)
	{
		return ComparisonComboChainNode->GetRequiredComboState().IsInAir(); 
	}
	return false; 
}
bool UAegisCharacterComboComponent::IsInSuperMode() const
{
	if (ComparisonComboChainNode)
	{
		ComparisonComboChainNode->GetRequiredComboState().IsInSuperMode(); 
	}
	return false; 
}
EAegisCharacterLockOnState UAegisCharacterComboComponent::GetLockOnState() const
{
	if (ComparisonComboChainNode)
	{
		return ComparisonComboChainNode->GetRequiredComboState().GetLockOnState(); 
	}
	return EAegisCharacterLockOnState::NotLockedOn; 
}

void UAegisCharacterComboComponent::SetIsInAir(bool bInValue)
{
	if (ComparisonComboChainNode)
	{
		FAegisCharacterComboState* ptr = &(ComparisonComboChainNode->GetRequiredComboState());
		static_cast<FAegisCharacterComboStateComparison*>(ptr)->SetIsInAir(bInValue);
	}
}

void UAegisCharacterComboComponent::SetIsInSuperMode(bool bInValue)
{
	if(ComparisonComboChainNode)
	{
		FAegisCharacterComboState* ptr = &(ComparisonComboChainNode->GetRequiredComboState());
		static_cast<FAegisCharacterComboStateComparison*>(ptr)->SetIsInSuperMode(bInValue);
	}
}

void UAegisCharacterComboComponent::SetLockOnState(EAegisCharacterLockOnState InLockOnState)
{
	if (ComparisonComboChainNode)
	{
		FAegisCharacterComboState* ptr = &(ComparisonComboChainNode->GetRequiredComboState());
		static_cast<FAegisCharacterComboStateComparison*>(ptr)->SetLockOnState(InLockOnState);
	}
}
