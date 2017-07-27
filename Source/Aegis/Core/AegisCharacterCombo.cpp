// Fill out your copyright notice in the Description page of Project Settings.

#include "Aegis.h"
#include "AegisCharacterCombo.h"

UAegisCharacterCombo::UAegisCharacterCombo()
{
	
}

TArray<UAegisCharacterCombo*> UAegisCharacterCombo::GetPossibleCombosFromInput(FName InputName) const
{
	return InputNameToPossibleComboMap[InputName]; 
}


