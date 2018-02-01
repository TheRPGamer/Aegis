// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Core/Combat/Combo/AegisCharacterComboComponent.h"
#include "Core/Combat/Guard/AegisCharacterGuardComponent.h"
#include "GameFramework/Character.h"
#include "Core/Combat/Combo/AegisCharacterCombatState.h"
#include "Core/Input/AegisActionInput.h"
#include "Core/GameplayEffects/AegisGameplayEffectApplicationOrder.h"
//Begin Interfaces
#include "Core/Interfaces/AegisPhysicalImpactInterface.h"
#include "Core/Interfaces/AegisProcessGameplayEffectInterface.h"
#include "Core/Interfaces/AegisDamageInterface.h"
#include "Core/Interfaces/AegisKnockbackInterface.h"
//End Interfaces
#include "AegisCharacter.generated.h"

class UAegisActionInputBufferComponent;


/**
* AAegisCharacter is an ACharacter with the addition of an HP field.
* All characters from Aegis will inherit from this class. Be it NPCs
* Players or Enemies.
*/

UCLASS()
class AEGIS_API AAegisCharacter : public ACharacter, public IAegisProcessGameplayEffectInterface, public IAegisPhysicalImpactInterface, public IAegisKnockbackInterface, public IAegisDamageInterface
{
	GENERATED_BODY()

public:
	/** Sets default values for this character's properties */
	AAegisCharacter();
    /**
     * Callback function called after constructor and before BeginPlay()
     * All BP Properties will be updated at this point
     */
    virtual void PostInitProperties() override;
protected:
	/** Called when the game starts or when spawned */
	virtual void BeginPlay() override;

public:
	/** Function called when AegisCharacter is damaged*/
	virtual float TakeDamage(float DamageAmount, const struct FDamageEvent& DamageEvent, AController* EventInstigagor, AActor* DamageCauser) override; 

	FORCEINLINE UFUNCTION(BlueprintCallable)
	float GetCurrentHP() const { return CurrentHP; }
	
	FORCEINLINE UFUNCTION(BlueprintCallable)
	void SetCurrentHP(float newValue) { CurrentHP = newValue; }

	FORCEINLINE UFUNCTION(BlueprintCallable)
	float GetMaxHP() const { return MaxHP; }
    
     
    
    UFUNCTION(BlueprintCallable)
	bool IsInAir() const;
	
	FORCEINLINE UFUNCTION(BlueprintCallable)
	bool IsInSuperMode() const { return bInSuperMode; }
	
	
	FORCEINLINE UFUNCTION(BlueprintCallable)
	bool IsInHitStun() const{	return bIsInHitStun; }
	
	
	FORCEINLINE UFUNCTION(BlueprintCallable)
	bool IsDead() const { return (CurrentHP <= 0.0f); }
	
    FORCEINLINE EAegisCharacterLockOnState GetLockOnState() const { return LockOnState; }
    /** Returns true if the character's current state allows for any movement*/
    UFUNCTION(BlueprintCallable)
	bool CanMove() const;
	
	FORCEINLINE class AAegisWeapon* GetEquippedWeapon() const { return EquippedWeapon; }
	
	FORCEINLINE UAegisCharacterComboComponent* GetComboComponent() const { return ComboComponent; }
    
    FORCEINLINE UAegisActionInputBufferComponent* GetInputBufferComponent() const { return InputBufferComponent;}
    
    //IAegisProcessGameplayEffectInterface Begin
    virtual FAegisGameplayEffectApplicationOrder GetCurrentApplicationOrder() const override;

    //IAegisProcessGameplayEffectInterfaceEnd
    
    // Begin IAegisPhysicalImpactInterface
    virtual void OnPhysicalImpact() override;
    // End IAegisPhysicalImpactInterface
    
    // Begin IAegisKnockbackInterface
    virtual void OnKnockback() override;
    // End IAegisKnockbackInterface
    
    // Begin IAegisDamageInterface
    virtual void OnDamage() override;
    //End IAegisDamageInterface
protected: 
    /** Function called when this character overlaps with another Actor */
    virtual void OnAegisCharacterBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

    /** Character's maximum HP. Must be > 0.0f*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "HP", meta = (AllowPrivateAccess = "true"))
	float MaxHP = 0.0f; 
	
	/** Character's current HP. Dies if < 0.0f*/
	float CurrentHP = 0.0f;

	/** True if character is in Super Mode*/
	bool bInSuperMode = false;

	/** True if character is currently in hit stun*/
	bool bIsInHitStun = false;
	
	/** Class of weapon that the character will have equipped*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Equipped Weapon")
	TSubclassOf<class AAegisWeapon> EquippedWeaponClass = nullptr;

	/** Character's currently equipped weapon */
	UPROPERTY()
	class AAegisWeapon* EquippedWeapon = nullptr;

	/** Character's Combo Component Class to be used. Must be set in editor  */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ComboCombponent")
	TSubclassOf<UAegisCharacterComboComponent> ComboComponentClass = UAegisCharacterComboComponent::StaticClass();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "ComboCombponent")
	UAegisCharacterComboComponent* ComboComponent = nullptr;

	/** Character's Combo Component Class to be used. Must be set in editor  */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GuardComponent")
    TSubclassOf<UAegisCharacterGuardComponent> GuardComponentClass = UAegisCharacterGuardComponent::StaticClass();
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GuardComponent")
	UAegisCharacterGuardComponent* GuardComponent = nullptr;
    
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Input Buffer")
    UAegisActionInputBufferComponent* InputBufferComponent = nullptr;

	/** The left hand socket of the character */
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Sockets")
	FName LeftHandSocket = NAME_None;

	/** The right hand socket of the character */
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Sockets")
	FName RightHandSocket = NAME_None;
    
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Lock On State")
    EAegisCharacterLockOnState LockOnState = EAegisCharacterLockOnState::NotLockedOn;

private: 
#if !UE_BUILD_SHIPPINGB
	/** Checks if sockets exist and logs missing ones */
	void ValidateSockets();
#endif
    /** Creates all custom component that have their class set in BP */
    void CreatePostInitComponents();
    /** Assertion checks to make sure the character has no null components*/
    void ValidateCharacterComponents();

};
