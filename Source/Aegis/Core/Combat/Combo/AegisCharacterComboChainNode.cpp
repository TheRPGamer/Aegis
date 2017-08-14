// Fill out your copyright notice in the Description page of Project Settings.

#include "Aegis.h"
#include "AegisCharacterComboChainNode.h"


bool UAegisCharacterComboChainNode::operator==(const UAegisCharacterComboChainNode& Other) const
{
	return GetRequiredComboState() == Other.GetRequiredComboState();
}

void UAegisCharacterComboChainNode::AddChildNode(UAegisCharacterComboChainNode* Child) 
{
	
	Children.Add(Child); 
}

UAegisCharacterComboChainNode* UAegisCharacterComboChainNode::FindChildNode(UAegisCharacterComboChainNode* Child)
{	
	return *(Children.Find(Child)); 
}

uint32 UAegisCharacterComboChainNode::GetTypeHash(const UAegisCharacterComboChainNode& Node)
{
	return Node.GetRequiredComboState().GetName().GetNumber(); 
}
