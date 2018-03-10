// Fill out your copyright notice in the Description page of Project Settings.

#include "Aegis.h"
#include "AegisActionInput.h"
#include "Core/Characters/AegisCharacter.h"

void FAegisCharacterActionInput::Clear()
{
    Action = nullptr;
    bPressed = false;
    Timestamp = FDateTime::MinValue();
}

void FAegisCharacterActionInput::Update(UAegisCharacterActionBase* InAction, bool InPressed)
{
    Action = InAction;
    bPressed = InPressed;
    Timestamp = FDateTime::Now(); 
}

void FAegisCharacterActionInput::Execute(const AAegisCharacter* Character) const
{
    if(Character && Character->IsValidLowLevel() && Action && Action->IsValidLowLevel())
    {
        Action->Execute(Character, bPressed);
    }
}

