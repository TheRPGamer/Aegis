// Fill out your copyright notice in the Description page of Project Settings.

#include "Aegis.h"
#include "AegisAnimNotify_GuardEnd.h"



void UAegisAnimNotify_GuardEnd::Notify(USkeletalMeshComponent* MeshComponent, UAnimSequenceBase* Animation)
{
	if (AegisCharacterTarget)
	{
		auto guardComp = AegisCharacterTarget->GetGuardComponent();
		if (guardComp)
		{
            guardComp->OnEndGuard();
		}
	}
}

