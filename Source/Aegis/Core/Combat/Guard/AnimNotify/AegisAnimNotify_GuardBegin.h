// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/AegisAnimNotify.h"
#include "AegisAnimNotify_GuardBegin.generated.h"

/**
 * Anim NOtify that turns the Aegis Character's in pause combo state to true 
 */
UCLASS()
class AEGIS_API UAegisAnimNotify_GuardBegin : public UAegisAnimNotify
{
	GENERATED_BODY()
public: 
	/** Function called when Anim Notify is triggered */
	void Notify(USkeletalMeshComponent* MeshComponent, UAnimSequenceBase* Animation) override;
	
	
	
	
};
