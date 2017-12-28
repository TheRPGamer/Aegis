// Fill out your copyright notice in the Description page of Project Settings.

#include "Aegis.h"
#include "AegisRequirements.h"

bool FAegisCharacterRequirementBase::AreConditionsSatisfied(class AAegisCharacter* Character)
{
    return false;
}

bool FAegisCharacterComboRequirement::AreConditionsSatisfied(class AAegisCharacter* Character)
{
    return false; 
}

bool FAegisCharacterResourceRequirement::AreConditionsSatisfied(class AAegisCharacter* Character)
{
    return false;
}





