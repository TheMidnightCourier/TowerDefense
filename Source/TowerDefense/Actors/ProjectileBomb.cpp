// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectileBomb.h"

AProjectileBomb::AProjectileBomb()
{
    ProjectileMovementComponent->bRotationFollowsVelocity = true;
    ProjectileMovementComponent->bShouldBounce = false;
    ProjectileMovementComponent->ProjectileGravityScale = 1.0f;
}

void AProjectileBomb::SetInitialSpeedByTargetDistance(FVector Location, float ShootRate)
{
    FVector CurrentLocation = GetActorLocation();
    float Height = abs(CurrentLocation.Z);
    float Length = FVector::Distance(FVector(CurrentLocation.X, CurrentLocation.Y, Location.Z), Location);
}
