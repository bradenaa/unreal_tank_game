// Fill out your copyright notice in the Description page of Project Settings.

#include "TankMovementComponent.h"
#include "TankTrack.h"
#include "GameFramework/Actor.h"

void UTankMovementComponent::Initialise(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet)
{
    LeftTrack = LeftTrackToSet;
    RightTrack = RightTrackToSet;
}

void UTankMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed)
{
    // No need to call Super because we are replacing the functionality here
    auto TankName = GetOwner() -> GetName();
    auto TankForward = GetOwner() -> GetActorForwardVector().GetSafeNormal();
    auto AIForwardIntention = MoveVelocity.GetSafeNormal();
    float ForwardThrow = FVector::DotProduct(TankForward, AIForwardIntention);
    
    IntendMoveForward(ForwardThrow);
    UE_LOG(LogTemp, Warning, TEXT("%s vectoring at %f"), *TankName, ForwardThrow);
}

void UTankMovementComponent::IntendMoveForward(float Throw)
{
    if (!LeftTrack || !RightTrack) { return; };
    LeftTrack -> SetThrottle(Throw);
    RightTrack -> SetThrottle(Throw);
    
    // TODO: prevent double-speed due to dual control use
}

void UTankMovementComponent::IntendTurnRight(float Throw)
{
    if (!LeftTrack || !RightTrack) { return; };
    LeftTrack -> SetThrottle(Throw);
    RightTrack -> SetThrottle(-Throw);
    
    // TODO: prevent double-speed due to dual control use
}

void UTankMovementComponent::IntendTurnLeft(float Throw)
{
    if (!LeftTrack || !RightTrack) { return; };
    LeftTrack -> SetThrottle(-Throw);
    RightTrack -> SetThrottle(Throw);
    
    // TODO: prevent double-speed due to dual control use
}

