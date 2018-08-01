// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "Tank.h"

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
        GetControlledTank() -> AimAt(HitLocation);
        // TODO: tell the controlled tank to aim at this point}
    }
    
}

bool ATankPlayerController::GetSightRayHitLocation(FVector& HitLocation) const
{
    
    // Find the crosshair position in pixel coordinates
    int32 ViewPortSizeX, ViewPortSizeY;
    GetViewportSize(ViewPortSizeX, ViewPortSizeY);
    auto ScreenLocation = FVector2D(CrossHairXLocation * ViewPortSizeX, CrossHairYLocation * ViewPortSizeY);

    FVector LookDirection;
    if ( GetLookDirection(ScreenLocation, LookDirection) )
    {
        // line trace along that look direction, and see what we hit (up to max range)
        GetLookVectorHitLocation(LookDirection, HitLocation);
        
    }
    return true;
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const
{
    // De-project the screen position of the crosshair to a world direction
    FVector CameraWorldLocation; // To be discarded
    return DeprojectScreenPositionToWorld(
               ScreenLocation.X,
               ScreenLocation.Y,
               CameraWorldLocation,
               LookDirection
            );
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const
{
    FHitResult HitResult;
    auto StartLocation = PlayerCameraManager -> GetCameraLocation();
    auto EndLocation = StartLocation + ( LookDirection * LineTraceRange);
    if (GetWorld() -> LineTraceSingleByChannel(
            HitResult,
            StartLocation,
            EndLocation,
            ECollisionChannel::ECC_Visibility)
    )
    {
        // Set hit location
        HitLocation = HitResult.Location;
        return true;
    }
    HitLocation = FVector(0);
    return false; // line trace did not succeed
}





