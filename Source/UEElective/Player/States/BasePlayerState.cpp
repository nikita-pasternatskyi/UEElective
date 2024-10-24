// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePlayerState.h"

#include "StateMachineComponent.h"
#include "UEElective/UEElectiveCharacter.h"

void UBasePlayerState::OnPlayerStateInit_Implementation(UStateMachineComponent* stateMachine,
                                                        AUEElectiveCharacter* character)
{
}

UBasePlayerState::UBasePlayerState()
{
}

void UBasePlayerState::OnStateInit_Implementation(UStateMachineComponent* stateMachine)
{
	Super::OnStateInit_Implementation(stateMachine);
	m_OwningCharacter = Cast<AUEElectiveCharacter>(stateMachine->GetOwner());
	OnPlayerStateInit(stateMachine, m_OwningCharacter);
	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, "Player State init");
}
