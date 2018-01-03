// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AegisCharacterComboRequirement.h"
#include "AegisCharacterRequirementBase.h"
#include "AegisCharacterMoveRequirement.generated.h"

/**
 * 
 */

USTRUCT(BlueprintType)
struct AEGIS_API FAegisCharacterMoveRequirement : public FAegisCharacterRequirementBase
{
    GENERATED_BODY()
public:
    virtual bool AreConditionsSatisfied(const class AAegisCharacter* Character) const override;
    bool operator==(const FAegisCharacterMoveRequirement& Other) const;
    FAegisCharacterComboRequirement GetComboRequirement() const { return ComboRequirement; }

protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
    FAegisCharacterComboRequirement ComboRequirement;
};

