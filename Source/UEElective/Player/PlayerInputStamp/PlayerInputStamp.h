// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerInputActionState.h"
#include "Components/ActorComponent.h"
#include "PlayerInputStamp.generated.h"

struct FInputActionValue;
class UInputAction;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class UEELECTIVE_API UPlayerInputStamp : public UActorComponent
{
	GENERATED_BODY()

public:
	UPlayerInputStamp();

	void BindActions(UEnhancedInputComponent* PlayerState);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Input")
	FPlayerInputActionState MoveValue;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Input")
	FPlayerInputActionState LookValue;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Input")
	FPlayerInputActionState StartJumpValue;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Input")
	FPlayerInputActionState StopJumpValue;
	
private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* m_JumpAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* m_MoveAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* m_LookAction;

private:
	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void StartJump(const FInputActionValue& Value);
	void StopJump(const FInputActionValue& Value);
	void Jumping(const FInputActionValue& Value);
};
