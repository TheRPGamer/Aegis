// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Core/GameplayEffects/AegisGameplayEffectApplicationOrder.h"
#include "Core/Interfaces/AegisProcessGameplayEffectInterface.h"
#include "AegisProjectile.generated.h"
class UAegisGameplayEffectBufferComponent;


UCLASS()
class AEGIS_API AAegisProjectile : public AActor  
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
};
