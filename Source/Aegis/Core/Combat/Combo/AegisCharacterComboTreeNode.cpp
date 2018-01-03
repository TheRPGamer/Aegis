// Fill out your copyright notice in the Description page of Project Settings.

#include "Aegis.h"
#include "AegisCharacterComboTreeNode.h"
#include "Core/Characters/AegisCharacter.h"


bool UAegisCharacterComboTreeNode::operator==(const UAegisCharacterComboTreeNode& Other) const
{
    return Move == Other.GetMove();
}

void UAegisCharacterComboTreeNode::AddUniqueChild(UAegisCharacterComboTreeNode* Child) 
{
	if (!Child)
	{
		UE_LOG(AegisComboLog, Error, TEXT("Child node to be added to AeigsComboChainNode is null")); 
		return;
	}
    for(auto& child : Children)
	{
		//don't add if inChild has the exact same Requirements as an existing Node
        if (*child == *Child)
		{
			return; 
		}
	}
	Children.Emplace(Child); 
}

UAegisCharacterComboTreeNode* UAegisCharacterComboTreeNode::FindSatisfiedChild(const AAegisCharacter* Character) const
{	
	if(!Character)
    {
        return nullptr;
    }
    for(auto& child : Children)
    {
        if(child->GetMove().CanExecute(Character))
        {
            return child;
        }
    }
	return nullptr; 
}
