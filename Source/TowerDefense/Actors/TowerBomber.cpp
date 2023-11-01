// Fill out your copyright notice in the Description page of Project Settings.

#include "TowerBomber.h"
#include "DrawDebugHelpers.h"
#include "Kismet/KismetMathLibrary.h"
#include "GameFramework/WorldSettings.h"
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

        /* Old Method
        float HeightCoeff = Projectile->ProjectileMovementComponent->ProjectileGravityScale*ShootRate*ShootRate/2;
        double Height = (StartPoint.Z - EnemyLocPrediction.Z) * HeightCoeff;
        FVector HeightPoint = FVector(EnemyLocPrediction.X, EnemyLocPrediction.Y, Height);

        FVector LengthToTarget = EnemyLocPrediction - FVector(StartPoint.X, StartPoint.Y, 0);
        FVector HorizontalVelocityVector = LengthToTarget / ShootRate;
        FVector VerticalVelocityVector= FVector(0, 0, (980 * ShootRate) / 2 - StartPoint.Z / ShootRate);

        Old method
        DrawDebugLine(GetWorld(), StartPoint,EnemyLocPrediction, FColor::Red, true, -1, 0, 1);
        DrawDebugLine(GetWorld(), ShootLocation->GetComponentLocation(), HeightPoint, FColor::Red, true, -1, 0, 1);
        
        FVector LaunchDirection = HeightPoint - ShootLocation->GetComponentLocation();
        LaunchDirection.Z *= 1.5;
        LaunchDirection.X /= 2.5;
        LaunchDirection.Y /= 2.5;
        TowerTop->SetWorldRotation(UKismetMathLibrary::FindLookAtRotation(TowerTop->GetComponentLocation(), HeightPoint));
        Projectile->SetActorLocation(ShootLocation->GetComponentLocation());

        Projectile->Damage = Damage;
        Projectile->FireInDirection(LaunchDirection);*/ 

        // New Method
        FVector LengthToTarget = EnemyLocPrediction - FVector(StartPoint.X, StartPoint.Y, 0);
        FVector HorizontalVelocityVector = LengthToTarget / ShootRate;
        FVector VerticalVelocityVector= FVector(0, 0, (970 * ShootRate) / 2 - StartPoint.Z / ShootRate);

        FVector LaunchDirection = HorizontalVelocityVector + VerticalVelocityVector;

        DrawDebugLine(GetWorld(), StartPoint, StartPoint + HorizontalVelocityVector + VerticalVelocityVector, FColor::Green, false, ShootRate, 0, 1);
        DrawDebugLine(GetWorld(), StartPoint,EnemyLocPrediction, FColor::Red, false, ShootRate, 0, 1);

        TowerTop->SetWorldRotation(UKismetMathLibrary::FindLookAtRotation(TowerTop->GetComponentLocation(), StartPoint + LaunchDirection));
        Projectile->SetActorLocation(ShootLocation->GetComponentLocation());

        Projectile->Damage = Damage;
        Projectile->FireInDirection(LaunchDirection);
    }
}
