// Fill out your copyright notice in the Description page of Project Settings.

#include "Aegis.h"
#include "AegisCharacterComboTreeNode.h"
#include "Core/Characters/AegisCharacter.h"


bool UAegisCharacterComboTreeNode::operator==(const UAegisCharacterComboTreeNode& Other) const
{
    return Move == Other.GetMove();
}

UAegisCharacterComboTreeNode* UAegisCharacterComboTreeNode::TryAddChild(const FAegisCharacterMove& InMove)
{
    for(const auto child : Children)
    {
        //if a child with the matching FAegisCharacterMove already exists
        if(child && (child->GetMove() == InMove))
        {
            return child; 
        }
    }
    auto newChild = NewObject<UAegisCharacterComboTreeNode>();
    newChild->SetMove(InMove);
    Children.Add(newChild);
    return newChild;
}


UAegisCharacterComboTreeNode* UAegisCharacterComboTreeNode::FindSatisfiedChild(const AAegisCharacter* Character) const
{	
	if(!Character)
    {
        return nullptr;
    }
    for(const auto child : Children)
    {
        if(child->GetMove().CanExecute(Character))
        {
            return child;
        }
    }
	return nullptr; 
}










