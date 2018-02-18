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
    
    virtual void OnSpawn(const struct FAegisProjectileSpawnParams& SpawnParams ) { }
    
    virtual void OnFire() { };
    /** Delegate called when this projectile Hits an Actor*/
UFUNCTION(BlueprintCallable)
    void OnHit(AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
    
    // Begin IAegisProcessGameplayEffectInterface
    FORCEINLINE virtual FAegisGameplayEffectApplicationOrder GetCurrentApplicationOrder() const override { return CollisionGFX; }
    
    FORCEINLINE virtual UProjectileMovementComponent* GetProjectileMovementComponent() { return ProjectileMovementComponent; }
    
    // End IAegisProcessGameplayEffect Interface
    
    // Begin IAegisReflectInterface
    virtual void OnReflect() override;
    // End IAegisReflectInterface

protected:
    UFUNCTION(BlueprintCallable)
    virtual void OnProjectileBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

    
    
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Movement")
    UProjectileMovementComponent* ProjectileMovementComponent = nullptr;
    
    
    
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Mesh")
    UMeshComponent* Mesh = nullptr;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Life Span")
    float LifeSpan = 0.0f;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay Effects")
    FAegisGameplayEffectApplicationOrder CollisionGFX;
    
    UPROPERTY(EditAnywhere, BLueprintReadWrite)
    bool bCollisionActive = false;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float InitialSpeed = 0.f;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float MaxSpeed = 0.f;
    
    bool bReflected = false;
};


USTRUCT(BlueprintType)
struct AEGIS_API FAegisProjectileSpawnParams
{
    GENERATED_BODY()
public:
    FAegisProjectileSpawnParams() { }
FORCEINLINE     AActor* GetTarget() const { return Target; }
    FORCEINLINE void SetTarget(AActor* InTarget) { Target = InTarget; }
    
    FORCEINLINE TSubclassOf<AAegisProjectile> GetProjectileClass() const { return ProjectileClass; }
    FORCEINLINE FVector GetSpawnLocation() const { return (Target) ? Target->GetActorLocation() + LocationOffset : LocationOffset; }
    
    //FORCEINLINE  FRotator GetSpawnRotation(); const { return (Target) ? Target->Rotaion + RotationOffset : RotationOffset; }
protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TSubclassOf<AAegisProjectile> ProjectileClass = nullptr;
    
    /** Target the projectile will be spawned relative to */
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    AActor* Target = nullptr;
    
    /** Location offset from  the position of the Target. Will be added to Target's location */
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FVector LocationOffset;
    
    /** Rotation relative to the Target's rotation. Will be added to Target's rotation.*/
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FRotator RotationOffset;
};

