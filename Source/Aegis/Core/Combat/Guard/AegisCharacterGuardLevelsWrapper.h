// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "AegisCharacterGuardLevel.h"
#include "AegisCharacterGuardLevelsWrapper.generated.h"

/**
 * 
 */
UCLASS()
class AEGIS_API UAegisCharacterGuardLevelsWrapper : public UDataAsset
{
	GENERATED_BODY()
public:
    TArray<FAegisCharacterGuardLevel> GetGuardLevels() const { return GuardLevels; }
private:
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Guard Levels", meta = (AllowPrivateAccess = "true"))
    TArray<FAegisCharacterGuardLevel> GuardLevels;
	
	
	
};
