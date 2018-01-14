// Fill out your copyright notice in the Description page of Project Settings.

#include "Aegis.h"
#include "AegisCharacterMove.h"
#include "Core/Characters/AegisCharacter.h"

bool FAegisCharacterMove::CanExecute(const AAegisCharacter* Character) const
{
    return Requirement.AreConditionsSatisfied(Character);
    
}

bool FAegisCharacterMove::operator==(const FAegisCharacterMove& Other) const
{
    return Requirement == Other.GetRequirement();
}

