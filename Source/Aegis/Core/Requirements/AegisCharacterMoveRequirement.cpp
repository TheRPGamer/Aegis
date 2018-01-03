// Fill out your copyright notice in the Description page of Project Settings.

#include "Aegis.h"
#include "Core/AegisCharacter.h"
#include "AegisCharacterMoveRequirement.h"

bool FAegisCharacterMoveRequirement::AreConditionsSatisfied(const AAegisCharacter* Character) const 
{
    return ComboRequirement.AreConditionsSatisfied(Character);
}

bool FAegisCharacterMoveRequirement::operator==(const FAegisCharacterMoveRequirement& Other) const
{
    return ComboRequirement == Other.GetComboRequirement(); 
}



