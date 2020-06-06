// Fill out your copyright notice in the Description page of Project Settings.


#include "TankTrack.h"

UTankTrack::UTankTrack()
{
    PrimaryComponentTick.bCanEverTick = true;
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
    UE_LOG(LogTemp, Warning, TEXT("I am Hit"));
}

void UTankTrack::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
    Super::TickComponent(DeltaTime,TickType,ThisTickFunction);

    // Calculate slippage speed
    auto SlippageSpeed = FVector::DotProduct(GetRightVector(), GetComponentVelocity());

    // Work-out the required acceleration this frame to correct
    auto CorrectionAcceleration = - SlippageSpeed / DeltaTime * GetRightVector(); // opposite direction of slip 

    // Calculate and apply sideways force (F = ma)
    auto TankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent()); // mass property is inside static mesh component tank
    auto CorrectionForce = TankRoot->GetMass() * CorrectionAcceleration / 2; // because there are two tracks

    TankRoot->AddForce(CorrectionForce);
}

void UTankTrack::SetThrottle(float Throttle)
{
    // TODO: clamp actual throttle value so player can't over - drive

    auto ForceApplied = GetForwardVector() * Throttle * TrackMaxDrivingForce;
    auto ForceLocation = GetComponentLocation();

    auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());

    TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
}