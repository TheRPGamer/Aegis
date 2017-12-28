// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "AegisCharacterRequirementBase.h"
#include "AegisCharacterResourceRequirement.generated.h"

/**
 * 
 */

USTRUCT(BlueprintType)
struct AEGIS_API FAegisCharacterResourceRequirement : public FAegisCharacterRequirementBase
{
    GENERATED_BODY()
public:
    virtual bool AreConditionsSatisfied(const class AAegisCharacter* Character) const override;
    
protected:
    float MinHP = 0.f;
    float MaxHP = 0.f;
    float MinSpecial = 0.0f;
    float MaxSpecial = 0.f;
    float MinSuper = 0.f;
    float MaxSuper = 0.f; 
    
};

