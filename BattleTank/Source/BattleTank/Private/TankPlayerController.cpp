// Fill out your copyright notice in the Description page of Project Settings.

#define OUT

#include "TankPlayerController.h"
#include "Camera/PlayerCameraManager.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "TankAimingComponent.h"


void ATankPlayerController::BeginPlay()
{
    Super::BeginPlay();

    auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
    if(!ensure(AimingComponent))
    {
        return;
    }
    FoundAimingComponent(AimingComponent);

}
void ATankPlayerController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    AimTowardsCrossHair();
}

void ATankPlayerController::AimTowardsCrossHair()
{
    if(!GetPawn()) 
    {
        return;
    }
    auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
    if(!ensure(AimingComponent))
    {
        return;
    }

    FVector HitLocation;

    if(GetSightRayHitLocation (OUT HitLocation))
    {
        AimingComponent->AimAt(HitLocation);
    } 
}

bool ATankPlayerController::GetSightRayHitLocation (FVector& HitLocation)const
{
    // Find the crosshair position
    int32 ViewportSizeX, ViewportSizeY;
    GetViewportSize(ViewportSizeX, ViewportSizeY);

    auto ScreenLocation = FVector2D(ViewportSizeX * CrosshairXLocation, ViewportSizeY * CrosshairYLocation);
    FVector LookDirection;

    if(GetLookDirection(ScreenLocation,LookDirection))
    {
        // Line-trace along that look direction, and see what we hit (up to max range)
        return GetLookVectorHitLocation(LookDirection,HitLocation); 
    }

    return true;
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const
{
    FVector CameraWorldLocation;

    // "de-project" the screen position of the crosshair to a world direction,
    return DeprojectScreenPositionToWorld(
        ScreenLocation.X, 
        ScreenLocation.Y, 
        CameraWorldLocation, 
        LookDirection
    );
}
bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector& OUT HitLocation)const
{
    FHitResult HitResult;
	// Ray-cast out to a certain distance (Reach)
    
    FVector StartLocation = PlayerCameraManager->GetCameraLocation();
    FVector EndLocation = StartLocation + LineTraceRange * LookDirection;

    if(GetWorld()->LineTraceSingleByChannel(
        OUT HitResult,
        StartLocation,
        EndLocation,
        ECollisionChannel::ECC_Visibility
    ))
    {
        HitLocation = HitResult.Location;
        return true;
    }
    else
    {  
        HitLocation = FVector(0);
        return false;
    }
}