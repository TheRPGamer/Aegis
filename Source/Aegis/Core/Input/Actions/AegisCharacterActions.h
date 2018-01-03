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

/**
 * Base class for all AegisCharacter Actions
 * Inherit from this class for new Default Character Actions
 */

USTRUCT()
struct AEGIS_API FAegisCharacterActionBase
{
    GENERATED_BODY()
public:
    virtual ~FAegisCharacterActionBase() { }
    /**
     * Updatest the passed in AegisCharacter's various Components by forwarding the calls to On Action Pressed() and On ActionReleased()*/
    void Execute(const AAegisCharacter* Character, bool bPressed) const;
protected:  
    /** Override in child classes*/
    virtual void OnActionPressed(const AAegisCharacter* Character) const{ }
    /**Override in child classes. */
    virtual void OnActionReleased(const AAegisCharacter* Character) const { }
    
};

/**
 * Default updates to AegisCharacters when Melee Input is pressed
 * Inherit from this class for custom handling of Melee inputsfor different Characters
 */
USTRUCT()
struct FAegisCharacterMeleeAction : public FAegisCharacterActionBase
{
    GENERATED_BODY()
protected:
    /** Updates Character's Combo Component.*/
    virtual void OnActionPressed(const AAegisCharacter* Character) const override;
    /** Updates Character's Combo Component*/
    virtual void OnActionReleased(const AAegisCharacter* Character) const override;
};

/**
 * Default updates to AegisCharacter when Guard Action is is Input
 * Inherit from this class for custom handling of Guard Inputs for different characters
 */
USTRUCT()
struct FAegisCharacterGuardAction : public FAegisCharacterActionBase
{
    GENERATED_BODY()
protected:
    /** Updates Character's Combo Component and Guard Component*/
    virtual void OnActionPressed(const AAegisCharacter* Character) const override;
    /** Updates Character's Combo Component and Guard Component*/
    virtual void OnActionReleased(const AAegisCharacter* Character) const override;
};



