// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/AegisAnimNotify.h"
#include "AegisAnimNotify_SetWeaponInactive.generated.h"

/**
 * 
 */
UCLASS()
class AEGIS_API UAegisAnimNotify_SetWeaponInactive : public UAegisAnimNotify
{
	GENERATED_BODY()
public: 
	/** Function called when Anim Notify is triggered */
	virtual void Notify(USkeletalMeshComponent* MeshComponent, UAnimSequenceBase* Animation) override;

	
	
};
