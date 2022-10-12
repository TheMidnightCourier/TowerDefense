// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectileBomb.h"
#include "Kismet/GameplayStatics.h"

AProjectileBomb::AProjectileBomb()
{
    ProjectileMovementComponent->bRotationFollowsVelocity = true;
    ProjectileMovementComponent->bShouldBounce = false;
    ProjectileMovementComponent->ProjectileGravityScale = 1.0f;
    CollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &AProjectileBomb::OnProjectileBeginOverlap);
}

void AProjectileBomb::SetInitialSpeedByTargetDistance(FVector Location, float ShootRate)
{
    FVector CurrentLocation = GetActorLocation();
    float Height = abs(CurrentLocation.Z);
    float Length = FVector::Distance(FVector(CurrentLocation.X, CurrentLocation.Y, Location.Z), Location);
}

void AProjectileBomb::OnProjectileBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
    if (OtherActor->ActorHasTag(TEXT("Surface")))
    {
        TArray<AActor*> IgnoreList;
        UGameplayStatics::ApplyRadialDamage(GetWorld(), Damage, SweepResult.Location, 300.f, NULL, IgnoreList, NULL, NULL, true);
        DrawDebugSphere(GetWorld(), SweepResult.Location, 300.f, 12, FColor::Yellow, true, 3.f, 0, 1);
        this->Destroy();
    }
}
