// Fill out your copyright notice in the Description page of Project Settings.

#include "Aegis.h"
#include "AegisActionInputBufferComponent.h"
#include "Core/AegisCharacter.h"


// Sets default values for this component's properties
UAegisActionInputBufferComponent::UAegisActionInputBufferComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UAegisActionInputBufferComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UAegisActionInputBufferComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
    //Increments the Read Index according to the Decay Rate
    Decay();
}

void UAegisActionInputBufferComponent::OnRegister()
{
    Super::OnRegister(); 
    InputBuffer.Init(FAegisCharacterActionInput(), BufferSize);
}

FAegisCharacterActionBase UAegisActionInputBufferComponent::GetAction(FName ActionName)
{
    //find returns a valid ptr if the value exists, else nullptr
    auto action = ActionNameToActionMap.Find(ActionName);
    if(action)
    {
        return *action;
    }
    //return a default character action if the key is invalid
    return ActionNameToActionMap[NAegisCharacterAction::None];
}

void UAegisActionInputBufferComponent::InitActionNameToActionMap()
{
    ActionNameToActionMap.Emplace(NAegisCharacterAction::None, FAegisCharacterActionBase() );
    ActionNameToActionMap.Emplace(NAegisCharacterAction::Melee, FAegisCharacterMeleeAction() );
    
}
void UAegisActionInputBufferComponent::AddActionPressed(FName ActionType)
{
    AddAction(ActionType, true);
}
void UAegisActionInputBufferComponent::AddActionReleased(FName ActionType)
{
    AddAction(ActionType, false);
}

void UAegisActionInputBufferComponent::AddAction(FName ActionType, bool Pressed)
{
    if(IsIndexValid(WriteIndex))
    {
        auto action = GetAction(ActionType);
        InputBuffer[WriteIndex].Update(action, Pressed);
        IncrementWriteIndex();
    }
}

FAegisCharacterActionInput UAegisActionInputBufferComponent::Get() 
{
    FAegisCharacterActionInput input;
    if(IsIndexValid(ReadIndex))
    {
        input = InputBuffer[ReadIndex];
        ResetReadWriteIndices();
        
    }
    return input;
}

void UAegisActionInputBufferComponent::IncrementReadIndex()
{
    //only advance read index if read index is behind write index
    if(ReadIndex != WriteIndex)
    {
        ++ReadIndex;
       //loops around like a circular buffer
        ReadIndex %= BufferSize;
    }
}

void UAegisActionInputBufferComponent::IncrementWriteIndex()
{
    ++WriteIndex;
    //loops around to act as circular buffer
    WriteIndex %= BufferSize;
}

void UAegisActionInputBufferComponent::ResetReadWriteIndices()
{
    ReadIndex = 0;
    WriteIndex = 0;
    //Clears the Action Input on Read Index in case inputs are read to prevent extra actions
    if(InputBuffer.Num() > 0)
    {
        InputBuffer[ReadIndex].Clear(); 
    }
}

bool UAegisActionInputBufferComponent::IsIndexValid(uint32 InIndex) const
{
    if(InIndex < InputBuffer.Num())
    {
        return true;
    }
    return false;
}

void UAegisActionInputBufferComponent::Decay()
{
    
    ++DecayCounter;
    if(DecayCounter >= DecayRate)
    {
        //expends the current Character Action on ReadIndex
        IncrementReadIndex();
        DecayCounter = 0;
    }
}

AAegisCharacter* UAegisActionInputBufferComponent::GetAegisOwner() const
{
    return Cast<AAegisCharacter>(GetOwner());
}

