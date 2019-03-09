// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TestProject_F51Projectile.h"
#include "AwesomeMultiplayerProjectile.generated.h"

UCLASS()
class TESTPROJECT_F51_API AAwesomeMultiplayerProjectile : public ATestProject_F51Projectile
{
    GENERATED_BODY()

public:
    AAwesomeMultiplayerProjectile();

    virtual void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit) override;

protected:
    UPROPERTY(EditAnywhere)
    float m_DamageOnHit = 20.f;
};
