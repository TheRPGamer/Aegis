// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "Core/Combat/LockOn/AegisCharacterLockOnComponent.h"
#include "Core/Requirements/AegisCharacterMoveRequirement.h"
#include "Core/GameplayEffects/AegisGameplayEffectApplicationOrder.h"
#include "AegisCharacterMove.generated.h"


class AAegisCharacter;

/**
 * Info struct that holds information about how an Animation for Character Move should be played
 */
USTRUCT(BlueprintType)
struct AEGIS_API FAegisCharacterMoveAnimData
{
    GENERATED_BODY()
    FAegisCharacterMoveAnimData() { }
    FORCEINLINE UAnimMontage* GetAnimation() const { return Animation; }
    FORCEINLINE float GetPlayRate() const { return PlayRate; }
protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    UAnimMontage* Animation = nullptr;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float PlayRate = 0.f;
    
};

/**
 * The building block for all Combos in Aegis.
 * Anything that a Character performs that has:
 * 1. A Requirement
 * An Animation
 * 3. Applies Gameplay Effects to something
 * SI a Character Move
 */
USTRUCT(BlueprintType)
struct AEGIS_API FAegisCharacterMove
{
   GENERATED_BODY()
    

    FORCEINLINE FName GetName() const { return Name; }
    FORCEINLINE FText GetDisplayName() const { return DisplayName; }
    FORCEINLINE UAnimMontage* GetAnimation() const { return Animation; }
    FORCEINLINE const FAegisCharacterMoveRequirement& GetRequirement() const { return Requirement; }
    bool CanExecute(const AAegisCharacter* Character) const;
    bool operator==(const FAegisCharacterMove& Other) const;
    
    const FAegisGameplayEffectApplicationOrder& GetPreCollisionGFX() const { return PreCollisionGFX; }
    const FAegisGameplayEffectApplicationOrder GetCollisionGFX() const { return CollisionGFX; }
    const FAegisGameplayEffectApplicationOrder GetPostCollisionGFX() const { return PostCollisionGFX; }
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
    
    /** Animation played when this Move is performed */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
    UAnimMontage* Animation = nullptr;
    
    /** Play Rate of the Animation */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
    float AnimationPlayRate = 1.0f;
    
    /** Gameplay Effects that will occur when this move is successfully performed before collision occurs */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay Effects")
    FAegisGameplayEffectApplicationOrder PreCollisionGFX;
    
    /** Gameplay Effects that will occur when this Move is successfully performed and collides with a target */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay Effects")
    FAegisGameplayEffectApplicationOrder CollisionGFX;
    
    /** Gameplay Effects that will occur when the move is successfully performed after a collision has occured */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay Effects")
    FAegisGameplayEffectApplicationOrder PostCollisionGFX;







};

