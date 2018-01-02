// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/DamageType.h"
#include "AegisDamageType.generated.h"

/**
 * Base class from which all Damage Types in Aegis are derived from 
 */
UCLASS()
class AEGIS_API UAegisDamageType : public UDamageType
{
	GENERATED_BODY()
public: 

protected: 
	/** Damage Multiplier associated with this Damage Type */
	float Multiplier = 0.f; 

	
	
	
};
