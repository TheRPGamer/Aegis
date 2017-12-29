// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
 #include "Core/Combat/Combo/AegisCharacterCombatState.h"
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
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat State")
     FAegisCharacterCombatState RequiredCombatState;
};


