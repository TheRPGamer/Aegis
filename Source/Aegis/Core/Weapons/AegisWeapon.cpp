// Fill out your copyright notice in the Description page of Project Settings.

#include "Aegis.h"
#include "Core/Weapons/AegisWeapon.h"
#include "Core/Characters/AegisPlayerCharacter.h"
#include "Core/Characters/AegisEnemyCharacter.h"

// Sets default values
AAegisWeapon::AAegisWeapon()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	
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
	if (!bCanDamageTargets || (OtherActor == this) || (OtherActor == GetOwner()) )
	{
		return; 
	}

	auto overlappedTarget = Cast<AAegisCharacter>(OtherActor); 
	auto owner = Cast<AAegisCharacter>(GetOwner());
	if (overlappedTarget && owner)
	{
		overlappedTarget->TakeDamage(MeleeAttackDamage, FDamageEvent(), owner->GetController(), owner); 
	}

}
