// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SplineComponent.h"
#include "Components/TimelineComponent.h"
#include "Core/GameplayEffects/AegisGameplayEffectApplicationOrder.h"

//Interfaces
#include "Core/Interfaces/AegisProcessGameplayEffectInterface.h"
#include "Core/Interfaces/AegisReflectInterface.h"
#include "GameplayTagAssetInterface.h"
#include "AegisProjectile.generated.h"


USTRUCT(BlueprintType)
struct AEGIS_API FAegisProjectileTrajectoryParams
{
    GENERATED_BODY()
public:
    FAegisProjectileTrajectoryParams() { }
    FORCEINLINE FVector GetStartLocation() const { return StartLocation; }
    FORCEINLINE FVector GetEndLocation() const { return EndLocation; }
    FORCEINLINE FVector GetStartTangent() const { return StartTangent; }
    FORCEINLINE FVector GetEndTangent() const { return EndTangent; }
    
    FORCEINLINE void SetStartLocation(const FVector& InStartLocation) { StartLocation = InStartLocation; }
    FORCEINLINE void SetEndLocation(const FVector& InEndLocation) { EndLocation = InEndLocation; }
    FORCEINLINE void SetStartTangent(const FVector& InStartTangent) { StartTangent = InStartTangent; }
    FORCEINLINE void SetEndTangent(const FVector& InEndTangent) { EndTangent = InEndTangent; }
protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FVector StartLocation;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FVector EndLocation;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FVector StartTangent;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FVector EndTangent;
    
};


UCLASS()
class AEGIS_API AAegisProjectile : public AActor, public IAegisProcessGameplayEffectInterface, public IAegisReflectInterface, public IGameplayTagAssetInterface
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
    
    UFUNCTION(BlueprintCallable)
    void OnUpdateTrajectory(float Value);
    
    UFUNCTION(BlueprintCallable)
    void OnFinishTrajectory();
    
    // Begin IAegisProcessGameplayEffectInterface
    FORCEINLINE virtual FAegisGameplayEffectApplicationOrder GetCurrentApplicationOrder() const override { return CollisionGFX; }
    // End IAegisProcessGameplayEffect Interface
    
    // Begin IAegisReflectInterface
    virtual void OnReflect() override;
    // End IAegisReflectInterface
    
    // Begin IGameplayTagAssetInterface
    UFUNCTION(BlueprintCallable)
    virtual void GetOwnedGameplayTags(FGameplayTagContainer& TagContainer) const override { TagContainer = CharacterTagsContainer; return; }
    // End IGameplayTagAssetInterface

protected:
    void ConstructTrajectory();
    
    UFUNCTION(BlueprintCallable)
    virtual void OnProjectileBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
    FGameplayTagContainer CharacterTagsContainer;
    
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Mesh")
    UMeshComponent* Mesh = nullptr;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Trajectory")
    UCurveFloat* TrajectoryCurve  = nullptr;
    
    /** Timeline used to follow the Spline Component */
    FTimeline TrajectoryTimeline;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Trajectory")
    USplineComponent* TrajectorySplineComponent = nullptr;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Trjactory")
    FAegisProjectileTrajectoryParams TrjectoryParams;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Life Span")
    float LifeSpan = 0.0f;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay Effects")
    FAegisGameplayEffectApplicationOrder CollisionGFX;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bCollisionActive = false;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float InitialSpeed = 0.f;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float MaxSpeed = 0.f;
    
    bool bReflected = false;
};




/**
 * Gives Location and Rotation of projectile to be spawned
 * Can be chosen if spawning is relative to an Actor
 */
USTRUCT(BlueprintType)
struct AEGIS_API FAegisProjectileSpawnParams
{
    GENERATED_BODY()
public:
    FAegisProjectileSpawnParams() { }
    //FVector SpawnLocation;
    //FVector LocationOffset;
    //FRotator Rotation;
    //bool bParentToTarget = false;
    //bool bTargetIsOwner = true;
    
};


