// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TestProject_F51Character.h"
#include "Multiplayer_DynamicLight.h"
#include "LightSwitcherCharacter.generated.h"

UCLASS()
class TESTPROJECT_F51_API ALightSwitcherCharacter : public ATestProject_F51Character
{
    GENERATED_BODY()

public:
    ALightSwitcherCharacter();

protected:
    virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;
    virtual void OnFire() override;

    UFUNCTION(Server, Reliable, WithValidation)
    void ServerFire();

    void ToggleLightSwitch();
    void ToggleLightColor();

    UFUNCTION(Server, Reliable, WithValidation)
    void ServerToggleLightSwitch();

    UFUNCTION(Server, Reliable, WithValidation)
        void ServerToggleLightColor();

private:
    UFUNCTION()
    void OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

    UFUNCTION()
    void OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

private:
    AMultiplayer_DynamicLight* m_OverlappedLight = nullptr;
};
