// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AegisWeapon.generated.h"

class AAegisCharacter; 
UCLASS()
class AEGIS_API AAegisWeapon : public AActor
{
	GENERATED_BODY()

public:
    AAegisWeapon();
protected:
	/** Called when the game starts or when spawned */
	virtual void BeginPlay() override;

public:	
	/** Called every frame */
	virtual void Tick(float DeltaTime) override;

	/** Returns true if the weapon is active and can damage enemies*/
	FORCEINLINE UPROPERTY(BlueprintCallable)
	bool CanDamageTargets(){ return bCanDamageTargets; }

	FORCEINLINE UFUNCTION(BlueprintCallable)
	void SetCanDamageTargetsTrue() { bCanDamageTargets = true; }
	
	FORCEINLINE UFUNCTION(BlueprintCallable)
	void SetCanDamageTargetsFalse() { bCanDamageTargets = false; }
	

protected:
	/** Function called when the weapon overlaps with a target*/
	UFUNCTION(BlueprintCallable)
    virtual void OnWeaponBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	/** True if the weapon is currently active and and will damage targets it overlaps with*/
	bool bCanDamageTargets = false; 
	
	/** Damage this weapon deals on Melee Attack hit*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WeaponDamage")
	float MeleeAttackDamage = 0.0f;
	
	/** The weapon's Mesh. To be assigned in BP*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh")
	UMeshComponent* Mesh = nullptr; 

	
	
};
