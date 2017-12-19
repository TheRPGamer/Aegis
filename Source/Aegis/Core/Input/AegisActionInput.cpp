// Fill out your copyright notice in the Description page of Project Settings.

#include "Aegis.h"
#include "AegisActionInput.h"

void FAegisCharacterActionInput::Clear()
{
    LockOnState = EAegisCharacterLockOnState::NotLockedOn;
    ActionType = EAegisCharacterActionType::None;
    bPressed = false;
    Timestamp = FDateTime::MinValue();
}

void FAegisCharacterActionInput::Update(EAegisCharacterLockOnState InLockOnState, EAegisCharacterActionType InActionType, bool InPressed)
{
    LockOnState = InLockOnState;
    ActionType = InActionType;
    bPressed = InPressed;
    Timestamp = FDateTime::Now(); 
}


