// Fill out your copyright notice in the Description page of Project Settings.

#include "Aegis.h"
#include "AegisCharacterComboState.h"

FAegisCharacterComboState::FAegisCharacterComboState()
{

}

FAegisCharacterComboState::FAegisCharacterComboState(const FAegisCharacterComboState& Other)
{
	bInAir = Other.IsInAir();
	bInSuperMode = Other.IsInSuperMode();
	LockOnState = Other.GetLockOnState();
}

bool FAegisCharacterComboState::operator==(const FAegisCharacterComboState& Other) const
{
	return IsInAir() == Other.IsInAir() && IsInSuperMode() == Other.IsInSuperMode() &&
		 IsInMeleeAttack() == Other.IsInMeleeAttack() && GetLockOnState() == Other.GetLockOnState(); 
}

FAegisCharacterComboState& FAegisCharacterComboState::operator=(const FAegisCharacterComboState& Other)
{
	if (this != &Other)
	{
		Name = Other.GetName(); 
		DisplayName = Other.GetDisplayName(); 
		bInAir = Other.IsInAir();
		bInSuperMode = Other.IsInSuperMode();
		bInMeleeAttack = Other.IsInMeleeAttack(); 
		LockOnState = Other.GetLockOnState();
	}
	return *this; 
}
