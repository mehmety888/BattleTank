// Fill out your copyright notice in the Description page of Project Settings.


#include "TankTrack.h"

void UTankTrack::SetThrottle(float Throttle)
{
    FString Name = GetName();
    UE_LOG(LogTemp, Warning, TEXT("%s have a throttle %f"), *Name, Throttle);

    // TODO: clamp actual throttle value so player can't over - drive
}