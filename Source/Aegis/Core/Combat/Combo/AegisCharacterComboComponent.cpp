// Fill out your copyright notice in the Description page of Project Settings.

#include "Aegis.h"
#include "Core/Characters/AegisCharacter.h"
#include "Core/Input/AegisActionInputBufferComponent.h"
#include "Core/Combat/Combo/AegisCharacterComboTreeNode.h"
#include "AegisCharacterComboComponent.h"
#include "Core/AegisCharacterAnimInstance.h"


// Sets default values for this component's properties
UAegisCharacterComboComponent::UAegisCharacterComboComponent()
{
    // Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
    // off to improve performance if you don't need them.
    PrimaryComponentTick.bCanEverTick = false;
}

UAnimMontage* UAegisCharacterComboComponent::GetCurrentAnimation() const
{
    if(CurrentComboTreeNode)
    {
        return CurrentComboTreeNode->GetMove().GetAnimation();
    }
    return nullptr;
}

FAegisCharacterMove UAegisCharacterComboComponent::GetCurrentMove() const
{
    if(CurrentComboTreeNode)
    {
        return CurrentComboTreeNode->GetMove();
    }
    return FAegisCharacterMove();
}

void UAegisCharacterComboComponent::BuildComboTree()
{
    //Construct Root
    if(!ComboTreeRootNode)
    {
        ComboTreeRootNode = NewObject<UAegisCharacterComboTreeNode>();
    }
    CurrentComboTreeNode = ComboTreeRootNode;
    
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
    auto currentNode = ComboTreeRootNode;
    for(const auto& move : moves)
    {
        currentNode = currentNode->TryAddChild(move);
    }
}

void UAegisCharacterComboComponent::Update()
{
    
    //if currently in a combo, don't update
    if(IsInCombo())
    {
        return;
    }
    auto inputBuffer = GetAegisOwnerInputBufferComponent();
    if(inputBuffer)
    {
        inputBuffer->Execute();
        
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
    }
}

void UAegisCharacterComboComponent::AbortCombo()
{
    SetCurrentNodeToRoot();
    ResetComparisonComboState();
    // allows Update9) to process inputs again
    SetInCombo(false);
}

void UAegisCharacterComboComponent::AdvanceCombo(UAegisCharacterComboTreeNode* InComboTreeNode)
{
    if (CurrentComboTreeNode && InComboTreeNode)
    {
        SetInCombo(true);
        CurrentComboTreeNode = InComboTreeNode;
        ResetComparisonComboState();
        UE_LOG(AegisLog, Log, TEXT("Current Combo Node Name: %s"), *(CurrentComboTreeNode->GetMove().GetName().ToString()) );
        AAegisCharacter* owner = GetAegisOwner();
        if(owner)
        {
            // 3rd param is the name of the section to jump to. Name_None plays montage form the start
            owner->PlayAnimMontage(GetCurrentAnimation(), 1.0f, NAME_None);
        }
        
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
    // allows Update to process inputs again
    SetInCombo(false);
    ResetComparisonComboState();
    Update();
}

void UAegisCharacterComboComponent::ResetComparisonComboState()
{
    SetInMelee(false);
    SetInGuard(false);
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

