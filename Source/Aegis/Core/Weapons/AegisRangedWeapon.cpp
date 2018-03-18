// Fill out your copyright notice in the Description page of Project Settings.

#include "Aegis.h"
#include "Core/Weapons/AegisRangedWeapon.h"

FAegisRangedAttack::FAegisRangedAttack()
{
    
    
}

void FAegisRangedAttack::Execute()
{
    for(auto& spawnParam : ProjectileSpawnParams)
    {
        AActor* target = nullptr;
        if(!target)
        {
            continue;
        }
        
    
        
    }
}

AAegisRangedWeapon::AAegisRangedWeapon()
{
    
}
void AAegisRangedWeapon::ExecuteRangedAttack()
{
    if(RangedAttacks.Num() < 1)
    {
        return;
    }
    //Purely debug hack thing for now
    const FAegisRangedAttack& rangedAttack = RangedAttacks[0];
}
