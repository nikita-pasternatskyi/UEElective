// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"
#include "UEElectiveCharacter.generated.h"

struct FInputActionValue;
class UPlayerInputStamp;
class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UStateMachineComponent;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

UCLASS(config=Game)
class AUEElectiveCharacter : public ACharacter
{
	GENERATED_BODY()
	
private:
	//Components
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = StateMachine, meta = (AllowPrivateAccess = "true"))
	UStateMachineComponent* StateMachine;

	//Input
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = StateMachine, meta = (AllowPrivateAccess = "true"))
	UPlayerInputStamp* m_PlayerInputStamp;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;

public:
	AUEElectiveCharacter();

	FORCEINLINE class UPlayerInputStamp* GetPlayerInput() const {return m_PlayerInputStamp;}
	
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
	
protected:
	virtual void BeginPlay();
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
private:
	UFUNCTION(BlueprintCallable)
	void Move(const FVector2D& value);
	UFUNCTION(BlueprintCallable)
	void Look(const FVector2D& value);
};

