// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CameraSettingsState.h"
#include "Components/ActorComponent.h"
#include "CameraTransitionerComponent.generated.h"

class UCameraComponent;
class USpringArmComponent;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class CAMERATRANSITIONS_API UCameraTransitionerComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UCameraTransitionerComponent();
protected:
	virtual void BeginPlay() override;
	
private:
	FCameraSettingsState m_CurrentSettings;

	void Lerp(float t);
	
public:
	USpringArmComponent* m_SpringArmComponent;
	UCameraComponent* m_CameraComponent;
	UPROPERTY(EditAnywhere)
	bool CreateStateOnBeginPlay;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	void ChangeCameraSettingsState(const FCameraSettingsState& NewCameraSettingsState);
	
	UFUNCTION(BlueprintCallable)
	void ImmediateChangeCameraSettingsState(const FCameraSettingsState& NewCameraSettingsState);
};
