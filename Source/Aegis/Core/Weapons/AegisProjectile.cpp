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
    TrajectorySplineComponent = CreateDefaultSubobject<USplineComponent>("TrajectorySpline");
    if(TrajectorySplineComponent)
    {
        //draw the trajectory on screen
        TrajectorySplineComponent->SetDrawDebug(true);
    }
    
}

void AAegisProjectile::PostInitProperties()
{
    Super::PostInitProperties();
}
// Called when the game starts or when spawned
void AAegisProjectile::BeginPlay()
{
	Super::BeginPlay();
    if(Mesh)
    {
        Mesh->OnComponentBeginOverlap.AddDynamic(this, &AAegisProjectile::OnProjectileBeginOverlap);
    }
    
    if(TrajectoryCurve)
    {
        //create update callback delegate
        FOnTimelineFloat onUpdate;
        onUpdate.BindUFunction(this, "OnUpdateTrajectory");
        //create delegate called when timeline finishes
        FOnTimelineEventStatic onFinished;
        onFinished.BindUFunction(this, "OnFinishTrajectory");
        //set delegates to timeline
        TrajectoryTimeline.AddInterpFloat(TrajectoryCurve, onUpdate);
        TrajectoryTimeline.SetTimelineFinishedFunc(onFinished);
        TrajectoryTimeline.SetTimelineLength(LifeSpan);
        TrajectoryTimeline.SetLooping(false);
    }
     
}

// Called every frame
void AAegisProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
    //sets the tik rate 
    TrajectoryTimeline.TickTimeline(DeltaTime);
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
    //Destroy();
    
    if(bReflected) {
        return;
    }
    FAegisGameplayEffectApplicationInfo appInfo;
    ApplyGameplayEffects(this, OtherActor, appInfo);
}

// Begin IAegisReflectInterface
void AAegisProjectile::OnReflect()
{
    bReflected = true;
    
}
//End IAegisReflectInterface

void AAegisProjectile::ConstructTrajectory()
{
    if(TrajectorySplineComponent)
    {
        TrajectorySplineComponent->ClearSplinePoints();
        //add start point
        //add end point
        
    }
}

void AAegisProjectile::OnUpdateTrajectory(float Value)
{
if(TrajectorySplineComponent)
{
    float distanceAlongSpline = TrajectorySplineComponent->GetSplineLength() * Value;
    FVector newLoc = TrajectorySplineComponent->GetLocationAtDistanceAlongSpline(distanceAlongSpline, ESplineCoordinateSpace::World);
    SetActorLocation(newLoc);
    FRotator newRot = TrajectorySplineComponent->GetRotationAtDistanceAlongSpline(distanceAlongSpline, ESplineCoordinateSpace::World);
    SetActorRotation(newRot);
    
}
}

void AAegisProjectile::OnFinishTrajectory()
{
    //Destroy Projectile
}

