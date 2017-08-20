// Fill out your copyright notice in the Description page of Project Settings.

#include "Aegis.h"
#include "AegisCharacterComboTreeNode.h"


bool UAegisCharacterComboTreeNode::operator==(const UAegisCharacterComboTreeNode& Other) const
{
	return GetRequiredComboState() == Other.GetRequiredComboState();
}

void UAegisCharacterComboTreeNode::AddUniqueChild(UAegisCharacterComboTreeNode* Child) 
{
	if (!Child)
	{
		UE_LOG(AegisComboLog, Error, TEXT("Child node to be added to AeigsComboChainNode is null")); 
		return;
	}
	for (int i=0; i<Children.Num(); ++i)
	{
		if (*Children[i] == *Child)
		{
			return; 
		}
	}
	Children.Emplace(Child); 
}

UAegisCharacterComboTreeNode* UAegisCharacterComboTreeNode::FindChild(UAegisCharacterComboTreeNode* Child)
{	
	for (int i=0; i<Children.Num(); ++i)
	{
		if (*Children[i] == *Child)
		{
			return Children[i]; 
		}
	}
	return nullptr; 
}
