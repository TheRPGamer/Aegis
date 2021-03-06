// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/Input/Actions/AegisCharacterActions.h"
#include "AegisActionInput.generated.h"

class AAegisCharacter;

USTRUCT(BlueprintType)
struct AEGIS_API FAegisCharacterActionInput
{
    GENERATED_BODY()
public:
    /** Called to apply effects of Action to an AegisCharacter  */
    void Execute(const AAegisCharacter* Character) const;
    /** Clears teh Action Input to default values*/
    void Clear();
    /** Updates all the member variables  with the arguments*/
    void Update(UAegisCharacterActionBase* InAction, bool InPressed);
    
    
    FORCEINLINE UAegisCharacterActionBase* GetAction() const { return Action; }
    FORCEINLINE bool GetPressed() const { return bPressed; }
    FORCEINLINE FDateTime GetTimestamp() const { return Timestamp; }
    
protected: 
    /** Time the input was made*/
    FDateTime Timestamp = FDateTime::MinValue();
    
    
    /**
     * Represents the Action that was input. E.g Melee, Guard etc
     * @ see AegisCharacterActions.h
     */
    UPROPERTY()
    UAegisCharacterActionBase* Action = nullptr;
    
    
    /** If the Input was from a Press or Release*/
    bool bPressed = false;
    

};
