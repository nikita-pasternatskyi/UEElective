// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "GameFramework/Character.h"
#include "PlayerCharacter.generated.h"

struct FInputActionValue;
class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UCameraTransitionerComponent;
class UInputAction;
class UPrimitiveComponent;

UENUM(BlueprintType)
enum EPlayerState
{
	Normal,
	InAir,
	Sliding,
	Crouching,
	EdgeHanging,
};

UCLASS(config=Game)
class UEELECTIVE_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	APlayerCharacter();

	FORCEINLINE EPlayerState GetCurrentState() const {return CurrentState;}
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return m_CameraBoom; }
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return m_FollowCamera; }

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Properties)
	float WalkSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Properties)
	float SprintSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Properties)
	float MinMoveSpeedForSlide;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Properties)
	float WallCheckLength;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Properties)
	float WallJumpPushForwardForce;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Properties)
	float WallJumpPushAwayForce;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Properties)
	float WallJumpWeakPushAwayForce;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Properties)
	float WallJumpUpForce;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Properties)
	float WallJumpClimbUpForce;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Properties)
	float EdgeGrabForwardForce;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Properties)
	float EdgeGrabJumpForce;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Properties)
	float EdgeGrabCooldownTime;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Properties)
	TEnumAsByte<EPlayerState> CurrentState;

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* m_JumpAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* m_MoveAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* m_LookAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* m_CrouchAction;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* m_SprintAction;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* m_CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* m_FollowCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraTransitionerComponent* m_CameraTransitioner;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* m_DefaultMappingContext;

	FVector m_RelativeMovementInput;
	FHitResult RayCast(const FVector& direction, const FCollisionQueryParams& traceParams, const float length) const; 

	float m_lastEdgeGrabTime;

	bool m_climbedUp;
	float m_lastClimbedUpTime;
	
private:
	UFUNCTION(BlueprintCallable)
	void Move(const FInputActionValue& value);
	UFUNCTION(BlueprintCallable)
	void Look(const FInputActionValue& value);

	void StartJump(const FInputActionValue& value);
	void StopJump(const FInputActionValue& value);

	void StartSprint(const FInputActionValue& value);
	void StopSprint(const FInputActionValue& value);

	void StartCrouch(const FInputActionValue& value);
	void StopCrouch(const FInputActionValue& value);
};
