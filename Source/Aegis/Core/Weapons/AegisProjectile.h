// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Core/GameplayEffects/AegisGameplayEffectApplicationOrder.h"

//Interfaces
#include "Core/Interfaces/AegisProcessGameplayEffectInterface.h"
#include "Core/Interfaces/AegisReflectInterface.h"
#include "AegisProjectile.generated.h"



UCLASS()
class AEGIS_API AAegisProjectile : public AActor, public IAegisProcessGameplayEffectInterface, public IAegisReflectInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAegisProjectile();
    virtual void PostInitProperties() override; 
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
    /** Delegate called when this projectile Hits an Actor*/
UFUNCTION(BlueprintCallable)
    void OnHit(AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
    
    // Begin IAegisProcessGameplayEffectInterface
    FORCEINLINE virtual FAegisGameplayEffectApplicationOrder GetCurrentApplicationOrder() const override { return CollisionGFX; }

    // End IAegisProcessGameplayEffect Interface
    
    // Begin IAegisReflectInterface
    virtual void OnReflect() override;
    // End IAegisReflectInterface

protected:
    
    
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Movement")
    UProjectileMovementComponent* ProjectileMovementComponent = nullptr;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Collision Component")
    USphereComponent* SphereCollisionComponent = nullptr;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Mesh")
    UMeshComponent* Mesh = nullptr;
    
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Collision Component")
    float SphereRadius = 0.0f;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Life Span")
    float LifeSpan = 0.0f;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay Effects")
    FAegisGameplayEffectApplicationOrder CollisionGFX;
};
