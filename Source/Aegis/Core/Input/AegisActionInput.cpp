// Fill out your copyright notice in the Description page of Project Settings.

#include "Aegis.h"
#include "AegisActionInput.h"
#include "Core/AegisCharacter.h"

void FAegisCharacterActionInput::Clear()
{
    Action = FAegisCharacterActionBase();
    bPressed = false;
    Timestamp = FDateTime::MinValue();
}

void FAegisCharacterActionInput::Update(const FAegisCharacterActionBase& InAction, bool InPressed)
{
    Action = InAction;
    bPressed = InPressed;
    Timestamp = FDateTime::Now(); 
}

void FAegisCharacterActionInput::Execute(const AAegisCharacter* Character) const
{
    if(Character)
    {
        Action.Execute(Character, bPressed);
    }
}

