// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "StateMachineComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class STATEMACHINE_API UStateMachineComponent : public UActorComponent
{
	GENERATED_BODY()
	friend class UState;

public:
	UStateMachineComponent();

protected:
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
private:
	UPROPERTY(EditDefaultsOnly)
	bool m_bDebug;
	
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UState> m_InitialState;

	UPROPERTY(VisibleAnywhere)
	UState* m_CurrentState;

	TMap<TSubclassOf<UState>, UState*> m_StatesMap;

	UFUNCTION(BlueprintCallable)
	void ChangeState(TSubclassOf<UState> NewState);
};
