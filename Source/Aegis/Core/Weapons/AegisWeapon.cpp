// Fill out your copyright notice in the Description page of Project Settings.

#include "Aegis.h"
#include "Core/Weapons/AegisWeapon.h"
#include "Core/Characters/AegisPlayerCharacter.h"
#include "Core/Characters/AegisEnemyCharacter.h"

// Sets default values
AAegisWeapon::AAegisWeapon()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	
	
	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>("Mesh"); 
	if (Mesh)
	{
		RootComponent = Mesh; 
		Mesh->bGenerateOverlapEvents = true;
	}
}

// Called when the game starts or when spawned:AegisPlayerCharacter.cpp
void AAegisWeapon::BeginPlay()
{
	Super::BeginPlay();
	if (Mesh)
	{
		Mesh->OnComponentBeginOverlap.AddDynamic(this, &AAegisWeapon::OnWeaponBeginOverlap);
	}
	
}

// Called every frame
void AAegisWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AAegisWeapon::OnWeaponBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
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
    
}

FAegisGameplayEffectApplicationOrder AAegisWeapon::GetCurrentApplicationOrder() const
{
    AActor* owner = GetOwner();
    auto interface = Cast<IAegisProcessGameplayEffectInterface>(owner);
    if(interface)
    {
        return interface->GetCurrentApplicationOrder(); 
    }
    return FAegisGameplayEffectApplicationOrder();
}










