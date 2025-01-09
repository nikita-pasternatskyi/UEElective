// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"

#include "CameraTransitionerComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"
#include "UEElective/UEElectiveCharacter.h"


APlayerCharacter::APlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);

	JumpMaxHoldTime = 2.f;
	GetCharacterMovement()->JumpZVelocity = 350.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = WalkSpeed = 500.0f;
	SprintSpeed = 800.0f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;

	m_CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	m_CameraBoom->SetupAttachment(RootComponent);
	m_CameraBoom->TargetArmLength = 400.0f;
	m_CameraBoom->bUsePawnControlRotation = true;

	m_FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	m_FollowCamera->SetupAttachment(m_CameraBoom, USpringArmComponent::SocketName);
	m_FollowCamera->bUsePawnControlRotation = false;

	m_CameraTransitioner = CreateDefaultSubobject<UCameraTransitionerComponent>(TEXT("CameraTransitioner"));
	m_CameraTransitioner->m_CameraComponent = m_FollowCamera;
	m_CameraTransitioner->m_SpringArmComponent = m_CameraBoom;

	CurrentState = EPlayerState::Normal;
	WallJumpWeakPushAwayForce = WallJumpPushAwayForce = 250.0f;
	WallJumpUpForce = 800.0f;
	WallJumpPushForwardForce = 450.0f;
	WallCheckLength = 150.0f;
}

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
}

void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	bool grounded = GetCharacterMovement()->IsMovingOnGround();
	
	switch(CurrentState)
	{
		default:
				GEngine->AddOnScreenDebugMessage(-1, DeltaTime, FColor::Red,TEXT("Current Player State is not accounted for"));
		case EPlayerState::Normal:
		case EPlayerState::Crouching:
		case EPlayerState::Sliding:
			if(grounded == false)
			{
				CurrentState = EPlayerState::InAir;
			}
			break;
		case EPlayerState::InAir:
			if(grounded == true)
			{
				CurrentState = EPlayerState::Normal;
			}
			break;
		case EPlayerState::EdgeHanging:
			break;
	}
	
}

void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(m_DefaultMappingContext, 0);
		}
	}
	
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(m_JumpAction, ETriggerEvent::Started, this, &APlayerCharacter::StartJump);
		EnhancedInputComponent->BindAction(m_JumpAction, ETriggerEvent::Completed, this, &APlayerCharacter::StopJump);

		EnhancedInputComponent->BindAction(m_CrouchAction, ETriggerEvent::Started, this, &APlayerCharacter::StartCrouch);
		EnhancedInputComponent->BindAction(m_CrouchAction, ETriggerEvent::Completed, this, &APlayerCharacter::StopCrouch);

		EnhancedInputComponent->BindAction(m_SprintAction, ETriggerEvent::Started, this, &APlayerCharacter::StartSprint);
		EnhancedInputComponent->BindAction(m_SprintAction, ETriggerEvent::Completed, this, &APlayerCharacter::StopSprint);
	
		EnhancedInputComponent->BindAction(m_MoveAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Move);
		EnhancedInputComponent->BindAction(m_MoveAction, ETriggerEvent::Completed, this, &APlayerCharacter::Move);

		EnhancedInputComponent->BindAction(m_LookAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Look);
		EnhancedInputComponent->BindAction(m_LookAction, ETriggerEvent::Completed, this, &APlayerCharacter::Look);
	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

void APlayerCharacter::Move(const FInputActionValue& value)
{
	if(Controller == nullptr)
		return;

	FVector2D input = value.Get<FVector2D>();
	
	// find out which way is forward
	const FRotator Rotation = Controller->GetControlRotation();
	const FRotator YawRotation(0, Rotation.Yaw, 0);

	// get forward vector
	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
			
	// get right vector 
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	m_RelativeMovementInput = ForwardDirection * input.Y + RightDirection * input.X;
	m_RelativeMovementInput.Normalize();

	switch(CurrentState)
	{
		case Normal:
		case InAir:
		case Sliding:
		case Crouching:
				AddMovementInput(ForwardDirection, input.Y);
				AddMovementInput(RightDirection, input.X);
				break;
		case EdgeHanging:
			break;
		default: break;
	}
	
	if(CurrentState == EPlayerState::InAir)
	{
		if(UGameplayStatics::GetRealTimeSeconds(GetWorld()) - m_lastEdgeGrabTime <= EdgeGrabCooldownTime)
			return;
		
		FCollisionQueryParams traceParams = FCollisionQueryParams(FCollisionQueryParams::DefaultQueryParam);
		traceParams.bTraceComplex = false;
		traceParams.AddIgnoredActor(this);
		traceParams.bReturnPhysicalMaterial = false;
		
		const FName traceTag("WallClimbChecks");

		GetWorld()->DebugDrawTraceTag = traceTag;
		traceParams.TraceTag = traceTag;

		FVector playerPosition = GetActorLocation();
		float height = GetCapsuleComponent()->GetScaledCapsuleHalfHeight();
		float width = GetCapsuleComponent()->GetScaledCapsuleRadius();
		FVector startPoint = height * GetActorUpVector() + width * GetActorForwardVector() + playerPosition;
		FVector endPoint = startPoint + width * GetActorForwardVector();
		
		FHitResult wallCheckHit;
		GetWorld()->LineTraceSingleByChannel(
		wallCheckHit,
		startPoint,
		endPoint,
		ECC_Visibility,
		traceParams
		);
		if(wallCheckHit.bBlockingHit == false)
			return;

		FVector possibleStandingPosition = endPoint + height * GetActorUpVector() + GetActorUpVector() * 15.0f; //15.0f is just a little offset to make sure we can stand ON ground
		FHitResult possibleStandCheckSweepHit;
		GetWorld()->SweepSingleByChannel(
			possibleStandCheckSweepHit,
			possibleStandingPosition,
			possibleStandingPosition,
			GetActorRotation().Quaternion(),
			ECC_Visibility,
			GetCapsuleComponent()->GetCollisionShape(),
			traceParams);
		if(possibleStandCheckSweepHit.bBlockingHit == false)
		{
			if(GetVelocity().Z > EdgeGrabJumpForce)
				return;
			if(GetVelocity().Z >= EdgeGrabJumpForce * 0.4f)
			{
				GetCharacterMovement()->Velocity.Z += EdgeGrabJumpForce * 0.5f;
				return;
			}
			GetCharacterMovement()->SetMovementMode(MOVE_Flying);
			GetCharacterMovement()->StopMovementImmediately();
			GetCharacterMovement()->Velocity = FVector::ZeroVector;
			CurrentState = EPlayerState::EdgeHanging;
		}
	}
}

void APlayerCharacter::Look(const FInputActionValue& value)
{
	auto input = value.Get<FVector2D>();
	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(input.X);
		AddControllerPitchInput(input.Y);
	}
}

void APlayerCharacter::StartJump(const FInputActionValue& value)
{
	switch(CurrentState)
	{
	case EPlayerState::Normal:
		break;
	case EPlayerState::Sliding:
		break;
	case EPlayerState::Crouching:
		break;
	case EPlayerState::InAir:
		{
			//check for collisions in front, left, right
			FCollisionQueryParams traceParams = FCollisionQueryParams(FCollisionQueryParams::DefaultQueryParam);
			traceParams.bTraceComplex = false;
			traceParams.AddIgnoredActor(this);
			traceParams.bReturnPhysicalMaterial = false;
		
			const FName traceTag("WallChecks");

			GetWorld()->DebugDrawTraceTag = traceTag;
			traceParams.TraceTag = traceTag;

			FHitResult leftHit = RayCast(GetActorRightVector(), traceParams, WallCheckLength);
			FHitResult rightHit = RayCast(GetActorRightVector() * -1.0f, traceParams, WallCheckLength);
			FHitResult forwardHit = RayCast(GetActorForwardVector(), traceParams, WallCheckLength);
			FHitResult backHit = RayCast(-GetActorForwardVector(), traceParams, WallCheckLength);

			FHitResult finalWall = leftHit;
		
			if(!rightHit.bBlockingHit && !leftHit.bBlockingHit && !forwardHit.bBlockingHit && !backHit.bBlockingHit)
			{
				return;
			}

			if(rightHit.Distance < leftHit.Distance)
				finalWall = rightHit;

			if(forwardHit.Distance < finalWall.Distance || (!rightHit.bBlockingHit && !leftHit.bBlockingHit))
				finalWall = forwardHit;

			if(backHit.Distance < finalWall.Distance || (!rightHit.bBlockingHit && !forwardHit.bBlockingHit && !leftHit.bBlockingHit))
				finalWall = backHit;

			FVector pushForce = m_RelativeMovementInput * WallJumpPushForwardForce + finalWall.Normal * WallJumpPushAwayForce;
			float dotProduct = FVector::DotProduct(finalWall.Normal, m_RelativeMovementInput);
			if(dotProduct <= -0.7f)
			{
				pushForce.X = 0;
				pushForce.Y = 0;
				pushForce += FVector::UpVector * WallJumpClimbUpForce;
			}
			if(dotProduct <= -0.2f && dotProduct >= -0.7f)
			{
				pushForce += finalWall.Normal * WallJumpWeakPushAwayForce;
			}
			pushForce += FVector::UpVector * WallJumpUpForce;
			LaunchCharacter(pushForce, true, true);
			break;
		}
	case EPlayerState::EdgeHanging:
		if(m_RelativeMovementInput.Dot(GetActorForwardVector()) > 0.75f)
		{
			//jump and leave the entire state
			GetCharacterMovement()->SetMovementMode(MOVE_Walking);
			m_lastEdgeGrabTime = UGameplayStatics::GetRealTimeSeconds((GetWorld()));
			CurrentState = EPlayerState::InAir;
			LaunchCharacter(GetActorForwardVector() * EdgeGrabForwardForce + GetActorUpVector() * EdgeGrabJumpForce, true, true);
		}
		else
		{
			CurrentState = EPlayerState::InAir;
			m_lastEdgeGrabTime = UGameplayStatics::GetRealTimeSeconds((GetWorld()));
			GetCharacterMovement()->SetMovementMode(MOVE_Walking);
			LaunchCharacter(m_RelativeMovementInput * EdgeGrabForwardForce + GetActorUpVector() * EdgeGrabJumpForce, true, true);
		}
		break;
	default:
		break;
	}
	Jump();
}


FHitResult APlayerCharacter::RayCast(const FVector& direction, const FCollisionQueryParams& traceParams, const float length) const
{
	FVector playerPosition = GetActorLocation();
	
	FHitResult resultHit;
	GetWorld()->LineTraceSingleByChannel(
	resultHit,
	playerPosition,
	playerPosition + direction * length,
	ECC_Visibility,
	traceParams
	);
	if(resultHit.bBlockingHit == false)
		resultHit.Distance = FLT_MAX;
	return resultHit;
}

void APlayerCharacter::StopJump(const FInputActionValue& value)
{
	StopJumping();
	if(GetCharacterMovement()->Velocity.Z > 0)
		GetCharacterMovement()->Velocity.Z = 0;
}

void APlayerCharacter::StartSprint(const FInputActionValue& value)
{
	switch(CurrentState)
	{
	case Normal:
		GetCharacterMovement()->MaxWalkSpeed = SprintSpeed;
		break;
	case InAir:
		break;
	case Sliding:
		break;
	case Crouching:
		break;
	}
}

void APlayerCharacter::StopSprint(const FInputActionValue& value)
{
	switch(CurrentState)
	{
	case Normal:
		GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
		break;
	case InAir:
		break;
	case Sliding:
		break;
	case Crouching:
		break;
	}
}

void APlayerCharacter::StartCrouch(const FInputActionValue& value)
{
	switch(CurrentState)
	{
	case EPlayerState::Normal:
		break;
	case EPlayerState::Sliding:
		break;
	case EPlayerState::Crouching:
		break;
	case EPlayerState::InAir:
		break;
	case EPlayerState::EdgeHanging:
		CurrentState = EPlayerState::InAir;
		m_lastEdgeGrabTime = UGameplayStatics::GetRealTimeSeconds((GetWorld()));
		GetCharacterMovement()->SetMovementMode(MOVE_Walking);
		break;
	default:
		break;
	}
	Crouch();
}

void APlayerCharacter::StopCrouch(const FInputActionValue& value)
{
	UnCrouch();
}

