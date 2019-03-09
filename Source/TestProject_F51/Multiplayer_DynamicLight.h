// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/PointLightComponent.h"
#include "Components/BoxComponent.h"
#include "Engine/ActorChannel.h"
#include "Multiplayer_DynamicLight.generated.h"

UCLASS()
class TESTPROJECT_F51_API AMultiplayer_DynamicLight : public AActor
{
    GENERATED_BODY()

public:
    AMultiplayer_DynamicLight();

    virtual void GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const override;

    void ToggleLightVisibility();
    void ToggleLightColor();

protected:
    virtual void BeginPlay() override;

private:
    UFUNCTION()
    void OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

    UFUNCTION()
    void OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

    UFUNCTION()
    void OnRep_LightColor();

    UFUNCTION()
    void OnRep_LightVisibility();

    void SetupComponents();

private:
    // Components
    UPROPERTY(VisibleAnywhere)
    UStaticMeshComponent* m_StaticMeshComponent = nullptr;

    UPROPERTY(VisibleAnywhere)
    UPointLightComponent* m_PointLightComponent = nullptr;

    UPROPERTY(VisibleAnywhere)
    UBoxComponent* m_BoxCollision = nullptr;

    // Properties
    UPROPERTY(EditAnywhere)
    float m_OverlappingChangeColorSpeedFactor = 100.0f;

    UPROPERTY(EditAnywhere)
    float m_ChangeColorSpeedFactor = 10.0f;

    UPROPERTY(EditAnywhere)
    float m_ChangeColorHSVHueOffset = 120.0f; // 3 colors

    // Replicated Properties
    //UPROPERTY(Replicated)
    //bool m_OverlappingWithCharacter = false;

    UPROPERTY(ReplicatedUsing = OnRep_LightVisibility)
    bool m_LightVisibility = true;

    UPROPERTY(ReplicatedUsing = OnRep_LightColor)
    FLinearColor m_LightColorHSV;
};
