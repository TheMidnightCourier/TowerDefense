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
    if (GetWorldTimerManager().IsTimerActive(ShootTimeHandle) && GetWorldTimerManager().GetTimerElapsed(ShootTimeHandle) != -1)
	{
		return;
	}
    GetWorldTimerManager().SetTimer(ShootTimeHandle, this, &ATowerArcher::ShootHandle, ShootRate, true, 0.0f);
}

void ATowerArcher::ShootHandle()
{
    ATowerBase::ShootHandle();

    if (ProjectileClass && ShootTarget)
    {
        UWorld *World = GetWorld();
        if (World)
        {
            FActorSpawnParameters SpawnParams;
            SpawnParams.Owner = this;
            SpawnParams.Instigator = GetInstigator();

            UCapsuleComponent* Collision = ShootTarget->FindComponentByClass<UCapsuleComponent>();

            if (!Collision) {
                return;
            }

            AProjectileBase* Projectile = World->SpawnActor<AProjectileBase>(ProjectileClass, ShootLocation->GetComponentLocation(), TowerTop->GetComponentRotation(), SpawnParams);
            
            if (Projectile)
            {
                FVector LaunchDirection = Collision->GetComponentLocation() - ShootLocation->GetComponentLocation();
                LaunchDirection.Normalize();
                Projectile->FireInDirection(LaunchDirection);
                Projectile->ProjectileMovementComponent->HomingTargetComponent = Collision;
                Projectile->Damage = Damage;
                Projectile->FireDamage = HasFireDamage;
            }
        }
    }  
}
