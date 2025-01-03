#include "CameraTransitionerComponent.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

UCameraTransitionerComponent::UCameraTransitionerComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UCameraTransitionerComponent::BeginPlay()
{
	Super::BeginPlay();
	if(!CreateStateOnBeginPlay)
		return;
	m_CurrentSettings = FCameraSettingsState(
		m_SpringArmComponent->TargetArmLength,
		m_CameraComponent->FieldOfView,
		m_SpringArmComponent->SocketOffset,
		1.0);
}

void UCameraTransitionerComponent::Lerp(float t)
{
	float fov = FMath::Lerp(m_CameraComponent->FieldOfView, m_CurrentSettings.FOV, t);
	float armLength = FMath::Lerp(m_SpringArmComponent->TargetArmLength, m_CurrentSettings.ArmLength, t);
	FVector socketOffset = FMath::Lerp(m_SpringArmComponent->SocketOffset, m_CurrentSettings.SocketOffset, t);
	m_CameraComponent->FieldOfView = fov;
	m_SpringArmComponent->TargetArmLength = armLength;
	m_SpringArmComponent->SocketOffset = socketOffset;
}

void UCameraTransitionerComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                                 FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	Lerp(DeltaTime * m_CurrentSettings.TransitionSpeed);
}

void UCameraTransitionerComponent::ChangeCameraSettingsState(const FCameraSettingsState& NewCameraSettingsState)
{
	if(m_CurrentSettings == NewCameraSettingsState)
		return;
	m_CurrentSettings = NewCameraSettingsState;
}

void UCameraTransitionerComponent::ImmediateChangeCameraSettingsState(
	const FCameraSettingsState& NewCameraSettingsState)
{
	if(m_CurrentSettings == NewCameraSettingsState)
		return;
	m_CurrentSettings = NewCameraSettingsState;
	Lerp(1);
}

