// Fill out your copyright notice in the Description page of Project Settings.


#include "TankPlayerController.h"

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

ATank* ATankPlayerController::GetControlledTank() const
{
    return Cast<ATank>(GetPawn());
}