// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Animation/AnimInstance.h"
#include "AegisCharacterAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class AEGIS_API UAegisCharacterAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
public: 
	explicit UAegisCharacterAnimInstance();
	virtual ~UAegisCharacterAnimInstance();
	
	/**
	* Calls the character's Reset Ground Melee State function
	* to set Ground Melee State to false
	*/
	UFUNCTION(BlueprintCallable)
	void ResetCharacterGroundMeleeState();

	/**
	* Call's the character's ResetGroundGuardState() to set 
	* its Guard State to false
	*/
	UFUNCTION(BlueprintCallable)
	void ResetCharacterGroundGuardState(); 
	
	/**
	* Function called when the character's idle state plays.
	* Acts as a safety net to ensure character will always be reset to 
	* Idle State
	*/
	UFUNCTION(BlueprintCallable)
	void OnIdleStateReset(); 
protected: 
	/*Function called every Animation Tick to update the State of the Character*/
	virtual void NativeUpdateAnimation(float DeltaSeconds) override; 

private: 
	/*True if the character is not on the ground*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "WalkAnimProperties", meta = (AllowPrivateAccess = "true") )
	bool bIsFalling = false;
	
	/*Character's current movement speed*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "WalkAnimProperties", meta = (AllowPrivateAccess = "true"))
	float MovementSpeed = 0.0f; 
	
	/*True if the character's state allows it to use Melee Attacks*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "WalkAnimProperties", meta = (AllowPrivateAccess = "true"))
	bool bCanUseMeleeAttack = false; 
	
	/*True if the character is currently performing a Melee Attack */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "WalkAnimProperties", meta = (AllowPrivateAccess = "true"))
	bool bIsInGroundMeleeAttack = false; 

	/*True if the character's state allows it to use Guard*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "WalkAnimProperties", meta = (AllowPrivateAccess = "true"))
	bool bCanUseGuard = false;

	/*True if the character is currently Guarding on the ground*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "WalkAnimProperties", meta = (AllowPrivateAccess = "true"))
	bool bIsInGroundGuard = false;
	
	/*True if the character is currently in a Hit Stun State*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "WalkAnimProperties", meta = (AllowPrivateAccess = "true"))
	bool bIsInHitStun = false;
	
	/*True if the character is the in the Dead State*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "WalkAnimProperties", meta = (AllowPrivateAccess = "true"))
	bool bIsDead = false; 

	
};
