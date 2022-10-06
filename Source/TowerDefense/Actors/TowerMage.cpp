// Fill out your copyright notice in the Description page of Project Settings.


#include "TowerMage.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"

void ATowerMage::Shoot()
{
    GetWorldTimerManager().SetTimer(ShootTimeHandle, this, &ATowerMage::ShootHandle, ShootRate, true, 0.0f);
}

void ATowerMage::ShootHandle()
{
    ATowerBase::ShootHandle();

    UWorld* World = GetWorld();
    if (World)
    {
        FVector CollisionLoc = ShootTarget->FindComponentByClass<UCapsuleComponent>()->GetComponentLocation();
        UGameplayStatics::ApplyDamage(ShootTarget, 1, NULL, this, NULL);
        DrawDebugLine(World, ShootLocation->GetComponentLocation(), CollisionLoc, FColor::Red, true, -1, 0, 10);
    }
}
