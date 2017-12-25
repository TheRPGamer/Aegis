// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AegisCharacterActions.generated.h"

class AAegisCharacter;
class UAegisCharacterComboComponent;

/**
 * All possible actions every single Aegis Character can perform.
 * Every unique action that updates teh AegisActionInputBufferComponnet must override the UpdateCombo() function
 */

/**
 * Namespace that contains the FNames of all possible actions an AegisCharacter can take
 * Must be updated if more actions are added
 */
namespace NAegisCharacterAction
{
    
    const FName None = "None"; 
    const FName Melee = "Melee";
    const FName Guard = "Guard";
    const FName Ranged = "Ranged";
    const FName Super = "Super";
};

USTRUCT()
struct AEGIS_API FAegisCharacterActionBase
{
    GENERATED_BODY()
public:
    virtual ~FAegisCharacterActionBase() { }
    void Execute(const AAegisCharacter* Character, bool bPressed) const;
protected:
    virtual void OnActionPressed(const AAegisCharacter* Character) const{ }
    virtual void OnActionReleased(const AAegisCharacter* Character) const { }
    
};

USTRUCT()
struct FAegisCharacterMeleeAction : public FAegisCharacterActionBase
{
    GENERATED_BODY()
public:
protected:
    virtual void OnActionPressed(const AAegisCharacter* Character) const override;
    virtual void OnActionReleased(const AAegisCharacter* Character) const override;
};



