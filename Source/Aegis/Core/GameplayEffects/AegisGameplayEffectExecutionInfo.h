// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Core/Requirements/AegisCharacterRequirementBase.h"
#include "AegisGameplayEffectExecutionInfo.generated.h"

/**
 * Info struct used to hold information about the parties involved in the Gameplay Effect
 * The impact position of the effect, hit normals etc
 */
USTRUCT()
struct AEGIS_API FAegisGameplayEffectExecutionInfo
{
	GENERATED_BODY()
public:
    UPROPERTY()
    AActor* Instigator = nullptr;
    
    UPROPERTY()
    AActor* Causer;
    
    UPROPERTY()
    AActor* Receiver = nullptr;
    
    UPROPERTY()
    AActor* Target = nullptr;
    
    FVector ImpactLocation;
    FVector ImpactNormal;
    
};













