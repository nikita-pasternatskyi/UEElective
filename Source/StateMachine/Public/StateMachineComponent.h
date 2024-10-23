// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "StateMachineComponent.generated.h"


UCLASS(BLueprintable)
class STATEMACHINE_API UStateMachineComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UStateMachineComponent();

protected:
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
private:
	UPROPERTY(EditAnywhere)
	class UState* PureStatePtr;

	UPROPERTY(EditAnywhere)
	TObjectPtr<class UState> StateTObjectPtr;

	UPROPERTY(EditAnywhere)
	TSoftClassPtr<class UState> SoftStateClassPtr;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UState> TSubclassStateClass;
};
