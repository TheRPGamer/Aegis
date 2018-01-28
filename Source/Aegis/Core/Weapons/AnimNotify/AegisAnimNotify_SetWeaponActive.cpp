// Fill out your copyright notice in the Description page of Project Settings.

#include "Aegis.h"
#include "AegisAnimNotify_SetWeaponActive.h"
#include "Core/Weapons/AegisWeapon.h"



void UAegisAnimNotify_SetWeaponActive::Notify(USkeletalMeshComponent* MeshComponent, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComponent, Animation); 
    if(AegisCharacterTarget)
    {
        AAegisWeapon* weapon = AegisCharacterTarget->GetEquippedWeapon();
        if(weapon)
        {
            weapon->SetCollisionActive(true);
        }
    }
    
    
}



