// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "AegisRequirements.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct AEGIS_API FAegisCharacterRequirementBase
{
	GENERATED_BODY()
public:
    virtual ~FAegisCharacterRequirementBase() { }
    virtual bool AreConditionsSatisfied(class AAegisCharacter* Character);
};

USTRUCT(BlueprintType)
struct AEGIS_API FAegisCharacterComboRequirement : public FAegisCharacterRequirementBase
{
   GENERATED_BODY()
public:
    virtual bool AreConditionsSatisfied(class AAegisCharacter* Character) override;

protected:
    bool bInMelee = false;
    bool bInRanged = false;
    bool bInGuard = false;
    bool bInSuper = false;
    bool bInAir = false;
};

USTRUCT(BlueprintType)
struct AEGIS_API FAegisCharacterResourceRequirement : public FAegisCharacterRequirementBase
{
    GENERATED_BODY()
public:
    virtual bool AreConditionsSatisfied(class AAegisCharacter* Character) override;
    
protected:
    float MinHP = 0.f;
    float MaxHP = 0.f;
    float MinSpecial = 0.0f;
    float MaxSpecial = 0.f;
    float MinSuper = 0.f;
    float MaxSuper = 0.f; 
    
};

