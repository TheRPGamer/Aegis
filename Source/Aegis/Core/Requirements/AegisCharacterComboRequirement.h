// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "AegisCharacterRequirementBase.h"
#include "AegisCharacterComboRequirement.generated.h"

/**
 * 
 */

USTRUCT(BlueprintType)
struct AEGIS_API FAegisCharacterComboRequirement : public FAegisCharacterRequirementBase
{
   GENERATED_BODY()
public:
    virtual bool AreConditionsSatisfied(const class AAegisCharacter* Character) const override;

protected:
    bool bInMelee = false;
    bool bInRanged = false;
    bool bInGuard = false;
    bool bInSuper = false;
    bool bInAir = false;
};


