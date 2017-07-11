// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "AegisWeapon.generated.h"

class AAegisCharacter; 
UCLASS()
class AEGIS_API AAegisWeapon : public APawn
{
	GENERATED_BODY()

public:
	explicit AAegisWeapon();
	virtual ~AAegisWeapon(); 
protected:
	/* Called when the game starts or when spawned */
	virtual void BeginPlay() override;

public:	
	/* Called every frame */
	virtual void Tick(float DeltaTime) override;

	/* Called to bind functionality to input */
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	/*Returns true if the weapon is active and can damage enemies*/
	FORCEINLINE bool CanDamageTargets(){ return bCanDamageTargets; }

	

protected:
	/*Function called when the weapon overlaps with a target*/
	UFUNCTION(BlueprintCallable)
	void OnWeaponBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, 
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	/*True if the weapon is currently active and and will damage targets it overlaps with*/
	bool bCanDamageTargets = false; 
	
private: 
	/*Damage this weapon deals on Melee Attack hit*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WeaponDamage", meta = (AllowPrivateAccess = "true"))
	float MeleeAttackDamage = 0.0f;
	
	/*The weapon's Mesh. To be assigned in BP*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh", meta = (AllowPrivateAccess = "true"))
	UMeshComponent* Mesh = nullptr; 

	
	
};
