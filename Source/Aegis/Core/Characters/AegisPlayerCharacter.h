// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Core/Characters/AegisCharacter.h"
#include "Core/Weapons/AegisProjectile.h"
#include "AegisPlayerCharacter.generated.h"

/**
 * 
 */

UCLASS()
class AEGIS_API AAegisPlayerCharacter : public AAegisCharacter
{
	GENERATED_BODY()
	
public: 
	AAegisPlayerCharacter(); 

protected:
	/** Called when the game starts or when spawned */
	virtual void BeginPlay() override;

public:
	/** Called to bind functionality to input*/
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private: 
	/** Function called when character moves in X Axis*/
	void MoveForward(float Value); 
	
	/** Function called when character moves in Y Axis*/
	void MoveRight(float Value); 

	/** Function called when Melee Attack Button is Pressed*/
	void OnMeleeAttackPressed(); 
	/** Function called when Melee Attack Button is Released */
	void OnMeleeAttackReleased(); 

	/** Function called when Lock On Button is pressed*/
	void OnLockOnPressed(); 
	/* Function called when Lock On Button is released*/
	void OnLockOnReleased(); 

	/** Function called when Super Mode Button is Pressed*/
	void OnSuperModePressed(); 
	/** Function called when Super Mode button Released*/
	void OnSuperModeReleased(); 
	
	/** Function called when the Guard Button is pressed*/
	void OnGuardPressed();
	
	/** Function called when Guard Button is released*/
	void OnGuardReleased(); 
	
	/**
	* Returns true ifthe character's input direction is toward the lock 
	* on target +- tolerance angle
	*/
	bool IsInputDirectionTowardLockOnTarget(); 
	
	/**
	* Returns true if the character's input direction is opposite 
	* to the lock on target +- a tolerance angle
	*/
	bool IsInputDirectionOppositeLockOnTarget(); 
	
	/** Calculatese the angle in RADIANS between the character's input direction and lock on target */
	float CalculateAngleBetweenInputDirectionAndLockOnTarget();

	/** Function called when player takes damage from attack*/
	UFUNCTION(BlueprintCallable)
	virtual float TakeDamage(float DamageAmount, const struct FDamageEvent& DamageEvent,
			AController* EventInstigagor, AActor* DamageCauser) override; 
	
	/** Tolerance angle when deciding if character input is toward/away from target */
	float InputDirectionToLockOnTargetAngleTolerance = 20.0f; 
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* ThirdPersonSpringArm; 
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	UCameraComponent* ThirdPersonCamera; 
	
	/** Debug Functions and Variables */
protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TSubclassOf<AAegisProjectile> ProjectileClass = nullptr;
UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float DebugProjectileDisplacement = 0.f;
    
    void DebugShootProjectile();
    
    void StartTakeDamageTimer();
	void SimulateTakeDamage();
    void TestGuardComponent();
    void TestGameplayEffectSystem();
	FTimerHandle TakeDamageTimerHandle; 
	bool bTimerActive = false; 
};
