// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerInputStamp.h"
#include "EnhancedInputComponent.h"

UPlayerInputStamp::UPlayerInputStamp()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UPlayerInputStamp::BindActions(UEnhancedInputComponent* EnhancedInputComponent)
{
	EnhancedInputComponent->BindAction(m_JumpAction, ETriggerEvent::Started, this, &UPlayerInputStamp::StartJump);
	EnhancedInputComponent->BindAction(m_JumpAction, ETriggerEvent::Ongoing, this, &UPlayerInputStamp::Jumping);
	EnhancedInputComponent->BindAction(m_JumpAction, ETriggerEvent::Completed, this, &UPlayerInputStamp::StopJump);

	EnhancedInputComponent->BindAction(m_MoveAction, ETriggerEvent::Triggered, this, &UPlayerInputStamp::Move);

	EnhancedInputComponent->BindAction(m_LookAction, ETriggerEvent::Triggered, this, &UPlayerInputStamp::Look);
}

void UPlayerInputStamp::Move(const FInputActionValue& Value)
{
	bool pressed = false;
	if(Value.IsNonZero())
		pressed = true;
	MoveValue = {Value, pressed, true, true};
}

void UPlayerInputStamp::Look(const FInputActionValue& Value)
{
	bool pressed = false;
	if(Value.IsNonZero())
		pressed = true;
	LookValue = {Value, pressed, true, false};
}

void UPlayerInputStamp::StartJump(const FInputActionValue& Value)
{
	StartJumpValue = {Value, true, true, false};
}

void UPlayerInputStamp::StopJump(const FInputActionValue& Value)
{
	StartJumpValue = {Value, false, false, true};
}

void UPlayerInputStamp::Jumping(const FInputActionValue& Value)
{
	StartJumpValue = {Value, true, false, false};
}
