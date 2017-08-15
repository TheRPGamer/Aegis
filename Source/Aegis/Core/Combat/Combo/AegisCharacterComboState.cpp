// Fill out your copyright notice in the Description page of Project Settings.

#include "Aegis.h"
#include "AegisCharacterComboState.h"

FAegisCharacterComboState::FAegisCharacterComboState()
{

}

FAegisCharacterComboState::FAegisCharacterComboState(const FAegisCharacterComboState& Other)
{
	bIsInAir = Other.IsInAir();
	bIsInSuperMode = Other.IsInSuperMode();
	LockOnState = Other.GetLockOnState();
}

bool FAegisCharacterComboState::operator==(const FAegisCharacterComboState& Other) const
{
	return IsInAir() == Other.IsInAir() && IsInSuperMode() == Other.IsInSuperMode() &&
		GetLockOnState() == Other.GetLockOnState(); 
}

FAegisCharacterComboState& FAegisCharacterComboState::operator=(const FAegisCharacterComboState& Other)
{
	if (this != &Other)
	{
		bIsInAir = Other.IsInAir();
		bIsInSuperMode = Other.IsInSuperMode();
		LockOnState = Other.GetLockOnState();
	}
	return *this; 
}
