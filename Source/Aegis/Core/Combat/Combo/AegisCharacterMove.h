// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "Core/Combat/LockOn/AegisCharacterLockOnComponent.h"
#include "Core/Requirements/AegisCharacterMoveRequirement.h"
#include "AegisCharacterMove.generated.h"

 

USTRUCT(BlueprintType)
struct AEGIS_API FAegisCharacterMove
{
   GENERATED_BODY()
    

    FORCEINLINE FName GetName() const { return Name; }
    FORCEINLINE FText GetDisplayName() const { return DisplayName; }
    FORCEINLINE UAnimSequenceBase* GetAnimation() const { return Animation; }
    bool CanExecute(const class AAegisCharacter* Character) const;
protected:
    /** Name of the move */
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Name")
    FName Name = NAME_None;
    
    /** Display name of the move*/
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Display Name")
    FText DisplayName;
    
    /** Requirements that need to be fulfilled to perform this move*/
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Requirements")
    FAegisCharacterMoveRequirement Requirement;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
    UAnimSequenceBase* Animation = nullptr;
    
    
};

