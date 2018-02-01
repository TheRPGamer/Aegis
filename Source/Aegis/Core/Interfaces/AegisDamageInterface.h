// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AegisDamageInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UAegisDamageInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class AEGIS_API IAegisDamageInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
    public:
    virtual void OnDamage() PURE_VIRTUAL(IAegisDamageInterface::OnDamage, );
	
};
