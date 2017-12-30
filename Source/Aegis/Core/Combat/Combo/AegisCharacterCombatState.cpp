// Fill out your copyright notice in the Description page of Project Settings.

#include "Aegis.h"
#include "AegisCharacterCombatState.h"

bool FAegisCharacterCombatState::operator==(const FAegisCharacterCombatState& Other) const
{
	return IsInAir() == Other.IsInAir() && IsInSuper() == Other.IsInSuper() &&
    IsInMelee() == Other.IsInMelee() && GetLockOnState() == Other.GetLockOnState(); 
}
