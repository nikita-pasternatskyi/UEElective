// Fill out your copyright notice in the Description page of Project Settings.

#include "StateMachineComponent.h"
#include "State.h"

UStateMachineComponent::UStateMachineComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

// Called when the game starts
void UStateMachineComponent::BeginPlay()
{
	Super::BeginPlay();
	if(m_InitialState)
		ChangeState(m_InitialState);
}

void UStateMachineComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                           FActorComponentTickFunction* ThisTickFunction)
{
	if(m_CurrentState)
	{
		m_CurrentState->TickState(DeltaTime);
	}
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UStateMachineComponent::ChangeState(TSubclassOf<UState> NewState)
{
	if(NewState == nullptr)
		return;
	if(m_CurrentState != nullptr)
	{
		if(m_CurrentState->StaticClass() == NewState)
			return;
		m_CurrentState->ExitState();
	}

	if(m_bDebug)
	{
		GEngine->AddOnScreenDebugMessage(-1, 1.0, FColor::Red, "Entering State: " + NewState->GetName());
	}
	
	UState* newStateInstance = nullptr;
	if(m_StatesMap.Contains(NewState))
	{
		newStateInstance = m_StatesMap[NewState];
	}
	else
	{
		UClass* typeClass = NewState;
		newStateInstance = NewObject<UState>(this, typeClass);
		newStateInstance->InitState(this);
		AddReplicatedSubObject(newStateInstance);
		m_StatesMap.Add(NewState, newStateInstance);
	}
	
	m_CurrentState = newStateInstance;
	m_CurrentState->EnterState();
}

