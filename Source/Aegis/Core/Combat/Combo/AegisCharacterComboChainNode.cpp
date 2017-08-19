// Fill out your copyright notice in the Description page of Project Settings.

#include "Aegis.h"
#include "AegisCharacterComboChainNode.h"


bool UAegisCharacterComboChainNode::operator==(const UAegisCharacterComboChainNode& Other) const
{
	return GetRequiredComboState() == Other.GetRequiredComboState();
}

void UAegisCharacterComboChainNode::AddChildNode(UAegisCharacterComboChainNode* Child) 
{
	for (int i=0; i<Children.Num(); ++i)
	{
		if (Child || (*Children[i] == *Child))
		{
			return; 
		}
	}
	Children.Emplace(Child); 
}

UAegisCharacterComboChainNode* UAegisCharacterComboChainNode::FindChildNode(UAegisCharacterComboChainNode* Child)
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
