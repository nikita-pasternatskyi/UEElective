#pragma once

#include "InputActionValue.h"
#include "PlayerInputActionState.generated.h"

USTRUCT(BlueprintType)
struct FPlayerInputActionState
{
	GENERATED_BODY()

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly)
	FInputActionValue InputValue;
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly)
	bool Pressed;
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly)
	bool JustPressed;
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly)
	bool JustReleased;
};
