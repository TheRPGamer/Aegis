// Fill out your copyright notice in the Description page of Project Settings.

#include "Aegis.h"
#include "AegisAnimNotify_SetWeaponInactive.h"
#include "Core/Weapons/AegisWeapon.h"

void UAegisAnimNotify_SetWeaponInactive::Notify(USkeletalMeshComponent* MeshComponent, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComponent, Animation); 
    if(AegisCharacterTarget)
    {
        AAegisWeapon* weapon = AegisCharacterTarget->GetEquippedWeapon();
        if(weapon)
        {
            weapon->SetCollisionActive(false); 
        }
    }
     
    
}



