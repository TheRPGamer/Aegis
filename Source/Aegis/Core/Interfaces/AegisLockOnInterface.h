// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AegisLockOnInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UAegisLockOnInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * This Interface is meant to be a marking Interface. It's to help easily locate all AActors that can be locked on to
 * Overriding of OnLockON not necessary
 */
class AEGIS_API IAegisLockOnInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
    virtual void OnLockOn() { }
};
