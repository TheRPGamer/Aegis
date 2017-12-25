// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/Input/Actions/AegisCharacterActions.h"
#include "AegisActionInput.generated.h"

/**
 * Enum for the various Lock ON States a Character can be in .
 */





USTRUCT(BlueprintType)
struct AEGIS_API FAegisCharacterActionInput
{
    GENERATED_BODY()
public:
    /** Called to apply effects of Action to an AegisCharacter  */
    void Execute(const class AAegisCharacter* Character) const;
    /** Clears teh Action Input to default values*/
    void Clear();
    /** Updates all the member variables  with the arguments*/
    void Update(const FAegisCharacterActionBase& InAction, bool InPressed);
    
    //Getters
    FORCEINLINE FAegisCharacterActionBase GetAction() const { return Action; }
    FORCEINLINE bool GetPressed() const { return bPressed; }
    FORCEINLINE FDateTime GetTimestamp() const { return Timestamp; }
    
    /**
     * Represents the Action that was input. E.g Melee, Guard etc
     * @ see AegisCharacterActions.h
     */
    FAegisCharacterActionBase Action;
    
    /** If the Input was from a Press or Release*/
    bool bPressed = false;
    
    /** Time the input was made*/
    FDateTime Timestamp = FDateTime::MinValue();
    
	
};
