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
	void ResetCharacterInCombo();

	
	/** Make Character Equipped Weapon's collision volume active */
	UFUNCTION(BlueprintCallable)
	void MakeCharacterWeaponActive(); 

	/** Make Character Equipped Weapon's collision volume inactive */
	UFUNCTION(BlueprintCallable)
	void MakeCharacterWeaponInactive(); 
	
	
	UFUNCTION(BlueprintCallable)
	class AAegisCharacter* GetAegisCharacter(); 

	UFUNCTION(BlueprintCallable)
	class UAegisCharacterComboComponent* GetAegisCharacterComboComponent();

	/** Gets Combo Animation to be played form character's Combo Component */
	UFUNCTION(BlueprintCallable)
	UAnimSequence* GetComboAnimToPlay();

	/** Returns true if character is currently in middle of a combo */
	UFUNCTION(BlueprintCallable)
	bool IsAegisCharacterInCombo(); 

	/** Sets whether the Aegis Character is iwthin a Pause Combo Window */
	UFUNCTION(BlueprintCallable)
	void SetAegisCharacterInPauseComboWindow(bool bInValue);
protected: 
	/** Function called every Animation Tick to update the State of the Character*/
	virtual void NativeUpdateAnimation(float DeltaSeconds) override; 

private: 
	/*True if the character is not on the ground*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "WalkAnimProperties", meta = (AllowPrivateAccess = "true") )
	bool bIsFalling = false;
	
	/*Character's current movement speed*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "WalkAnimProperties", meta = (AllowPrivateAccess = "true"))
	float MovementSpeed = 0.0f; 
	
	/*True if the character is currently in a Hit Stun State*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "WalkAnimProperties", meta = (AllowPrivateAccess = "true"))
	bool bIsInHitStun = false;
	
	/*True if the character is the in the Dead State*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "WalkAnimProperties", meta = (AllowPrivateAccess = "true"))
	bool bIsDead = false; 

	/** True if character is currently in a combo */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "WalkAnimProperties", meta = (AllowPrivateAccess = "true"))
	bool bInCombo = false;

	/** The current combo animation to be played */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MeleeAnimProperties", meta = (AllowPrivateAccess = "true"))
	UAnimSequence* CurrentComboAnimation = nullptr; 
	
};
