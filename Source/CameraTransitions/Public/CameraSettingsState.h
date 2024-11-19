#pragma once

#include "CameraSettingsState.generated.h"

USTRUCT(BlueprintType)
struct FCameraSettingsState
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float ArmLength;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float FOV;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FVector SocketOffset;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float TransitionSpeed;

	FORCEINLINE bool operator==(const FCameraSettingsState& MyDataReference) const
	{
		return	ArmLength == MyDataReference.ArmLength && FOV == MyDataReference.FOV
				&& SocketOffset == MyDataReference.SocketOffset && TransitionSpeed == MyDataReference.TransitionSpeed;
	}

};
