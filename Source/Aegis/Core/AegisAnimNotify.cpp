// Fill out your copyright notice in the Description page of Project Settings.

#include "Aegis.h"
#include "AegisAnimNotify.h"
#include "Core/Characters/AegisCharacter.h"


void UAegisAnimNotify::Notify(USkeletalMeshComponent* MeshComponent, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComponent, Animation); 
	if (MeshComponent)
	{
		AegisCharacterTarget = Cast<AAegisCharacter>(MeshComponent->GetOwner());
	}
}

