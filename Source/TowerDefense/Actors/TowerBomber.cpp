// Fill out your copyright notice in the Description page of Project Settings.

#include "TowerBomber.h"
#include "DrawDebugHelpers.h"
#include "Kismet/KismetMathLibrary.h"
#define cos45 sqrt(2) / 2

void ATowerBomber::Shoot()
{
    if (!ProjectileClass)
        return;
    if (GetWorldTimerManager().IsTimerActive(ShootTimeHandle) && GetWorldTimerManager().GetTimerElapsed(ShootTimeHandle) != -1)
	{
		D("CD is on");
		return;
	}
    GetWorldTimerManager().SetTimer(ShootTimeHandle, this, &ATowerBomber::ShootHandle, ShootRate, true, 0.0f);
}

void ATowerBomber::ShootHandle()
{
    ATowerBase::ShootHandle();

    FActorSpawnParameters SpawnParams;
    SpawnParams.Owner = this;
    SpawnParams.Instigator = GetInstigator();

    FVector StartPoint = ShootLocation->GetComponentLocation();

    AProjectileBomb *Projectile = GetWorld()->SpawnActor<AProjectileBomb>(ProjectileClass, StartPoint, TowerTop->GetComponentRotation(), SpawnParams);
    if (Projectile)
    {
        AEnemyBase* Enemy = Cast<AEnemyBase>(ShootTarget);
        FVector EnemyLocPrediction = Enemy->GetLocationAfterTime(ShootRate);

        float HeightCoeff = Projectile->ProjectileMovementComponent->ProjectileGravityScale*ShootRate*ShootRate/2;
        double Height = (StartPoint.Z - EnemyLocPrediction.Z) * HeightCoeff;
        FVector HeightPoint = FVector(EnemyLocPrediction.X, EnemyLocPrediction.Y, Height);

        DrawDebugLine(GetWorld(), StartPoint,EnemyLocPrediction, FColor::Red, true, -1, 0, 1);
        DrawDebugLine(GetWorld(), ShootLocation->GetComponentLocation(), HeightPoint, FColor::Red, true, -1, 0, 1);
        
        FVector LaunchDirection = HeightPoint - ShootLocation->GetComponentLocation();
        LaunchDirection.Z *= 1.5;
        LaunchDirection.X /= 2.5;
        LaunchDirection.Y /= 2.5;
        TowerTop->SetWorldRotation(UKismetMathLibrary::FindLookAtRotation(TowerTop->GetComponentLocation(), HeightPoint));\
        Projectile->SetActorLocation(ShootLocation->GetComponentLocation());

        Projectile->Damage = Damage;
        Projectile->FireInDirection(LaunchDirection);

    }
}
