// Fill out your copyright notice in the Description page of Project Settings.

#define OUT
#include "TankPlayerController.h"
#include "Engine/World.h"


void ATankPlayerController::BeginPlay()
{
    Super::BeginPlay();

    ATank* PossessedTank = nullptr;
    PossessedTank  = GetControlledTank();
    if(PossessedTank == nullptr)
    {
        UE_LOG(LogTemp,Error,TEXT("PlayerController not possessing a tank"));
    }
    else 
    {
        UE_LOG(LogTemp,Warning,TEXT("PlayerController possessing %s"),*PossessedTank->GetName());
    }    
}

void ATankPlayerController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    AimTowardsCrossHair();
}



ATank* ATankPlayerController::GetControlledTank() const
{
    return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimTowardsCrossHair()
{
    if(!GetControlledTank())
    {
        return;
    }

    FVector OUT HitLocation;

    if(GetSightRayHitLocation (OUT HitLocation))
    {
        UE_LOG(LogTemp, Warning, TEXT("HitLocation: %s"),*HitLocation.ToString())
    } 
    // Get World Location if linetrace through crosshair
    // If it hits the landscape 
        // Tell controlled tank to aim at this point
}

bool ATankPlayerController::GetSightRayHitLocation (FVector& HitLocation)const
{
    HitLocation = FVector(1.0f);
    return true;
}