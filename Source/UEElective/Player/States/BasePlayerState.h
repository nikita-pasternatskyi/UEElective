﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "State.h"
#include "UObject/Object.h"
#include "BasePlayerState.generated.h"

class AUEElectiveCharacter;
class UPlayerInputStamp;

UCLASS()
class UEELECTIVE_API UBasePlayerState : public UState
{
	GENERATED_BODY()

public:
	UBasePlayerState();
	
protected:
	virtual void OnStateInit_Implementation(UStateMachineComponent* stateMachine) override;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void OnPlayerStateInit(UStateMachineComponent* stateMachine, AUEElectiveCharacter* character);
	
private:
	UPROPERTY(BlueprintReadOnly, VisibleInstanceOnly, meta = (AllowPrivateAccess = true))
	UPlayerInputStamp* m_PlayerInput;

	UPROPERTY(BlueprintReadOnly, VisibleInstanceOnly, meta = (AllowPrivateAccess = true))
	AUEElectiveCharacter* m_OwningCharacter;
};
