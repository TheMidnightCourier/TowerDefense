// Fill out your copyright notice in the Description page of Project Settings.

#include "TowerArcher.h"
#include "ProjectileBase.h"
#include "Kismet/KismetMathLibrary.h"
#include "TowerDefense/macros.h"

ATowerArcher::ATowerArcher()
{
}

void ATowerArcher::Shoot()
{
    GetWorldTimerManager().SetTimer(ShootTimeHandle, this, &ATowerArcher::ShootHandle, ShootRate, true);
}

void ATowerArcher::ShootHandle()
{
    ATowerBase::ShootHandle();

    if (ProjectileClass)
    {
        UWorld *World = GetWorld();
        if (World)
        {
            FActorSpawnParameters SpawnParams;
            SpawnParams.Owner = this;
            SpawnParams.Instigator = GetInstigator();

            AProjectileBase* Projectile = World->SpawnActor<AProjectileBase>(ProjectileClass, ShootLocation->GetRelativeLocation(), TowerTop->GetComponentRotation(), SpawnParams);
            DEBUGMESSAGE("Shoot Locatoin = %s", *ShootLocation->GetComponentLocation().ToString());
            if (Projectile)
            {
                FVector LaunchDirection = ShootTarget->GetActorLocation() - ShootLocation->GetComponentLocation();
                LaunchDirection.Normalize();
                Projectile->FireInDirection(LaunchDirection);
                Projectile->ProjectileMovementComponent->HomingTargetComponent = ShootTarget->GetRootComponent();
                D("Projectile Spawned");
            }
        }
    }
    else D("No ProjectileClass");
}
