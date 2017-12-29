// Fill out your copyright notice in the Description page of Project Settings.

#include "Aegis.h"
#include "AegisCharacterCombatState.h"

FAegisCharacterCombatState::FAegisCharacterCombatState(const FAegisCharacterCombatState& Other)
{
	bInAir = Other.IsInAir();
	bInSuper = Other.IsInSuper();
    bInMelee = Other.IsInMelee();
    LockOnState = Other.GetLockOnState();
}

bool FAegisCharacterCombatState::operator==(const FAegisCharacterCombatState& Other) const
{
	return IsInAir() == Other.IsInAir() && IsInSuper() == Other.IsInSuper() &&
    IsInMelee() == Other.IsInMelee() && GetLockOnState() == Other.GetLockOnState(); 
}
