// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Destructable.generated.h"

UCLASS()
class TESTPROJECT_F51_API ADestructable : public AActor
{
    GENERATED_BODY()

public:
    ADestructable();

    virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, class AActor* DamageCauser) override;
    virtual void GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const override;

protected:
    UFUNCTION(NetMulticast, Reliable)
    void Multicast_DestroyAndPlayParticle();

    UFUNCTION()
    virtual void OnExplosionParticleEnd(class UParticleSystemComponent* FinishedComponent);

protected:
    // Components
    UPROPERTY(VisibleAnywhere)
    UStaticMeshComponent* m_StaticMeshComponent = nullptr;

    UPROPERTY(VisibleAnywhere)
    UParticleSystemComponent* m_ExplosionParticle = nullptr;

    // Properties
    UPROPERTY(EditAnywhere, Replicated)
    float m_HP = 20.f;
};
