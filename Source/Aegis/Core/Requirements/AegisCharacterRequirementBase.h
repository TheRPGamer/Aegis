// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "AegisCharacterRequirementBase.generated.h"

class AAegisCharacter;

/**
 * 
 */
USTRUCT(BlueprintType)
struct AEGIS_API FAegisCharacterRequirementBase
{
	GENERATED_BODY()
public:
    virtual ~FAegisCharacterRequirementBase() { }
    virtual bool AreConditionsSatisfied(const  AAegisCharacter* Character) const;
};


