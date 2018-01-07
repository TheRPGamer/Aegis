// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Core/GameplayEffects/AegisGameplayEffectExecutionOrder.h"
#include "Core/Interfaces/AegisProcessGameplayEffectInterface.h"
#include "AegisProjectile.generated.h"
class UAegisGameplayEffectBufferComponent;
struct FAegisGameplayEffectTriggerInfo; 

UCLASS()
class AEGIS_API AAegisProjectile : public AActor, public IAegisProcessGameplayEffectInterface
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
    
    //Begin IAegisProcessGameplayEffectInterface
    FORCEINLINE UAegisGameplayEffectBufferComponent* GetGameplayEffectComponent() const override { return GameplayEffectComponent; }
    FAegisGameplayEffectExecutionOrder GetCurrentExecutionOrder() const override { return CollisionEffects; }
    void ProcessInstigatorEffects(FAegisGameplayEffectTriggerInfo& TriggerInfo) override;
    void ProcessCauserEffects(FAegisGameplayEffectTriggerInfo& TriggerInfo) override;
    //End IAegisProcessGameplayEffectInterface
    void OnHit(AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit); 

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
    FAegisGameplayEffectExecutionOrder CollisionEffects;
    
private:
    UPROPERTY()
    UAegisGameplayEffectBufferComponent* GameplayEffectComponent = nullptr;
    
    
    

	
	
};
