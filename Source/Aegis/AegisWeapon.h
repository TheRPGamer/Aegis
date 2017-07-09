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
	// Sets default values for this pawn's properties
	AAegisWeapon();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	FORCEINLINE bool CanDamageTargets()
	{
		return bCanDamageTargets; 
	}

	FORCEINLINE AAegisCharacter* GetWeaponOwner() const
	{
		return Owner; 
	}
	FORCEINLINE void SetWeaponOwner(AAegisCharacter* owner)
	{
		Owner = owner; 
	}

protected:
	UFUNCTION(BlueprintCallable)
	void OnWeaponBeginOverlap(AActor* MyOverlappedActor, AActor* OtherActor); 
	
	bool bCanDamageTargets = false; 
	
private: 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WeaponDamage", meta = (AllowPrivateAccess = "true"))
	float Damage = 0.0f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh", meta = (AllowPrivateAccess = "true"))
	UMeshComponent* Mesh = nullptr; 

	AAegisCharacter* Owner; 
	
	
};
