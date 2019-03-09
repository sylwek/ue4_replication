// Fill out your copyright notice in the Description page of Project Settings.

#include "LightSwitcherCharacter.h"
#include "Components/CapsuleComponent.h"
#include "AwesomeMultiplayerProjectile.h"
#include "Net/UnrealNetwork.h"

ALightSwitcherCharacter::ALightSwitcherCharacter()
{
    if (auto capsuleComponent = GetCapsuleComponent())
    {
        capsuleComponent->OnComponentBeginOverlap.AddDynamic(this, &ALightSwitcherCharacter::OnBeginOverlap);
        capsuleComponent->OnComponentEndOverlap.AddDynamic(this, &ALightSwitcherCharacter::OnEndOverlap);
    }

    ProjectileClass = TSubclassOf<class AAwesomeMultiplayerProjectile>();
}

void ALightSwitcherCharacter::SetupPlayerInputComponent(UInputComponent* InputComponent)
{
    Super::SetupPlayerInputComponent(InputComponent);
    InputComponent->BindAction("ToggleLightSwitch", IE_Pressed, this, &ALightSwitcherCharacter::ToggleLightSwitch);
    InputComponent->BindAction("ToggleLightColor", IE_Pressed, this, &ALightSwitcherCharacter::ToggleLightColor);
}

void ALightSwitcherCharacter::OnFire()
{
    // override implementation
    ServerFire();

    if (Role < ROLE_Authority)
    {
        PlayFireSound();
        PlayFireAnim();
    }
}

void ALightSwitcherCharacter::ServerFire_Implementation()
{
    Super::OnFire();
}

bool ALightSwitcherCharacter::ServerFire_Validate()
{
    return true;
}

void ALightSwitcherCharacter::ToggleLightSwitch()
{
    if (m_OverlappedLight)
        m_OverlappedLight->ToggleLightVisibility(); // visibility will be updated from server anyway and overrided if needed

    if (Role < ROLE_Authority)
        ServerToggleLightSwitch();
}

void ALightSwitcherCharacter::ToggleLightColor()
{
    if (m_OverlappedLight)
        m_OverlappedLight->ToggleLightColor();

    if (Role < ROLE_Authority)
        ServerToggleLightColor();
}

void ALightSwitcherCharacter::ServerToggleLightSwitch_Implementation()
{
    ToggleLightSwitch();
}

bool ALightSwitcherCharacter::ServerToggleLightSwitch_Validate()
{
    return true;
}

void ALightSwitcherCharacter::ServerToggleLightColor_Implementation()
{
    ToggleLightColor();
}

bool ALightSwitcherCharacter::ServerToggleLightColor_Validate()
{
    return true;
}

void ALightSwitcherCharacter::OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    if (auto light = Cast<AMultiplayer_DynamicLight>(OtherActor))
        m_OverlappedLight = light;
}

void ALightSwitcherCharacter::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
    if (auto light = Cast<AMultiplayer_DynamicLight>(OtherActor))
        m_OverlappedLight = nullptr;
}
