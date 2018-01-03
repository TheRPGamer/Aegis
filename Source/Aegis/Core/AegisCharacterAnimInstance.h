// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Animation/AnimInstance.h"
#include "AegisCharacterAnimInstance.generated.h"

class AAegisCharacter;
class UAegisCharacterComboComponent;

/**
 * 
 */
UCLASS()
class AEGIS_API UAegisCharacterAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
public: 
	FORCEINLINE UFUNCTION(BlueprintCallable)
    AAegisCharacter* GetAegisCharacter() const {return Cast<AAegisCharacter>(TryGetPawnOwner());}

	UFUNCTION(BlueprintCallable)
	UAegisCharacterComboComponent* GetAegisCharacterComboComponent() const;

	/** Gets Character's current Combo Animation*/
	UFUNCTION(BlueprintCallable)
	UAnimSequenceBase* GetComboAnim() const;

	/** Returns true if character is currently in middle of a combo */
	UFUNCTION(BlueprintCallable)
	bool IsAegisCharacterInCombo() const;

	
protected: 
	/** Function called every Animation Tick to update the State of the Character*/
	virtual void NativeUpdateAnimation(float DeltaSeconds) override; 

private: 
	/** True if the character is not on the ground*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "WalkAnimProperties", meta = (AllowPrivateAccess = "true") )
	bool bFalling = false;
	
	/** Character's current movement speed*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "WalkAnimProperties", meta = (AllowPrivateAccess = "true"))
	float MovementSpeed = 0.0f; 
	
	/** True if the character is currently in a Hit Stun State*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "WalkAnimProperties", meta = (AllowPrivateAccess = "true"))
	bool bInHitStun = false;
	
	/** True if the character is the in the Dead State*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "WalkAnimProperties", meta = (AllowPrivateAccess = "true"))
	bool bDead = false;

	/** True if character is currently in a combo */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "WalkAnimProperties", meta = (AllowPrivateAccess = "true"))
	bool bInCombo = false;

	/** Debug thing. A variable that is always set to !bInCombo jus to 
	* check if there's anything wrong with Anim BP
	*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "WalkAnimProperties", meta = (AllowPrivateAccess = "true"))
	bool bTransitionOutOfCombo = false;


	/** The current combo animation to be played */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MeleeAnimProperties", meta = (AllowPrivateAccess = "true"))
	UAnimSequenceBase* CurrentComboAnimation = nullptr; 
	
	/** The next combo animation to be played */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MeleeAnimProperties", meta = (AllowPrivateAccess = "true"))
	UAnimSequenceBase* NextComboAnimation = nullptr;

};
