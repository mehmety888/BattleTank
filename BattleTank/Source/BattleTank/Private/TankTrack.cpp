// Fill out your copyright notice in the Description page of Project Settings.


#include "TankTrack.h"

UTankTrack::UTankTrack()
{
    PrimaryComponentTick.bCanEverTick = false;
}

void UTankTrack::BeginPlay()
{
    Super::BeginPlay();
    OnComponentHit.AddDynamic(this, &UTankTrack::OnHit);
}
void UTankTrack::OnHit(UPrimitiveComponent *HitComponent, 
                       AActor* OtherActor, 
                       UPrimitiveComponent* OtherComponent, 
                       FVector NormalImpulse, 
                       const FHitResult &Hit)
{
    DriveTrack();
    ApplySidewaysForce();
    // Reset Throttle
    CurrentThrottle = 0.f;
}

void UTankTrack::ApplySidewaysForce()
{
    // Calculate slippage speed
    auto SlippageSpeed = FVector::DotProduct(GetRightVector(), GetComponentVelocity());

    auto DeltaTime = GetWorld()->GetDeltaSeconds();
    // Work-out the required acceleration this frame to correct
    auto CorrectionAcceleration = - SlippageSpeed / DeltaTime * GetRightVector(); // opposite direction of slip 

    // Calculate and apply sideways force (F = ma)
    auto TankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent()); // mass property is inside static mesh component tank
    auto CorrectionForce = TankRoot->GetMass() * CorrectionAcceleration / 2; // because there are two tracks

    TankRoot->AddForce(CorrectionForce);
}

void UTankTrack::SetThrottle(float Throttle)
{
    CurrentThrottle = FMath::Clamp<float>(CurrentThrottle + Throttle, -1, 1);
}

void UTankTrack::DriveTrack()
{
    auto ForceApplied = GetForwardVector() * CurrentThrottle * TrackMaxDrivingForce;
    auto ForceLocation = GetComponentLocation();

    auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());

    TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
}