// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Core/Combat/Combo/AegisCharacterComboComponent.h"
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
	/** Sets default values for this character's properties */
	AAegisCharacter();

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

	/** Returns character's max HP*/
	FORCEINLINE UFUNCTION(BlueprintCallable)
	float GetMaxHP() const { return MaxHP; }

	/** Returns true if the character is currently in the air*/
	FORCEINLINE UFUNCTION(BlueprintCallable)
	bool IsInAir() const;
	

	/** Returns true if character is currently in Super Mode*/
	FORCEINLINE UFUNCTION(BlueprintCallable)
	bool IsInSuperMode() const { return bInSuperMode; }
	
	/** Returns true if character is currently in Hit Stun State*/
	FORCEINLINE UFUNCTION(BlueprintCallable)
	bool IsInHitStun() const{	return bIsInHitStun; }
	
	/** Returns true if character is in the Dead State*/
	FORCEINLINE UFUNCTION(BlueprintCallable)
	bool IsDead() const { return (CurrentHP <= 0.0f); }
	
	/** Returns true if the character's current state allows for any movement*/
	FORCEINLINE UFUNCTION(BlueprintCallable)
	bool CanMove() const;
	
	FORCEINLINE class AAegisWeapon* GetEquippedWeapon() const { return EquippedWeapon; }
	
	FORCEINLINE class UAegisCharacterComboComponent* GetComboComponent() { return ComboComponent; }
protected: 
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
	TSubclassOf<class UAegisCharacterComboComponent> ComboComponentClass = UAegisCharacterComboComponent::StaticClass();

	/** Character's Combo Component */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "ComboCombponent")
	class UAegisCharacterComboComponent* ComboComponent = nullptr;


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

};
