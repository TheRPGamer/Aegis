// Fill out your copyright notice in the Description page of Project Settings.

#include "Aegis.h"
#include "AegisCharacterComboState.h"

FAegisCharacterComboState::FAegisCharacterComboState()
{

}

FAegisCharacterComboState::FAegisCharacterComboState(const FAegisCharacterComboState& Other)
{
	bRequiresInAir = Other.RequiresInAir();
	bRequiresSuperMode = Other.RequiresSuperMode();
	RequiredLockOnState = Other.GetRequiredLockOnState();
}

bool FAegisCharacterComboState::operator==(const FAegisCharacterComboState& Other) const
{
	return RequiresInAir() == Other.RequiresInAir() && RequiresSuperMode() == Other.RequiresSuperMode() &&
		GetRequiredLockOnState() == Other.GetRequiredLockOnState(); 
}

FAegisCharacterComboState& FAegisCharacterComboState::operator=(const FAegisCharacterComboState& Other)
{
	if (this != &Other)
	{
		bRequiresInAir = Other.RequiresInAir();
		bRequiresSuperMode = Other.RequiresSuperMode();
		RequiredLockOnState = Other.GetRequiredLockOnState();
	}
	return *this; 
}
