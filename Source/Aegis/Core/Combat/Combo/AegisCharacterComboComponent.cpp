// Fill out your copyright notice in the Description page of Project Settings.

#include "Aegis.h"
#include "Core/AegisCharacter.h"
#include "Core/Input/AegisActionInputBufferComponent.h"
#include "Core/Combat/Combo/AegisCharacterComboTreeNode.h"
#include "AegisCharacterComboComponent.h"

// Sets default values for this component's properties
UAegisCharacterComboComponent::UAegisCharacterComboComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
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
	TArray<FAegisCharacterMove> moves = ComboChain->GetComboStates();
	UAegisCharacterComboTreeNode* currentNode = ComboTreeRootNode;
    for(auto& move : moves)
	{
		auto node = NewObject<UAegisCharacterComboTreeNode>(); 
		node->SetMove(move);
		currentNode->AddUniqueChild(node);
        currentNode = node;
	}
}

void UAegisCharacterComboComponent::Update()
{
    
    //only update if not currently in a combo
    if(!IsInCombo())
    {
        auto inputBuffer = GetAegisOwnerInputBufferComponent();
        if(inputBuffer)
        {
            //grab the top input and execute the Character Actio to update the relevant Character Components
            auto input = inputBuffer->Get();
            input.Execute(GetAegisOwner());
        }
        
    }
    
}

void UAegisCharacterComboComponent::TryAdvanceCombo()
{
	
	if (CurrentComboTreeNode && ComparisonComboTreeNode)
	{
		//Based on Owner's current state, see if there's a node to move on to
        auto nextComboNode = CurrentComboTreeNode->FindSatisfiedChild(GetAegisOwner());
		
		if(!nextComboNode)
		{
            //reset current node to combo tree Root
            AbortCombo();
            //try looking for a child from the root
            nextComboNode = CurrentComboTreeNode->FindSatisfiedChild(GetAegisOwner());
            //if we still can't find a child node from root, stop search
            if (!nextComboNode)
			{
				//Sets comparison combo node to Idle State params
                ResetComparisonComboState();
				//This starts transitioning the ABP from Combo back to Idle
				SetInCombo(false);
                //See SetInMelee(), allows player inputs to be registered again
                bAcceptInput = true;
                return;
			}
			 
		}
        //if execution reaches here, we found a valid child. Advance the combo
        AdvanceCombo(nextComboNode);
        //this being true starts Anim BP transition to combo
        SetInCombo(true);
            
	}
}


void UAegisCharacterComboComponent::AdvanceCombo(UAegisCharacterComboTreeNode* InComboTreeNode)
{
    if (CurrentComboTreeNode && InComboTreeNode)
    {
        CurrentComboTreeNode = InComboTreeNode;
        //Resets Comparison Combo state to Idle State params
        ResetComparisonComboState();
        //UE_LOG(AegisLog, Log, TEXT("Current Combo Node Name: %s"), *(CurrentComboTreeNode->GetRequiredComboState().GetName().ToString()) );
    }
}

void UAegisCharacterComboComponent::AbortCombo()
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
		//UE_LOG(AegisLog, Log, TEXT("%s, "), *(node->GetRequiredComboState().GetName().ToString()));
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
	SetInCombo(false); 
	TryAdvanceCombo(); 
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


