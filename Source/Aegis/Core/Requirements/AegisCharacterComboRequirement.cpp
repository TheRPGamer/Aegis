// Fill out your copyright notice in the Description page of Project Settings.

#include "Aegis.h"
#include "Core/Characters/AegisCharacter.h"
#include "Core/Combat/Combo/AegisCharacterComboComponent.h"
#include "AegisCharacterComboRequirement.h"

bool FAegisCharacterComboRequirement::AreConditionsSatisfied(const AAegisCharacter* Character) const
{
    if(Character)
    {
        auto comboComp = Character->GetComboComponent();
        if(comboComp)
        {
            return comboComp->GetCurrentCombatState() == CombatState;
        }
    }
    return false; 
}

bool FAegisCharacterComboRequirement::operator==(const FAegisCharacterComboRequirement& Other) const
{
    return CombatState == Other.GetCombatState(); 
}




