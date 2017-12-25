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
    void Execute(const class AAegisCharacter* Character) const;
    void Clear();
    void Update(const FAegisCharacterActionBase& InAction, bool InPressed);
    FORCEINLINE FAegisCharacterActionBase GetAction() const { return Action; }
    FORCEINLINE bool GetPressed() const { return bPressed; }
    FORCEINLINE FDateTime GetTimestamp() const { return Timestamp; }
    
    FAegisCharacterActionBase Action;
    bool bPressed = false;
    FDateTime Timestamp = FDateTime::MinValue();
    
	
};
