// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Animation/AnimInstance.h"
#include "AegisCharacterAnimInstance.generated.h"

class AAegisCharacter;
class UAegisCharacterComboComponent;

/**
 * 
 */
UCLASS(transient, Blueprintable)
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
	UAnimMontage* GetComboAnim() const;
    /**
     * Plays the provided Combo Animation.
     * IMPORTANT: Changes EAnimationMOde of USkeletalMeshComponent to AnimationSingleNode
     * IMPORTANT: Removes control of aniamtion playback from UAegisCharacterAnimInstance. jjj
     */
    void PlayComboAnimation(UAnimSequenceBase* Base);
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
    
};
