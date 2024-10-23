// Fill out your copyright notice in the Description page of Project Settings.

#include "StateMachineComponent.h"

UStateMachineComponent::UStateMachineComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

// Called when the game starts
void UStateMachineComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UStateMachineComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                           FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

