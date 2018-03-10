// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Core/Combat/Combo/AegisCharacterComboComponent.h"
#include "Core/Combat/Guard/AegisCharacterGuardComponent.h"
#include "Core/Combat/LockOn/AegisCharacterLockOnComponent.h"
#include "GameFramework/Character.h"
#include "Core/Combat/Combo/AegisCharacterCombatState.h"
#include "Core/Input/AegisActionInput.h"
#include "Core/GameplayEffects/AegisGameplayEffectApplicationOrder.h"

//Begin Interfaces
#include "Core/Interfaces/AegisPhysicalImpactInterface.h"
#include "Core/Interfaces/AegisProcessGameplayEffectInterface.h"
#include "Core/Interfaces/AegisDamageInterface.h"
#include "Core/Interfaces/AegisKnockbackInterface.h"
#include "Core/Interfaces/AegisGuardStunInterface.h"
#include "GameplayTagAssetInterface.h"
//End Interfaces
#include "AegisCharacter.generated.h"



class UAegisActionInputBufferComponent;


/**
* AAegisCharacter is an ACharacter with the addition of an HP field.
* All characters from Aegis will inherit from this class. Be it NPCs
* Players or Enemies.
*/

UCLASS()
class AEGIS_API AAegisCharacter : public ACharacter, public IAegisProcessGameplayEffectInterface, public IAegisPhysicalImpactInterface, public IAegisKnockbackInterface, public IAegisDamageInterface, public IAegisGuardStunInterface, public IGameplayTagAssetInterface
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
    FORCEINLINE bool IsInGuardStun() const { return bInGuardStun; }
    
    FORCEINLINE bool IsInKnockback() const { return bInKnockback; }
	
	FORCEINLINE UFUNCTION(BlueprintCallable)
	bool IsDead() const { return bDead; }
	
    /** Returns true if the character's current state allows for any movement*/
    UFUNCTION(BlueprintCallable)
	bool CanMove() const;
    
	FORCEINLINE class AAegisWeapon* GetEquippedWeapon() const { return EquippedWeapon; }
	FORCEINLINE UAegisCharacterComboComponent* GetComboComponent() const { return ComboComponent; }
    FORCEINLINE UAegisCharacterGuardComponent* GetGuardComponent() const { return GuardComponent; }
    FORCEINLINE UAegisActionInputBufferComponent* GetInputBufferComponent() const { return InputBufferComponent;}
    FORCEINLINE UAegisCharacterLockOnComponent* GetLockOnComponent() const { return LockOnComponent; }
    
    EAegisCharacterLockOnState GetLockOnState() const;
    
    /** Resets the various Character states of the character. E.g bIsInHitStun, bInGuardStun, bInKnockback etc*/
    void ResetStatus();
    
    //IAegisProcessGameplayEffectInterface Begin
    virtual FAegisGameplayEffectApplicationOrder GetCurrentApplicationOrder() const override;

    //IAegisProcessGameplayEffectInterfaceEnd
    
    // Begin IAegisPhysicalImpactInterface
    virtual void OnPhysicalImpact() override;
    // End IAegisPhysicalImpactInterface
    
    // Begin IAegisKnockbackInterface
    virtual void OnKnockback(FVector KnockbackDirection, float KnockbackMagnitude) override;
    // End IAegisKnockbackInterface
    
    // Begin IAegisDamageInterface
    virtual void OnDamage(float DamageAmount) override;
    //End IAegisDamageInterface
    
    // Begin IAegisGuardStunInterface
    virtual void OnGuardStun() override;
    // End IAegisGuardStunInterface
    
    // Begin IGameplayTagAssetInterface
    virtual void GetOwnedGameplayTags(FGameplayTagContainer& TagContainer) const override { TagContainer = CharacterTagsContainer; return; }
    // End IGameplayTagAssetInterface

protected: 
    /** Function called when this character overlaps with another Actor */
    UFUNCTION(BlueprintCallable)
    virtual void OnAegisCharacterBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

    /** Character's maximum HP. Must be > 0.0f*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "HP", meta = (AllowPrivateAccess = "true"))
	float MaxHP = 0.0f;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
    FGameplayTagContainer CharacterTagsContainer;
	
	/** Character's current HP. Dies if < 0.0f*/
	float CurrentHP = 0.0f;

	/** True if character is in Super Mode*/
	bool bInSuperMode = false;

	/** True if character is currently in hit stun*/
	bool bIsInHitStun = false;
    
    /** True if character is in Guard Stun*/
    bool bInGuardStun = false;
    
    /** True if the character is in Knockback*/
    bool bInKnockback = false;
    
    /** True if the character is dead */
    bool bDead = false;
	
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

	/** Character's Guard Component Class to be used. Must be set in editor  */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GuardComponent")
    TSubclassOf<UAegisCharacterGuardComponent> GuardComponentClass = UAegisCharacterGuardComponent::StaticClass();
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GuardComponent")
	UAegisCharacterGuardComponent* GuardComponent = nullptr;
    
    /** Class of Lock On Component to be used for the Character. Must be set in Editor*/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LockOn")
    TSubclassOf<UAegisCharacterLockOnComponent> LockOnComponentClass = UAegisCharacterLockOnComponent::StaticClass();
    /** The Lock ON Component the Character will be using */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "LockOn")
    UAegisCharacterLockOnComponent* LockOnComponent = nullptr;
    
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Input Buffer")
    UAegisActionInputBufferComponent* InputBufferComponent = nullptr;

	/** The left hand socket of the character */
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Sockets")
	FName LeftHandSocket = NAME_None;

	/** The right hand socket of the character */
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Sockets")
	FName RightHandSocket = NAME_None;

private: 
#if !UE_BUILD_SHIPPINGB
	/** Checks if sockets exist and logs missing ones */
	void ValidateSockets();
#endif
    /** Creates all custom component that have their class set in BP */
    void CreatePostInitComponents();
    /** Assertion checks to make sure the character has no null components*/
    void ValidateCharacterComponents();
    
    //Begin Debug Functionality
    FAegisGameplayEffectApplicationOrder CreateDebugComboGFXApplicationOrder() const;
    void CreateDebugGuardComponent(); 
    //End Debug Functionality

};
