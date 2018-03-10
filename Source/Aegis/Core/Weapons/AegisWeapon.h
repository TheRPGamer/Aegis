// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Core/GameplayEffects/AegisGameplayEffectApplicationOrder.h"
//Interfaces
#include "Core/Interfaces/AegisProcessGameplayEffectInterface.h"
#include "GameplayTagAssetInterface.h"
#include "AegisWeapon.generated.h"

class AAegisCharacter; 
UCLASS()
class AEGIS_API AAegisWeapon : public AActor, public IAegisProcessGameplayEffectInterface, public IGameplayTagAssetInterface
{
	GENERATED_BODY()

public:
    AAegisWeapon();
protected:
	/** Called when the game starts or when spawned */
	virtual void BeginPlay() override;

public:	
	/** Called every frame */
	virtual void Tick(float DeltaTime) override;
	
    FORCEINLINE bool IsCollisionActive() const { return bCollisionActive; }
    void SetCollisionActive(bool bInCollisionActive) { bCollisionActive = bInCollisionActive; }
    
    //IAegisProcessGameplayEffectInterface Begin
    virtual FAegisGameplayEffectApplicationOrder GetCurrentApplicationOrder() const override;
    //IAegisProcessGameplayEffectInterface End
	
    // Begin IGameplayTagAssetInterface
    virtual void GetOwnedGameplayTags(FGameplayTagContainer& TagContainer) const override { TagContainer = CharacterTagsContainer; return; }
    // End IGameplayTagAssetInterface

protected:
	/** Function called when the weapon overlaps with a target*/
	UFUNCTION(BlueprintCallable)
    virtual void OnWeaponBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	/** True if the weapon is currently active and and will damage targets it overlaps with*/
	bool bCollisionActive = false;
	
	/** The weapon's Mesh. To be assigned in BP*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh")
	UMeshComponent* Mesh = nullptr; 

    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
    FGameplayTagContainer CharacterTagsContainer;
	
};
