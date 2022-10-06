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
    GetWorldTimerManager().SetTimer(ShootTimeHandle, this, &ATowerArcher::ShootHandle, ShootRate, true, 0.0f);
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

            UCapsuleComponent* Collision = ShootTarget->FindComponentByClass<UCapsuleComponent>();

            if (!Collision) {
                D("No collision found!");
                return;
            }

            AProjectileBase* Projectile = World->SpawnActor<AProjectileBase>(ProjectileClass, ShootLocation->GetComponentLocation(), TowerTop->GetComponentRotation(), SpawnParams);
            DEBUGMESSAGE("Shoot Locatoin = %s", *ShootLocation->GetComponentLocation().ToString());
            if (Projectile)
            {
                FVector LaunchDirection = Collision->GetComponentLocation() - ShootLocation->GetComponentLocation();
                LaunchDirection.Normalize();
                Projectile->FireInDirection(LaunchDirection);
                Projectile->ProjectileMovementComponent->HomingTargetComponent = Collision;
            }
        }
    }
    else D("No ProjectileClass");
}
