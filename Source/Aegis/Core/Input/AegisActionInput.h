// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AegisActionInput.generated.h"

/**
 * Enum for the various Lock ON States a Character can be in .
 */

UENUM()
enum class EAegisCharacterActionType : uint8
{
    None,
    Melee,
    Ranged,
    Guard
};

UENUM()
enum class EAegisCharacterLockOnState : uint8
{
    //Char Locked On && Velocity Vector Toward Target
    MovingTowardsTarget,
    //Char Locked On && Velocity Vector Away From Target
    MovingAwayFromTarget,
    //Char Locked On && Char not moving
    NotMoving,
    //Char not locked on and not moving
    NotLockedOn
};


USTRUCT(BlueprintType)
struct AEGIS_API FAegisCharacterActionInput
{
    GENERATED_BODY()
public:
    void Clear();
    void Update(EAegisCharacterLockOnState InLockOnState, EAegisCharacterActionType InActionType, bool InPressed); 
    FORCEINLINE EAegisCharacterLockOnState GetLockOnState() const { return LockOnState; }
    FORCEINLINE EAegisCharacterActionType GetActionType() { return ActionType; }
    FORCEINLINE bool GetPressed() const { return bPressed; }
    FORCEINLINE FDateTime GetTimestamp() const { return Timestamp; }
    
    EAegisCharacterLockOnState LockOnState = EAegisCharacterLockOnState::NotLockedOn;
    EAegisCharacterActionType ActionType = EAegisCharacterActionType::None;
    bool bPressed = false;
    FDateTime Timestamp = FDateTime::MinValue();
    
	
};
