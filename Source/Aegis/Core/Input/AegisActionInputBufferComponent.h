// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Core/Input/AegisActionInput.h"
#include "Core/Input/Actions/AegisCharacterActions.h"
#include "AegisActionInputBufferComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class AEGIS_API UAegisActionInputBufferComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UAegisActionInputBufferComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	/**
     * Calls Decay() every frame
     * @see Decay()
     */
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
    virtual void OnRegister() override; 

    void AddActionPressed(FName ActionType);
    void AddActionReleased(FName ActionType);
    FAegisCharacterActionInput Get();
    
protected:
    /**
     * Given an FName for an ActionType, returns the corresponding FAegisCharacterActionBase from the ActionNameToActionMap
     * Returns FAegisCharacterActionBase() if ActionType cannot be found
     */
    virtual FAegisCharacterActionBase GetAction(FName ActionName);
    
    /**
     * Initialises the ActionNameToActionMap with the correct values of Keys and values.
     * Must be overridden if custom FAegisCharacterActions are to be used as values
     */
    virtual void InitActionNameToActionMap();

    /**
     * Maps the FName of an action its correspoinding FAegisCharacterActionBase
     * @see NAegisCharacterAction
     * @see FAegisCharacterActionBase
     */
    TMap<FName, FAegisCharacterActionBase> ActionNameToActionMap;
private:
    void IncrementReadIndex();
    void AddAction(FName ActionType, bool Pressed);

    
    void IncrementWriteIndex();
    /** Resets Read and Write Indices to 0 to prevent the write index from lapping the read index*/
    void ResetReadWriteIndices();
    bool IsIndexValid(uint32 InIndex) const;
    /** Increments the Read Index at set intervals to expend inputs*/
    void Decay();
    class AAegisCharacter* GetAegisOwner() const;
    
    /** A circular buffer of FAegisCharacterActionINputs*/
    UPROPERTY()
    TArray<FAegisCharacterActionInput> InputBuffer;
    
    uint32 ReadIndex = 0;
    uint32 WriteIndex = 0;
    
    /** Rate in seconds the input at the read index is expended*/
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Input Buffer Parameters", meta = (AllowPrivateAccess = "true"))
    float ExpendInputRate = 0.4f;

    
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category= "Input Buffer Parameters", meta = (AllowPrivateAccess = "true"))
    int32 BufferSize = 60;
};



