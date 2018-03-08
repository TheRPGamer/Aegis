// Fill out your copyright notice in the Description page of Project Settings.

#include "Aegis.h"
#include "AegisActionInputBufferComponent.h"
#include "Core/Characters/AegisCharacter.h"


// Sets default values for this component's properties
UAegisActionInputBufferComponent::UAegisActionInputBufferComponent()
: InputBuffer(1024)
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

UAegisActionInputBufferComponent::UAegisActionInputBufferComponent(FVTableHelper& Helper)
: Super(Helper)
, InputBuffer(1024)
{
    PrimaryComponentTick.bCanEverTick = true;
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
    //expends extra mashed inputs
    ExpendInput();
}

void UAegisActionInputBufferComponent::OnRegister()
{
    Super::OnRegister();
    InitActionNameToActionMap();
    PrimaryComponentTick.TickInterval = ExpendInputRate;
}

UAegisCharacterActionBase* UAegisActionInputBufferComponent::GetAction(FName ActionName)
{
    //find returns a valid ptr if the value exists, else nullptr
    //UE_LOG(AegisInputLog, Log, TEXT("Action Name: %s"), *(ActionName.ToString()));
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
    // every character action needs to be appended to this map
    //@see AegisCharacterActions.h/.cpp
    ActionNameToActionMap.Add(NAegisCharacterAction::None, NewObject<UAegisCharacterActionBase>() );
    ActionNameToActionMap.Add(NAegisCharacterAction::Melee, NewObject<UAegisCharacterMeleeAction>() );
    ActionNameToActionMap.Add(NAegisCharacterAction::Guard, NewObject<UAegisCharacterGuardAction>() );
    ActionNameToActionMap.Add(NAegisCharacterAction::Super, NewObject<UAegisCharacterSuperAction>() );

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

void UAegisActionInputBufferComponent::Execute()
{
    if(IsIndexValid(ReadIndex))
    {
        AAegisCharacter* owner = GetAegisOwner();
        auto input = InputBuffer[ReadIndex];
        input.Execute(owner);
        ResetReadWriteIndices();
    }
}

void UAegisActionInputBufferComponent::ExpendInput()
{
    IncrementReadIndex();
}

void UAegisActionInputBufferComponent::IncrementReadIndex()
{
    //only advance read index if read index is behind write index
    if(ReadIndex == WriteIndex)
    {
        return;
    }
    ReadIndex = InputBuffer.GetNextIndex(ReadIndex);
    
}

void UAegisActionInputBufferComponent::IncrementWriteIndex()
{
    WriteIndex = InputBuffer.GetNextIndex(WriteIndex);
    
    
}

void UAegisActionInputBufferComponent::ResetReadWriteIndices()
{
    ReadIndex = 0;
    WriteIndex = 0;
    //clear input at read index just in case
    InputBuffer[ReadIndex].Clear();
}

bool UAegisActionInputBufferComponent::IsIndexValid(uint32 InIndex) const
{
    return InIndex < InputBuffer.Capacity();
}


AAegisCharacter* UAegisActionInputBufferComponent::GetAegisOwner() const
{
    return Cast<AAegisCharacter>(GetOwner());
}

