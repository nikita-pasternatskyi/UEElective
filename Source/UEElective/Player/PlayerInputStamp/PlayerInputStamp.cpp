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

	EnhancedInputComponent->BindAction(m_SlideAction, ETriggerEvent::Started, this, &UPlayerInputStamp::StartSlide);
	EnhancedInputComponent->BindAction(m_SlideAction, ETriggerEvent::Ongoing, this, &UPlayerInputStamp::Slide);
	EnhancedInputComponent->BindAction(m_SlideAction, ETriggerEvent::Completed, this, &UPlayerInputStamp::StopSlide);

	EnhancedInputComponent->BindAction(m_MainAttack, ETriggerEvent::Started, this, &UPlayerInputStamp::StartMainAttack);
	EnhancedInputComponent->BindAction(m_MainAttack, ETriggerEvent::Ongoing, this, &UPlayerInputStamp::MainAttack);
	EnhancedInputComponent->BindAction(m_MainAttack, ETriggerEvent::Completed, this, &UPlayerInputStamp::StopMainAttack);

	EnhancedInputComponent->BindAction(m_AltAttack, ETriggerEvent::Started, this, &UPlayerInputStamp::StartAltAttack);
	EnhancedInputComponent->BindAction(m_AltAttack, ETriggerEvent::Ongoing, this, &UPlayerInputStamp::AltAttack);
	EnhancedInputComponent->BindAction(m_AltAttack, ETriggerEvent::Completed, this, &UPlayerInputStamp::StopAltAttack);

	EnhancedInputComponent->BindAction(m_UseItem, ETriggerEvent::Started, this, &UPlayerInputStamp::StartUseItem);
	EnhancedInputComponent->BindAction(m_UseItem, ETriggerEvent::Ongoing, this, &UPlayerInputStamp::UseItem);
	EnhancedInputComponent->BindAction(m_UseItem, ETriggerEvent::Completed, this, &UPlayerInputStamp::StopUseItem);
	
	EnhancedInputComponent->BindAction(m_Sprint, ETriggerEvent::Started, this, &UPlayerInputStamp::StartSprint);
	EnhancedInputComponent->BindAction(m_Sprint, ETriggerEvent::Ongoing, this, &UPlayerInputStamp::Sprint);
	EnhancedInputComponent->BindAction(m_Sprint, ETriggerEvent::Completed, this, &UPlayerInputStamp::StopSprint);

	
	EnhancedInputComponent->BindAction(m_MoveAction, ETriggerEvent::Triggered, this, &UPlayerInputStamp::Move);
	EnhancedInputComponent->BindAction(m_MoveAction, ETriggerEvent::Completed, this, &UPlayerInputStamp::Move);

	EnhancedInputComponent->BindAction(m_LookAction, ETriggerEvent::Triggered, this, &UPlayerInputStamp::Look);
	EnhancedInputComponent->BindAction(m_LookAction, ETriggerEvent::Completed, this, &UPlayerInputStamp::Look);
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
	JumpValue = {Value, true, true, false};
}

void UPlayerInputStamp::StopJump(const FInputActionValue& Value)
{
	JumpValue = {Value, false, false, true};
}

void UPlayerInputStamp::Jumping(const FInputActionValue& Value)
{
	JumpValue = {Value, true, false, false};
}

void UPlayerInputStamp::StartSprint(const FInputActionValue& Value)
{
	SprintValue = {Value, true, true, false};
}

void UPlayerInputStamp::StopSprint(const FInputActionValue& Value)
{
	SprintValue = {Value, false, false, true};
}

void UPlayerInputStamp::Sprint(const FInputActionValue& Value)
{
	SprintValue =  {Value, true, false, false};
}

void UPlayerInputStamp::StartSlide(const FInputActionValue& Value)
{
	SlideValue = {Value, true, true, false};
}

void UPlayerInputStamp::StopSlide(const FInputActionValue& Value)
{
	SlideValue = {Value, false, false, true};
}

void UPlayerInputStamp::Slide(const FInputActionValue& Value)
{
	SlideValue = {Value, true, false, false};
}

void UPlayerInputStamp::StartMainAttack(const FInputActionValue& Value)
{
	MainAttackValue = {Value, true, true, false};
}

void UPlayerInputStamp::StopMainAttack(const FInputActionValue& Value)
{
	MainAttackValue = {Value, false, false, true};
}

void UPlayerInputStamp::MainAttack(const FInputActionValue& Value)
{
	MainAttackValue = {Value, true, false, false};
}

void UPlayerInputStamp::StartAltAttack(const FInputActionValue& Value)
{
	AltAttackValue = {Value, true, true, false};
}

void UPlayerInputStamp::StopAltAttack(const FInputActionValue& Value)
{
	AltAttackValue = {Value, false, false, true};
}

void UPlayerInputStamp::AltAttack(const FInputActionValue& Value)
{
	AltAttackValue = {Value, true, false, false};
}

void UPlayerInputStamp::StartUseItem(const FInputActionValue& Value)
{
	UseItemValue = {Value, true, true, false};
}

void UPlayerInputStamp::StopUseItem(const FInputActionValue& Value)
{
	UseItemValue = {Value, false, false, true};
}

void UPlayerInputStamp::UseItem(const FInputActionValue& Value)
{
	UseItemValue = {Value, true, false, false};
}
