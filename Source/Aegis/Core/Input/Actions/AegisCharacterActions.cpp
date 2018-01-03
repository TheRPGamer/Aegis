// Fill out your copyright notice in the Description page of Project Settings.

#include "Aegis.h"
#include "AegisCharacterActions.h"
#include "Core/Characters/AegisCharacter.h"
#include "Core/Combat/Combo/AegisCharacterCombatState.h"
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
        comboComp->SetInMelee(true);
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


void FAegisCharacterGuardAction::OnActionPressed(const AAegisCharacter* Character) const
{
    if(!Character)
    {
        return;
    }
    auto comboComp = Character->GetComboComponent();
    if(comboComp)
    {
        //TODO: Update Guard Stuff 
        auto lockOn = Character->GetLockOnState();
        comboComp->SetLockOnState(lockOn);
    }
}

void FAegisCharacterGuardAction::OnActionReleased(const AAegisCharacter* Character) const
{
    if(!Character)
    {
        return;
    }
}



