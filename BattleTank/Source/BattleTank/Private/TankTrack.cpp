// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"
#include "Components/PrimitiveComponent.h"




void UTankTrack::SetThrottle(float Throttle)
{
//    auto Time = GetWorld() -> GetTimeSeconds();
    auto Name = GetName();
    UE_LOG(LogTemp, Warning, TEXT("%s throttle: %f"), *Name, Throttle);
    
    // TODO: clamp the actual throttle value so that player can not overdrive
    
    auto ForceApplied = GetForwardVector() * Throttle * TrackMaxDrivingForce;
    auto ForceLocation = GetComponentLocation();
    auto TankRoot = Cast<UPrimitiveComponent> (GetOwner() -> GetRootComponent());
    
    TankRoot -> AddForceAtLocation(ForceApplied, ForceLocation);
}
