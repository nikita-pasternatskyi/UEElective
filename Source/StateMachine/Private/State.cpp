// Fill out your copyright notice in the Description page of Project Settings.

#include "State.h"

UState::UState()
{
}

void UState::InitState(class UStateMachineComponent* stateMachine)
{
	m_StateMachine = stateMachine;
	OnStateInit(stateMachine);
}

void UState::EnterState_Implementation()
{
}

void UState::ExitState_Implementation()
{
}

void UState::TickState_Implementation(float deltaTime)
{
}

void UState::OnStateInit_Implementation(UStateMachineComponent* stateMachine)
{
}
