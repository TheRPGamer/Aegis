// Fill out your copyright notice in the Description page of Project Settings.

#include "Aegis.h"
#include "Core/Characters/AegisCharacter.h"
#include "Core/Input/AegisActionInputBufferComponent.h"
#include "Core/Combat/Combo/AegisCharacterComboTreeNode.h"
#include "AegisCharacterComboComponent.h"

// Sets default values for this component's properties
UAegisCharacterComboComponent::UAegisCharacterComboComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
    PrimaryComponentTick.TickGroup = TG_PostPhysics;
}

UAnimSequenceBase* UAegisCharacterComboComponent::GetCurrentAnimation() const
{
    if(CurrentComboTreeNode)
    {
        return CurrentComboTreeNode->GetMove().GetAnimation();
    }
    return nullptr;
}

void UAegisCharacterComboComponent::BuildComboTree()
{
	//Construct Root
    if(!ComboTreeRootNode)
    {
        ComboTreeRootNode = NewObject<UAegisCharacterComboTreeNode>();
    }
    CurrentComboTreeNode = ComboTreeRootNode;
    ComparisonComboTreeNode = NewObject<UAegisCharacterComboTreeNode>();
    if(ComparisonComboTreeNode)
    {
        //TODO: Set Comparison Requirements for Comparison Combo Tree Node
    }
    //Begin Constructing Tree
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
	auto& moves = ComboChain->GetMoves();
	UAegisCharacterComboTreeNode* currentNode = ComboTreeRootNode;
    for(auto& move : moves)
	{
		auto node = NewObject<UAegisCharacterComboTreeNode>(); 
		if(node)
        {
            node->SetMove(move);
            currentNode->AddUniqueChild(node);
            currentNode = node;
        }
        else
        {
            UE_LOG(AegisComboLog, Error, TEXT("ComboTreeNode could not be created while building Combo Tree."));
        }
	}
}

void UAegisCharacterComboComponent::Update()
{
    
    //only update if not currently in a combo
    if(IsInCombo())
    {
        return;
    }
    auto inputBuffer = GetAegisOwnerInputBufferComponent();
    if(inputBuffer)
    {
        //grab the top input and execute the Character action to update the relevant Character Components
        auto input = inputBuffer->Get();
        input.Execute(GetAegisOwner());
    }
    TryAdvanceCombo();
}

void UAegisCharacterComboComponent::Interrupt()
{
    //TODO: Interrupt the combo from an extrenal source 
}

void UAegisCharacterComboComponent::TryAdvanceCombo()
{
	if (CurrentComboTreeNode)
	{
		//Based on Owner's current state, see if there's a node to move on to
        auto nextComboNode = CurrentComboTreeNode->FindSatisfiedChild(GetAegisOwner());
		if(!nextComboNode)
		{
            //Try searching from the Root
            SetCurrentNodeToRoot();
            nextComboNode = CurrentComboTreeNode->FindSatisfiedChild(GetAegisOwner());
            //if we still can't find a child node from root, stop search
            if (!nextComboNode)
			{
                AbortCombo();
                return;
			}
		}
        //if execution reaches here, we found a valid child. Advance the combo
        AdvanceCombo(nextComboNode);
        //Starts AnimBP transition from Idle to Combo
        // SetInCombo(true);
	}
}

void UAegisCharacterComboComponent::AbortCombo()
{
    ResetComparisonComboState();
    //This starts transitioning the ABP from Combo back to Idle
    SetInCombo(false);
}

void UAegisCharacterComboComponent::AdvanceCombo(UAegisCharacterComboTreeNode* InComboTreeNode)
{
    SetInCombo(true);
    if (CurrentComboTreeNode)
    {
        CurrentComboTreeNode = InComboTreeNode;

        ResetComparisonComboState();
        UE_LOG(AegisLog, Log, TEXT("Current Combo Node Name: %s"), *(CurrentComboTreeNode->GetMove().GetName().ToString()) );
    }
}

void UAegisCharacterComboComponent::SetCurrentNodeToRoot()
{
	if (CurrentComboTreeNode && ComboTreeRootNode)
	{
		CurrentComboTreeNode = ComboTreeRootNode;
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
//        UE_LOG(AegisLog, Log, TEXT("%s, "), *(node->GetRequiredCombatState().GetName().ToString()));
	}
    
}
#endif
void UAegisCharacterComboComponent::OnRegister()
{
	Super::OnRegister(); 
	BuildComboTree();
	PrintComboTree(); 
}

    void UAegisCharacterComboComponent::OnComboAnimationBegin()
    {
        //TODO: Code that runs at teh start of every Combo Animation
    }

    
void UAegisCharacterComboComponent::OnComboAnimationEnd()
{
	//transitions Anim BP from Combo to Idle
    SetInCombo(false);
    ResetComparisonComboState();
    Update();
}

void UAegisCharacterComboComponent::ResetComparisonComboState()
{
	SetInMelee(false); 
	 
}

AAegisCharacter* UAegisCharacterComboComponent::GetAegisOwner() const
{
    return Cast<AAegisCharacter>(GetOwner());
}

UAegisActionInputBufferComponent* UAegisCharacterComboComponent::GetAegisOwnerInputBufferComponent() const
{
    auto owner = GetAegisOwner();
    if(owner)
    {
        return owner->GetInputBufferComponent();
    }
    return nullptr;
}


