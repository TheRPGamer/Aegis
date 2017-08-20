// Fill out your copyright notice in the Description page of Project Settings.

#include "Aegis.h"
#include "AegisCharacterComboState.h"

FAegisCharacterComboState::FAegisCharacterComboState(const FAegisCharacterComboState& Other)
{
	bInAir = Other.IsInAir();
	bInSuperMode = Other.IsInSuperMode();
	LockOnState = Other.GetLockOnState();
	Animation = Other.GetAnimation(); 
}

bool FAegisCharacterComboState::operator==(const FAegisCharacterComboState& Other) const
{
	return IsInAir() == Other.IsInAir() && IsInSuperMode() == Other.IsInSuperMode() &&
		 IsInMeleeAttack() == Other.IsInMeleeAttack() && GetLockOnState() == Other.GetLockOnState(); 
}
