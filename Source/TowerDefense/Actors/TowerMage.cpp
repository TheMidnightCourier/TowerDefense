// Fill out your copyright notice in the Description page of Project Settings.


#include "TowerMage.h"
#include "DrawDebugHelpers.h"

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
        DrawDebugLine(World, ShootLocation->GetComponentLocation(), ShootTarget->GetActorLocation(), FColor::Red, true, -1, 0, 10);
    }
}
