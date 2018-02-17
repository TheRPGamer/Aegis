// Fill out your copyright notice in the Description page of Project Settings.

#include "Aegis.h"
#include "Core/GameplayEffects/AegisGameplayEffectApplicationInfo.h"
#include "Core/Input/AegisActionInputBufferComponent.h"
#include "Core/Weapons/AegisWeapon.h"
#include "Core/Characters/AegisCharacter.h"

//Start Debug Includes
#include "Core/GameplayEffects/AegisGameplayEffectApplicationOrder.h"
#include "Core/GameplayEffects/AegisGameplayEffectTargets.h"
#include "Core/GameplayEffects/AegisGameplayEffectChain.h"
#include "Core/GameplayEffects/Effects/AegisPhysicalImpactGameplayEffect.h"
#include "Core/GameplayEffects/Effects/AegisKnockbackGameplayEffect.h"
#include "Core/GameplayEffects/Effects/AegisDamageGameplayEffect.h"

#include "Core/Combat/Guard/AegisCharacterGuardLevel.h"
//End Debug Includes

// Sets default values
AAegisCharacter::AAegisCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	if (GetCapsuleComponent())
	{
		GetCapsuleComponent()->bGenerateOverlapEvents = true;
	}
    InputBufferComponent = CreateDefaultSubobject<UAegisActionInputBufferComponent>("Input Buffer ");
    if(GetCapsuleComponent())
    {
        GetCapsuleComponent()->bGenerateOverlapEvents = true;

    }
}

void AAegisCharacter::PostInitProperties()
{
    Super::PostInitProperties();
    //Creates components from TSubclassOf Properties set in Editor
    CreatePostInitComponents();

}

// Called when the game starts or when spawned
void AAegisCharacter::BeginPlay()
{
	Super::BeginPlay();
	ValidateSockets();
    ValidateCharacterComponents();
    if(GetCapsuleComponent())
    {
        GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &AAegisCharacter::OnAegisCharacterBeginOverlap);
    }
    
    
    

}

float AAegisCharacter::TakeDamage(float DamageAmount, const struct FDamageEvent& DamageEvent,
	AController* EventInstigagor, AActor* DamageCauser)
{
	Super::TakeDamage(DamageAmount, DamageEvent, EventInstigagor, DamageCauser);
	UE_LOG(AegisLog, Log, TEXT("Character took damage")); 
	return DamageAmount; 
}


bool AAegisCharacter::CanMove() const
{
	if (ComboComponent)
	{
		return !ComboComponent->IsInCombo(); 
	}
	return false; 
}

bool AAegisCharacter::IsInAir() const
{
	if (GetCharacterMovement())
	{
		return GetCharacterMovement()->IsFalling();

	}
	return false;
}

#if !UE_BUILD_SHIPPING
void AAegisCharacter::ValidateSockets()
{
	if (!HasAnyFlags(RF_ClassDefaultObject) && GetMesh())
	{
		if (!GetMesh()->GetSocketByName(LeftHandSocket))
		{
			UE_LOG(AegisLog, Warning, TEXT("Missing Left Hand Socket for %s. Please specify one in the skeletal mesh and set it's name in the character's properties."), *GetHumanReadableName());
		}

		if (!GetMesh()->GetSocketByName(RightHandSocket))
		{
			UE_LOG(AegisLog, Warning, TEXT("Missing Right Hand Socket for %s. Please specify one in the skeletal mesh and set it's name in the character's properties."), *GetHumanReadableName());
		}
	}
	else if (!HasAnyFlags(RF_ClassDefaultObject))
	{
		UE_LOG(AegisLog, Error, TEXT("Unexpected, missing mesh for %s."), *GetHumanReadableName());
	}
}
#endif

void AAegisCharacter::CreatePostInitComponents()
{
    if (ComboComponentClass)
    {
        ComboComponent = NewObject<UAegisCharacterComboComponent>(this, *ComboComponentClass);
    }
    else
    {
        UE_LOG(AegisComboLog, Error, TEXT("ERROR: AAegisCharacter has invalid ComboComponentClass. Fix in editor "));
    }
    if(GuardComponentClass)
    {
        GuardComponent = NewObject<UAegisCharacterGuardComponent>(this, *GuardComponentClass);
        //CreateDebugGuardComponent();
        
        
    }
    else
    {
        UE_LOG(AegisGuardLog, Error, TEXT("AAegisCharacter has an invalid GuardComponentClass. Fix in Editor"));
    }
}

// Begin IProcessGameplayEffectInterface
FAegisGameplayEffectApplicationOrder AAegisCharacter::GetCurrentApplicationOrder() const
{
    //Debug
    return CreateDebugComboGFXApplicationOrder();
    
    if(ComboComponent)
    {
        return ComboComponent->GetCurrentMove().GetCollisionGFX();
    }
    return FAegisGameplayEffectApplicationOrder();
}
//End IAegisProcessGameplayEffectInterface

//Begin IAegisPhysicalmpactInterface
void AAegisCharacter::OnPhysicalImpact()
{
    UE_LOG(AegisGameplayEffectLog, Log, TEXT("Character::OnPhysicalImpact")); 
}
// End IAegisPhysicalImpactInterface

//Begin IAegisKnockbackInterface
void AAegisCharacter::OnKnockback(FVector KnockbackDirection, float KnockbackMagnitude)
{
    UE_LOG(AegisGameplayEffectLog, Log, TEXT("Character::OnKnockback"));
}
//End IAegisKnockbackInterface

// Begin IAegisDamageInterface
void AAegisCharacter::OnDamage(float DamageAmount)
{
    UE_LOG(AegisGameplayEffectLog, Log, TEXT("Character::OnDamage"));
}
// End IAegisDamageInterface

void AAegisCharacter::ValidateCharacterComponents()
{
    checkf(ComboComponent, TEXT("ComboComponent for is null in AegisCharacter"));
    checkf(GuardComponent, TEXT("Guard Component s null in AegisCharacter"));
}

void AAegisCharacter::OnAegisCharacterBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    // ignore if colliding with self
    if(!OtherActor || (GetUniqueID() == OtherActor->GetUniqueID()))
    {
        return;
    }
    //check other actor is not a child actor of current AAegisCharacter
    //E.g colliding with CurrentEquippedWeapon or somethign of the like 
    AActor* otherOwner = OtherActor->GetOwner();
    if(otherOwner)
    {
        if(GetUniqueID() == otherOwner->GetUniqueID())
        {
            return;
        }
    }
    
    FAegisGameplayEffectApplicationInfo appInfo;
    ApplyGameplayEffects(this, OtherActor, appInfo);
}

// Begin Debug Functionality
FAegisGameplayEffectApplicationOrder AAegisCharacter::CreateDebugComboGFXApplicationOrder() const
{
    
    FAegisGameplayEffectApplicationOrder debugOrder;
    auto impact = NewObject<UAegisPhysicalImpactGameplayEffect>();
    auto damage = NewObject<UAegisDamageGameplayEffect>();
    auto knockback = NewObject<UAegisKnockbackGameplayEffect>();
    debugOrder.GetPreEffects().AddReceiverEffect(impact);
    debugOrder.GetPreEffects().AddInstigatorEffect(knockback);
    debugOrder.GetPreEffects().AddInstigatorEffect(damage);
    return debugOrder;
}

void AAegisCharacter::CreateDebugGuardComponent()
{
    FAegisCharacterGuardLevel level1, level2, level3;
    level3.SetName(FName("One"));
    level3.SetLowerBound(80);
    
    level2.SetName(FName("Two"));
    level2.SetLowerBound(160);
    
    level1.SetName(FName("Three"));
    level1.SetLowerBound(240);
    GuardComponent = NewObject<UAegisCharacterGuardComponent>();

    if(GuardComponent)
    {
        GuardComponent->AddGuardLevel(level1);
        GuardComponent->AddGuardLevel(level2);
        GuardComponent->AddGuardLevel(level3);
        GuardComponent->PrintGuardLevels();
    }
    
    
}

