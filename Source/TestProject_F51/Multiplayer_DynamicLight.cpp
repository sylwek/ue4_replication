// Fill out your copyright notice in the Description page of Project Settings.

#include "Multiplayer_DynamicLight.h"
#include "TestProject_F51/TestProject_F51Character.h"
#include "Net/UnrealNetwork.h"

AMultiplayer_DynamicLight::AMultiplayer_DynamicLight()
{
    bReplicates = true;

    SetupComponents();

    m_LightColorHSV = FLinearColor::Red.LinearRGBToHSV();
}

void AMultiplayer_DynamicLight::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    //DOREPLIFETIME(AMultiplayer_DynamicLight, m_OverlappingWithCharacter);
    DOREPLIFETIME(AMultiplayer_DynamicLight, m_LightColorHSV);
    DOREPLIFETIME(AMultiplayer_DynamicLight, m_LightVisibility);
}

void AMultiplayer_DynamicLight::ToggleLightVisibility()
{
    if (HasAuthority())
    {
        m_LightVisibility = !m_LightVisibility;
        OnRep_LightVisibility();
    }
}

void AMultiplayer_DynamicLight::ToggleLightColor()
{
    if (HasAuthority())
    {
        m_LightColorHSV.R = fmodf(m_LightColorHSV.R + m_ChangeColorHSVHueOffset, 360.0f);
        OnRep_LightColor();
    }
}

void AMultiplayer_DynamicLight::BeginPlay()
{
    Super::BeginPlay();

    // update light's properties for late joining players
    OnRep_LightColor();
    OnRep_LightVisibility();
}

void AMultiplayer_DynamicLight::OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    if (HasAuthority())
    {
        UE_LOG(LogTemp, Warning, TEXT("OnBeginOverlap"));
        GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("OnBeginOverlap"));

        //if (auto player = Cast<ATestProject_F51Character>(OtherActor))
        //{
        //    m_OverlappingWithCharacter = true;
        //}
    }
}

void AMultiplayer_DynamicLight::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
    if (HasAuthority())
    {
        UE_LOG(LogTemp, Warning, TEXT("OnEndOverlap"));
        GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("OnEndOverlap"));

        //if (auto player = Cast<ATestProject_F51Character>(OtherActor))
        //{
        //    m_OverlappingWithCharacter = false;
        //}
    }
}

void AMultiplayer_DynamicLight::OnRep_LightColor()
{
    m_PointLightComponent->SetLightColor(m_LightColorHSV.HSVToLinearRGB());
}

void AMultiplayer_DynamicLight::OnRep_LightVisibility()
{
    m_PointLightComponent->SetVisibility(m_LightVisibility);
}

void AMultiplayer_DynamicLight::SetupComponents()
{
    m_StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("Static Mesh");
    m_PointLightComponent = CreateDefaultSubobject<UPointLightComponent>("Point Light");

    m_BoxCollision = CreateDefaultSubobject<UBoxComponent>("Box Collision");
    m_BoxCollision->OnComponentBeginOverlap.AddDynamic(this, &AMultiplayer_DynamicLight::OnBeginOverlap);
    m_BoxCollision->OnComponentEndOverlap.AddDynamic(this, &AMultiplayer_DynamicLight::OnEndOverlap);
    //m_BoxCollision->BodyInstance.SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics, true);
    m_BoxCollision->SetWorldScale3D(FVector(5.f, 5.f, 5.f));

    RootComponent = m_StaticMeshComponent;
}

