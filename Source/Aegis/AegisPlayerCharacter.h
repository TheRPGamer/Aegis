// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AegisCharacter.h"
#include "AegisPlayerCharacter.generated.h"

/**
 * 
 */
UCLASS()
class AEGIS_API AAegisPlayerCharacter : public AAegisCharacter
{
	GENERATED_BODY()
	
public: 
	explicit AAegisPlayerCharacter(); 
	virtual ~AAegisPlayerCharacter(); 
protected:
	/* Called when the game starts or when spawned */
	virtual void BeginPlay() override;

public:
	/*Called every frame*/
	virtual void Tick(float DeltaTime) override;

	/*Called to bind functionality to input*/
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private: 
	void MoveForward(float Value); 
	void MoveRight(float Value); 

	void OnMeleeAttackPressed(); 
	void OnMeleeAttackReleased(); 

	void OnLockOnPressed(); 
	void OnLockOnReleased(); 

	void OnSuperModePressed(); 
	void OnSuperModeReleased(); 
	
	bool IsInputDirectionTowardLockOnTarget(); 
	bool IsInputDirectionOppositeLockOnTarget(); 
	float CalculateAngleBetweenInputDirectionAndLockOnTarget();

	float GetMeleeAttackInputTimeDown();

	float InputDirectionToLockOnTargetAngleTolerance = 20.0f; 
	
	USpringArmComponent* ThirdPersonSpringArm; 
	UCameraComponent* ThirdPersonCamera; 
};
