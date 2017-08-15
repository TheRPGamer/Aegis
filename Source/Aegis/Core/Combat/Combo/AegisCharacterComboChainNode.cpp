// Fill out your copyright notice in the Description page of Project Settings.

#include "Aegis.h"
#include "AegisCharacterComboChainNode.h"


bool UAegisCharacterComboChainNode::operator==(const UAegisCharacterComboChainNode& Other) const
{
	return GetRequiredComboState() == Other.GetRequiredComboState();
}

void UAegisCharacterComboChainNode::AddChildNode(UAegisCharacterComboChainNode* Child) 
{
	for (auto comboNode : Children)
	{
		if (*comboNode == *Child)
		{
			return; 
		}
	}
	Children.Emplace(Child); 
}

UAegisCharacterComboChainNode* UAegisCharacterComboChainNode::FindChildNode(UAegisCharacterComboChainNode* Child)
{	
	for (auto comboNode : Children)
	{
		if (*comboNode == *Child)
		{
			return comboNode; 
		}
	}
	return nullptr; 
}
