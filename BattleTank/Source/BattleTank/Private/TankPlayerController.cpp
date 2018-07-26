// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"




void ATankPlayerController::BeginPlay()
{
    Super::BeginPlay();
    
    auto ControlledTank = GetControlledTank();
    if (!ControlledTank)
    {
        UE_LOG(LogTemp, Warning, TEXT("PlayerController not possessing a tank"));
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("PlayerController possessing %s"), *(ControlledTank -> GetName()) );
    }
}

void ATankPlayerController::Tick(float DeltaTime)
{
    // Super
    Super::Tick( DeltaTime );
    
    // AimTowardsCrosshair
    AimTowardsCrosshair();

}

ATank* ATankPlayerController::GetControlledTank() const
{
    return Cast<ATank>(GetPawn());
    
}

void ATankPlayerController::AimTowardsCrosshair()
{
    if (!GetControlledTank()) { return; }
    
    FVector HitLocation; // Out parameters
    
    if (GetSightRayHitLocation(HitLocation)) // Has 'side-effect, is going to line trace'
    {
        UE_LOG(LogTemp, Warning, TEXT("Hit location: %s"), *HitLocation.ToString());
        // TODO: tell the controlled tank to aim at this point}
    }
    
}

bool ATankPlayerController::GetSightRayHitLocation(FVector& OutHitLocation) const
{
    
    OutHitLocation = FVector(1.0);
    // ray cast through the crosshair
        // if the ray cast hits something
            // give out parameter of the location
            // return true
        // otherwise return false
    
    return true;
}



