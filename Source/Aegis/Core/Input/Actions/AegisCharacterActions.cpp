// Fill out your copyright notice in the Description page of Project Settings.

#include "Aegis.h"
#include "AegisCharacterActions.h"
#include "Core/AegisCharacter.h"
#include "Core/Combat/Combo/AegisCharacterComboState.h"
#include "Core/Combat/Combo/AegisCharacterComboComponent.h"


void FAegisCharacterActionBase::Execute(const AAegisCharacter* Character, bool bPressed) const
{
    if(!Character)
    {
        return;
    }
    if(bPressed)
    {
        OnActionPressed(Character);
    }
    else
    {
        OnActionReleased(Character);
    }
}

void FAegisCharacterMeleeAction::OnActionPressed(const AAegisCharacter* Character) const
{
    if(!Character)
    {
        return;
    }
    auto comboComp = Character->GetComboComponent();
    if(comboComp)
    {
        comboComp->SetInMeleeAttack(true);
        auto lockOn = Character->GetLockOnState();
        comboComp->SetLockOnState(lockOn);
    }
}

void FAegisCharacterMeleeAction::OnActionReleased(const AAegisCharacter* Character) const
{
    if(!Character)
    {
        return;
    }
}



