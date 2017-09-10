// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/AegisAnimNotify.h"
#include "AegisAnimNotify_ClosePauseWindow.generated.h"

/**
 * Anim Notify to turn the Aegis Character's ComboState bInPauseComboWindow parameter to false 
 */
UCLASS()
class AEGIS_API UAegisAnimNotify_ClosePauseWindow : public UAegisAnimNotify
{
	GENERATED_BODY()
public:
	/** Function call when Anim Notify is triggered */
	void Notify(USkeletalMeshComponent* MeshComponent, UAnimSequenceBase* Animation) override;

	
	
	
};
