// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Core/AegisCharacter.h"
#include "AegisPlayerCharacter.generated.h"

/**
 * 
 */

enum class EInputState
{
	//Char Locked On && Velocity Vector Toward Target
	LockOnTowardsTarget,
	//Char Locked On && Velocity Vector Away From Target
	LockOnOppositeFromTarget,
	//Char Locked On && Char not moving 
	LockOnNeutral,
	//Char not locked on and not moving 
	Neutral
};

enum class ECharacterCombatState
{
	Ground, 
	SuperGround, 
	Air, 
	SuperAir
};

enum class EInputCombatCombinedState
{
	//Either Combat State or Input State is invalid
	Invalid, 

	GroundLockOnTowardTarget, 
	SuperGroundLockOnTowardTarget, 
	AirLockOnTowardTarget, 
	SuperAirLockOnTowardTarget, 
	
	GroundLockOnOppositeTarget,
	SuperGroundLockOnOppositeTarget,
	AirLockOnOppositeTarget,
	SuperAirLockOnOppositeTarget,

	GroundLockOnNeutral, 
	SuperGroundLockOnNeutral, 
	AirLockOnNeutral,
	SuperAirLockOnNeutral, 

	GroundNeutral, 
	SuperGroundNeutral, 
	AirNeutral, 
	SuperAirNeutral
};
UCLASS()
class AEGIS_API AAegisPlayerCharacter : public AAegisCharacter
{
	GENERATED_BODY()
	
public: 
	explicit AAegisPlayerCharacter(); 

protected:
	/** Called when the game starts or when spawned */
	virtual void BeginPlay() override;

public:
	/** Called every frame*/
	virtual void Tick(float DeltaTime) override;

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

	/** Get amount of time the Melee Attack Button is held down*/
	float GetMeleeAttackInputTimeDown() const;

	/** Get amount of time the Melee Attack Button is held down*/
	float GetGuardInputTimeDown() const;
	
	/** Function called when taking a direct hit by an attack */
	void GuardLevel0(float OriginalDamageTaken);

	/**Function called when a Level 1 Guard is performed */
	void GuardLevel1(float OriginalDamageTaken); 
	
	/** Called when a Levle 2 Guard is performed */
	void GuardLevel2(float OriginalDamageTaken); 
	
	/** Called when a Level 3 Guard is performed */
	void GuardLevel3(); 

	/** Determines the Guard Level on blocking an attack. */
	int32 DetermineGuardLevel(); 
	
	/** Function called when player takes damage from attack*/
	UFUNCTION(BlueprintCallable)
	virtual float TakeDamage(float DamageAmount, const struct FDamageEvent& DamageEvent,
			AController* EventInstigagor, AActor* DamageCauser) override; 
	
	/** Tolerance angle when deciding if character input is toward/away from target */
	float InputDirectionToLockOnTargetAngleTolerance = 20.0f; 
	
	/** Used to determine Guard Level. Any number of frames <= Level3GuardFrameThreshold guarantees Level 3 Guard */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Guard", meta = (AllowPrivateAccess = "true"))
	float Level3GuardFrameThreshold = 15.0f;
	
	/** Used to determine Guard Level. Any number of frames >= Level1GuardFrameThreshold guarantees Level 1 Guard */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Guard", meta = (AllowPrivateAccess = "true"))
	float Level1GuardFrameThreshold = 30.0f;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* ThirdPersonSpringArm; 
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	UCameraComponent* ThirdPersonCamera; 
	
	EInputState DetermineInputState();
	ECharacterCombatState DetermineCharacterCombatState();
	EInputCombatCombinedState DetermineInputCombatCombinedState(EInputState InputState, ECharacterCombatState CombatState);
};
