// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "Core/Combat/LockOn/AegisCharacterLockOnComponent.h"
#include "Core/Requirements/AegisCharacterMoveRequirement.h"
#include "Core/GameplayEffects/AegisGameplayEffectContainer.h"
#include "AegisCharacterMove.generated.h"

 

USTRUCT(BlueprintType)
struct AEGIS_API FAegisCharacterMove
{
   GENERATED_BODY()
    

    FORCEINLINE FName GetName() const { return Name; }
    FORCEINLINE FText GetDisplayName() const { return DisplayName; }
    FORCEINLINE UAnimSequenceBase* GetAnimation() const { return Animation; }
    FORCEINLINE const FAegisCharacterMoveRequirement& GetRequirement() const { return Requirement; }
    bool CanExecute(const class AAegisCharacter* Character) const;
    bool operator==(const FAegisCharacterMove& Other) const;
    
protected:
    /** Name of the move */
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName Name = NAME_None;
    
    /** Display name of the move*/
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FText DisplayName;
    
    /** Requirements that need to be fulfilled to perform this move*/
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FAegisCharacterMoveRequirement Requirement;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    UAnimSequenceBase* Animation = nullptr;
    
    /** Gameplay Effects that will occur when this Move is successfully performed*/
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FAegisGameplayEffectContainer GameplayEffects;
};

