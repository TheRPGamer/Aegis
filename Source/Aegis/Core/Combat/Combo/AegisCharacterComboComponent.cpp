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
	if (!ComboChain || !ComboChainRootNode)
	{
		return; 
	}
	auto comboStateArray = ComboChain->GetComboStates();
	UAegisCharacterComboChainNode* currentNode = ComboChainRootNode;
	for (auto& comboState : comboStateArray)
	{
		auto node = NewObject<UAegisCharacterComboChainNode>(); 
		node->SetRequiredComboState(comboState); 
		currentNode->AddChildNode(node); 
		currentNode = currentNode->FindChildNode(currentNode); 
	}
}

