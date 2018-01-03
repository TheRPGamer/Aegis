// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Core/Requirements/AegisCharacterRequirementBase.h"
#include "AegisGameplayEffectBase.generated.h"

class AAegisCharacter;

/**
 * 
 */

//EditInlineNew allows for unique copy to be created and edited in Properties Window
// Inherited by all child classes by default. Use NoEditInlineNew to override
UCLASS(Abstract, EditInlineNew, BlueprintType, Blueprintable)
class AEGIS_API UAegisGameplayEffectBase : public UObject
{
	GENERATED_BODY()
public:
    // Look into PURE_VIRTUAL/make this class abstract
    virtual void OnBegin() { }
    virtual void OnEnd() { }
	
};













