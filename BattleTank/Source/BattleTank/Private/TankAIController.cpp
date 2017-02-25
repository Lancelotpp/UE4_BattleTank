// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankAIController.h"



void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	ATank* ControlledTank = GetControlledTank();
	if (!ControlledTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("AIController not possessing tank"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("AIController possessing : %s"), *ControlledTank->GetName());
	}

	ATank* PlayerTank = GetPlayerTank();
	if (!PlayerTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("Player not controlling tank"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Player controlling : %s"), *PlayerTank->GetName());
	}
}


void ATankAIController::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
	if (GetPlayerTank)
	{
		// Move towards the player

		GetControlledTank()->AimAt(GetPlayerTank()->GetActorLocation()); // Aim at player location

		// Fire if ready
	}
}

ATank* ATankAIController::GetPlayerTank() const
{
	return Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
}


ATank* ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}
