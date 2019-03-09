// Fill out your copyright notice in the Description page of Project Settings.

#include "AwesomeMultiplayerProjectile.h"
#include "Destructable.h"
#include "GameFramework/DamageType.h"

AAwesomeMultiplayerProjectile::AAwesomeMultiplayerProjectile()
{
    bReplicates = true;
    bReplicateMovement = true;
}

void AAwesomeMultiplayerProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
    Super::OnHit(HitComp, OtherActor, OtherComp, NormalImpulse, Hit);

    if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr))
    {
        if (auto destructable = Cast<ADestructable>(OtherActor))
        {
            FDamageEvent DamageEvent(UDamageType::StaticClass());
            destructable->TakeDamage(m_DamageOnHit, DamageEvent, nullptr, this);
        }
    }
}
