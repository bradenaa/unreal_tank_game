// Fill out your copyright notice in the Description page of Project Settings.


#include "TankBarrel.h"
#include "TankAimingComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/GameplayStaticsTypes.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
    PrimaryComponentTick.bCanEverTick = true; // TODO: Should this really tick?

	// ...
}

void UTankAimingComponent::SetBarrelReference(UTankBarrel *BarrelToSet)
{
    Barrel = BarrelToSet;
}

void UTankAimingComponent::AimAt(FVector HitLocation, float LaunchSpeed)
{
    if (!Barrel) { return; }
    FVector OutLaunchVelocity;
    FVector StartLocation = Barrel -> GetSocketLocation(FName("Projectile"));

    
    // Calculate the OutLaunchVelocity
    bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity
    (
        this,
        OutLaunchVelocity,
        StartLocation,
        HitLocation,
        LaunchSpeed,
        ESuggestProjVelocityTraceOption::DoNotTrace
     );
    
    if (bHaveAimSolution)
    {
        auto AimDirection = OutLaunchVelocity.GetSafeNormal();
        auto Time = GetWorld() -> GetTimeSeconds();
        UE_LOG(LogTemp, Warning, TEXT("%f: move barrel called"), Time);
        MoveBarrelTowards(AimDirection);
    }
    // If no solution found - do nothing
    else
    {
        auto Time = GetWorld() -> GetTimeSeconds();
        UE_LOG(LogTemp, Warning, TEXT("%f: no aim solution found"), Time);
    }

    
}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
    // work out difference between current barrel rotation, and AimDirection
    auto BarrelRotator = Barrel -> GetForwardVector().Rotation();
    auto AimAsRotator = AimDirection.Rotation();
    auto DeltaRotator = AimAsRotator - BarrelRotator;
    
    Barrel -> Elevate(5); // TODO: Remove magic number
    
}











