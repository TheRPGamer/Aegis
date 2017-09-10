// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/AegisAnimNotify.h"
#include "AegisAnimNotify_EndCombo.generated.h"

/**
 * Anim Notify called when a AegisCharacterComboState animation has reached the end of the combo attack
 */
UCLASS()
class AEGIS_API UAegisAnimNotify_EndCombo : public UAegisAnimNotify
{
	GENERATED_BODY()
public:
	/** Function called when Anim Notify is trigggered */
	virtual void Notify(USkeletalMeshComponent* MeshComponent, UAnimSequenceBase* Animation) override;

	
	
	
};
