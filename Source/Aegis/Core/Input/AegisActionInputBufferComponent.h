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
	UAegisActionInputBufferComponent();

protected:
	virtual void BeginPlay() override;

public:	
	/**  IncrementReadIndex() called every Tick*/
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
    /** Updates Editor provided values of ExpendInputRate and BufferSize*/
    virtual void OnRegister() override;

    void AddActionPressed(FName ActionType);
    void AddActionReleased(FName ActionType);
    /** Gets Input at current Read Index*/
    FAegisCharacterActionInput Get();
    
    /** Executes the Action Input at the current Read Index */
    void Execute();
    
protected:
    /**
     * Given an FName for an ActionType, returns the corresponding UAegisCharacterActionBase from the ActionNameToActionMap
     * Returns UAegisCharacterActionBase() if ActionType cannot be found
     */
    virtual UAegisCharacterActionBase* GetAction(FName ActionName);
    
    /**
     * Initialises the ActionNameToActionMap with the correct values of Keys and values.
     * Must be overridden if custom FAegisCharacterActions are to be used as values
     */
    virtual void InitActionNameToActionMap();

    /**
     * Maps the FName of an action its correspoinding UAegisCharacterActionBase
     * @see NAegisCharacterAction
     * @see UAegisCharacterActionBase
     */
    TMap<FName, UAegisCharacterActionBase*> ActionNameToActionMap;
private:
    void IncrementReadIndex();
    void AddAction(FName ActionType, bool Pressed);

    
    void IncrementWriteIndex();
    /** Resets Read and Write Indices to 0 to prevent the write index from lapping the read index*/
    void ResetReadWriteIndices();
    bool IsIndexValid(uint32 InIndex) const;
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



