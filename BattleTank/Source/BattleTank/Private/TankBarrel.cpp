// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBarrel.h"

void UTankBarrel::Elevate(float DegreesPerSecond)
{
    // Move the barrel to the right direction
    // Given a max elevation speed, and the frame time
    UE_LOG(LogTemp, Warning, TEXT("Barrel elevate has been called at %f"), DegreesPerSecond);
}
