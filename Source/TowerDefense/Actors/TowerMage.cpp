// Fill out your copyright notice in the Description page of Project Settings.


#include "TowerMage.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"

void ATowerMage::Shoot()
{
    if (ShootTarget)
    {
        AEnemyBase* Enemy = Cast<AEnemyBase>(ShootTarget);
        if (Enemy->MovementSpeed == Enemy->DefaultMovementSpeed)
        {
            Enemy->MovementSpeed *= 1 - Slowdown;
            DEBUGMESSAGE("New speed = %f", Enemy->MovementSpeed);
            Enemy->SetNewSpeed();
        }
    }
    GetWorldTimerManager().SetTimer(ShootTimeHandle, this, &ATowerMage::ShootHandle, ShootRate, true, 0.0f);
}

void ATowerMage::ShootHandle()
{
    ATowerBase::ShootHandle();

    UWorld* World = GetWorld();
    if (World)
    {
        FVector CollisionLoc = ShootTarget->FindComponentByClass<UCapsuleComponent>()->GetComponentLocation();
        UGameplayStatics::ApplyDamage(ShootTarget, Damage, NULL, this, NULL);
        DrawDebugLine(World, ShootLocation->GetComponentLocation(), CollisionLoc, FColor::Red, false, .1f, 0, 10);
    }
}
