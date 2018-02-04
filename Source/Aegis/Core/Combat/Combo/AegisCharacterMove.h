// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "Core/Combat/LockOn/AegisCharacterLockOnComponent.h"
#include "Core/Requirements/AegisCharacterMoveRequirement.h"
#include "Core/GameplayEffects/AegisGameplayEffectApplicationOrder.h"
#include "AegisCharacterMove.generated.h"


class AAegisCharacter;

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
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    UAnimMontage* Animation = nullptr;
    
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

