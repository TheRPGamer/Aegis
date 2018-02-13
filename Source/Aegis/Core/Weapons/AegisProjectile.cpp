// Fill out your copyright notice in the Description page of Project Settings.

#include "Aegis.h"
#include "AegisProjectile.h"
#include "Core/GameplayEffects/AegisGameplayEffectApplicationInfo.h"
#include "Core/GameplayEffects/AegisActorGameplayEffectApplier.h"





// Sets default values
AAegisProjectile::AAegisProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
    
    
    
    Mesh = CreateDefaultSubobject<USkeletalMeshComponent>("Mesh");
    if (Mesh)
    {
        RootComponent = Mesh;
        Mesh->bGenerateOverlapEvents = true;
    }
    
    ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>("Projectile Movement");
    if(ProjectileMovementComponent)
    {
        ProjectileMovementComponent->SetUpdatedComponent(RootComponent);
        ProjectileMovementComponent->InitialSpeed = 300.0f;
        ProjectileMovementComponent->MaxSpeed = 300.0f;
        ProjectileMovementComponent->bRotationFollowsVelocity = true;
        ProjectileMovementComponent->bShouldBounce = true;
        ProjectileMovementComponent->ProjectileGravityScale = 0.0f; 
    }
    
}

void AAegisProjectile::PostInitProperties()
{
    Super::PostInitProperties(); 
    InitialLifeSpan = LifeSpan;
}

// Called when the game starts or when spawned
void AAegisProjectile::BeginPlay()
{
	Super::BeginPlay();
    if(Mesh)
    {
        Mesh->OnComponentBeginOverlap.AddDynamic(this, &AAegisProjectile::OnProjectileBeginOverlap);
        bCollisionActive = true; 

    }
	
}

// Called every frame
void AAegisProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AAegisProjectile::OnHit(AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
    UE_LOG(AegisGameplayEffectLog, Log, TEXT("AAegisProjectile::OnReflect"));
}


void AAegisProjectile::OnProjectileBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
                                        int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    //last check is if other actor is self
    if(!bCollisionActive || !OtherActor || (GetUniqueID() == OtherActor->GetUniqueID()) )
    {
        return;
    }
    AActor* owner = GetOwner();
    // check if other actor is owner. Ignore that case
    if(owner)
    {
        if(owner->GetUniqueID() == OtherActor->GetUniqueID())
        {
            return;
        }
    }
    Destroy();
}

// Begin IAegisReflectInterface
void AAegisProjectile::OnReflect()
{
    
}
//End IAegisReflectInterfaceFVector
