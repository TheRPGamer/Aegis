// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/Weapons/AegisWeapon.h"
#include "Core/Weapons/AegisProjectile.h"
#include "AegisRangedWeapon.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct FAegisRangedAttack
{
    GENERATED_BODY()
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Projectile ")
    AAegisProjectile* Projectile = nullptr;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Projectile")
    FVector ProjectileSpawnLocation;
    
};

UCLASS()
class AEGIS_API AAegisRangedWeapon : public AAegisWeapon
{
	GENERATED_BODY()
public:
    AAegisRangedWeapon();
    
protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Projectile Type")
    TSubclassOf<AAegisProjectile> ProjectileClass  = AAegisProjectile::StaticClass();
    
	
	
	
	
};
