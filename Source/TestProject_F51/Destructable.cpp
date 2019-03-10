// Fill out your copyright notice in the Description page of Project Settings.

#include "Destructable.h"
#include "Net/UnrealNetwork.h"

ADestructable::ADestructable()
{
    bReplicates = true;
    bReplicateMovement = true;

    m_StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("Static Mesh");
    m_ExplosionParticle = CreateDefaultSubobject<UParticleSystemComponent>("Explosion Particle");

    RootComponent = m_StaticMeshComponent;
}

float ADestructable::TakeDamage(float DamageAmount, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser)
{
    m_HP -= DamageAmount;
    if (m_HP <= 0)
    {
        Multicast_DestroyAndPlayParticle(); // only server will call this
    }

    return m_HP;
}

void ADestructable::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);
    DOREPLIFETIME(ADestructable, m_HP);
}

void ADestructable::Multicast_DestroyAndPlayParticle_Implementation()
{
    if (m_ExplosionParticle)
    {
        m_ExplosionParticle->ActivateSystem();
        m_ExplosionParticle->OnSystemFinished.AddUniqueDynamic(this, &ADestructable::OnExplosionParticleEnd);

        if (m_StaticMeshComponent)
        {
            m_StaticMeshComponent->SetVisibility(false);
            m_StaticMeshComponent->BodyInstance.SetInstanceSimulatePhysics(false);
            m_StaticMeshComponent->BodyInstance.SetCollisionEnabled(ECollisionEnabled::NoCollision, true);
        }
    }
    else
        OnExplosionParticleEnd(nullptr);
}

void ADestructable::OnExplosionParticleEnd(UParticleSystemComponent * FinishedComponent)
{
    if (HasAuthority())
        Destroy(); // destroy on server and propagate to clients
}
