// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "Core/AegisCharacter.h"
#include "AegisAnimNotify.generated.h"

/**
 * Base class of all Aegis Character Anim Notifies
 */
UCLASS()
class AEGIS_API UAegisAnimNotify : public UAnimNotify
{
	GENERATED_BODY()
public: 
	/** Function called when teh Anim Notify is triggered */
	virtual void Notify(USkeletalMeshComponent* MeshComponent, UAnimSequenceBase* Animation) override;

protected: 
	/** Character the anim notify applies to */
	UPROPERTY()
	AAegisCharacter* AegisCharacterTarget = nullptr; 
	
	
	
};
