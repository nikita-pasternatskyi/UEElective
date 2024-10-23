// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "State.generated.h"

UCLASS(Abstract, Blueprintable)
class STATEMACHINE_API UState : public UObject
{
	GENERATED_BODY()
		
public:
	UState();
	void InitState(class UStateMachineComponent* stateMachine);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void EnterState();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void ExitState();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void TickState(float deltaTime);

protected:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void OnStateInit(UStateMachineComponent* stateMachine);

	UPROPERTY(BlueprintReadOnly)
	UStateMachineComponent* m_StateMachine;
	
};
