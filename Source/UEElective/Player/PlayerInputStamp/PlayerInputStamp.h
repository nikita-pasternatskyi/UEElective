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

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category="Input")
	FPlayerInputActionState MoveValue;
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category="Input")
	FPlayerInputActionState LookValue;
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category="Input")
	FPlayerInputActionState JumpValue;
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category="Input")
	FPlayerInputActionState SlideValue;
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category="Input")
	FPlayerInputActionState SprintValue;
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category="Input")
	FPlayerInputActionState MainAttackValue;
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category="Input")
	FPlayerInputActionState AltAttackValue;
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category="Input")
	FPlayerInputActionState UseItemValue;
	
private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* m_JumpAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* m_MoveAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* m_LookAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* m_SlideAction;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* m_Sprint;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* m_MainAttack;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* m_AltAttack;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* m_UseItem;


private:
	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void StartJump(const FInputActionValue& Value);
	void StopJump(const FInputActionValue& Value);
	void Jumping(const FInputActionValue& Value);

	
	void StartSprint(const FInputActionValue& Value);
	void StopSprint(const FInputActionValue& Value);
	void Sprint(const FInputActionValue& Value);

	void StartSlide(const FInputActionValue& Value);
	void StopSlide(const FInputActionValue& Value);
	void Slide(const FInputActionValue& Value);
	
	void StartMainAttack(const FInputActionValue& Value);
	void StopMainAttack(const FInputActionValue& Value);
	void MainAttack(const FInputActionValue& Value);

	void StartAltAttack(const FInputActionValue& Value);
	void StopAltAttack(const FInputActionValue& Value);
	void AltAttack(const FInputActionValue& Value);

	void StartUseItem(const FInputActionValue& Value);
	void StopUseItem(const FInputActionValue& Value);
	void UseItem(const FInputActionValue& Value);
};
