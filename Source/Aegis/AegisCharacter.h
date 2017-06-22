// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "AegisCharacter.generated.h"
/**
* AAegisCharacter is an ACharacter with the addition of an HP field.
* All characters from Aegis will inherit from this class. Be it NPCs
* Players or Enemies.
*/

UCLASS()
class AEGIS_API AAegisCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	/* Sets default values for this character's properties */
	AAegisCharacter();

protected:
	/* Called when the game starts or when spawned */
	virtual void BeginPlay() override;

public:	
	/*Called every frame*/
	virtual void Tick(float DeltaTime) override;

	/*Called to bind functionality to input*/
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	FORCEINLINE float GetCurrentHP() const
	{
		return CurrentHP; 
	}

	void SetCurrentHP(float newValue)
	{
		CurrentHP = newValue; 
	}

	FORCEINLINE float GetMaxHP() const
	{
		return MaxHP; 
	}

protected: 
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "HP", meta = (AllowPrivateAccess = "true"))
	float MaxHP = 0.0f; 
	
	float CurrentHP = 0.0f;

};
