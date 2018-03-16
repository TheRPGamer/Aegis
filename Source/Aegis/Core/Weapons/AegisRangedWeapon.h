// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/Weapons/AegisWeapon.h"
#include "Core/Weapons/AegisProjectile.h"
#include "Components/TimelineComponent.h"
#include "AegisRangedWeapon.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct AEGIS_API FAegisRangedAttack
{
    GENERATED_BODY()
public:
    FAegisRangedAttack();
    
    /** Name of this Ranged Attack*/
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName Name = NAME_None;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FText DisplayName;
    
    /** Executes the Ranged Attack */
    void Execute();
    
    /** An array of projectiles to spawn as part of this Ranged Attack */
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<FAegisProjectileSpawnParams> ProjectileSpawnParams;
    
    /** Timeline used to coordinate when the projectiles will spawn */
    FTimeline SpawnTimeline;
    /** Timeline used to coordinate when all the projectiles in the TArray fire*/
    FTimeline ShootTimeline; 
    
    
    
    
    
    
};

UCLASS()
class AEGIS_API AAegisRangedWeapon : public AAegisWeapon
{
	GENERATED_BODY()
public:
    AAegisRangedWeapon();

    virtual void ExecuteRangedAttack();

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<FAegisRangedAttack> RangedAttacks;
    

};
