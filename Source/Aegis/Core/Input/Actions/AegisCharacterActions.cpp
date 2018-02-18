// Fill out your copyright notice in the Description page of Project Settings.

#include "Aegis.h"
#include "AegisCharacterActions.h"
#include "Core/Characters/AegisCharacter.h"
#include "Core/Combat/Combo/AegisCharacterCombatState.h"
#include "Core/Combat/Combo/AegisCharacterComboComponent.h"


void UAegisCharacterActionBase::Execute(const AAegisCharacter* Character, bool bPressed) const
{
    UE_LOG(AegisInputLog, Log, TEXT("%s"), *(DebugName.ToString()));
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
void UAegisCharacterMeleeAction::OnActionPressed(const AAegisCharacter* Character) const
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

void UAegisCharacterMeleeAction::OnActionReleased(const AAegisCharacter* Character) const
{
    if(!Character)
    {
        return;
    }
}


void UAegisCharacterGuardAction::OnActionPressed(const AAegisCharacter* Character) const
{
    if(!Character)
    {
        return;
    }
    auto comboComp = Character->GetComboComponent();
    if(comboComp)
    {
        //TODO: Update Guard Stuff
        comboComp->SetInGuard(true);
        auto lockOn = Character->GetLockOnState();
        comboComp->SetLockOnState(lockOn);
    }
}

void UAegisCharacterGuardAction::OnActionReleased(const AAegisCharacter* Character) const
{
    if(!Character)
    {
        return;
    }
    auto comboComp = Character->GetComboComponent();
    if(comboComp)
    {
        //comboComp->SetInGuard(false);
    }
    
}


void UAegisCharacterSuperAction::OnActionPressed(const AAegisCharacter* Character) const
{
    if(!Character)
    {
        return;
    }
    auto comboComp = Character->GetComboComponent();
    if(comboComp)
    {
        //TODO: Update Super Stuff
        comboComp->SetInSuper(true);
        auto lockOn = Character->GetLockOnState();
        comboComp->SetLockOnState(lockOn);
    }
}

void UAegisCharacterSuperAction::OnActionReleased(const AAegisCharacter* Character) const
{
    if(!Character)
    {
        return;
    }
    auto comboComp = Character->GetComboComponent();
    if(comboComp)
    {
        
    }
    
}



