// Fill out your copyright notice in the Description page of Project Settings.

#include "Aegis.h"
#include "Core/AegisCharacter.h"
#include "AegisCharacterComboRequirement.h"

bool FAegisCharacterComboRequirement::AreConditionsSatisfied(const AAegisCharacter* Character) const
{
    return false; 
}

bool FAegisCharacterComboRequirement::operator==(const FAegisCharacterComboRequirement& Other) const
{
    return CombatState == Other.GetCombatState(); 
}




