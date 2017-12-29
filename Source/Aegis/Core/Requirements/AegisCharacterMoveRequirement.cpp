// Fill out your copyright notice in the Description page of Project Settings.

#include "Aegis.h"
#include "Core/AegisCharacter.h"
#include "AegisCharacterMoveRequirement.h"

bool FAegisCharacterMoveRequirement::AreConditionsSatisfied(const AAegisCharacter* Character) const 
{
    for(auto& requirement : Requirements)
    {
        if(!requirement.AreConditionsSatisfied(Character))
        {
            return false;
        }
    }
    return true;
}

void FAegisCharacterMoveRequirement::Init()
{
    Requirements.Add(ComboRequirement);
}




