// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankPlayerController.h"



void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	ATank* ControlledTank = GetControlledTank();
	if (!ControlledTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerController not possessing tank"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerController possessing : %s"), *ControlledTank->GetName());
	}
}


// Called every frame
void ATankPlayerController::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
	AimTowardsCrosshair();
}


ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}


void ATankPlayerController::AimTowardsCrosshair()
{
	if (!GetControlledTank()) { return; }
	FVector HitLocation;
	if (GetSightRayHitLocation(HitLocation)) // OUT
	{
		GetControlledTank()->AimAt(HitLocation);
	}
}


bool ATankPlayerController::GetSightRayHitLocation(FVector& HitLocation) const
{
	int32 ViewportSizeX, ViewportSizeY; // Viewport sizes
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	// Calculate CrossHair pixel coords with X and Y percent of the screen defined in UIPlayer
	FVector2D ScreenLocation(CrossHairXLocation * ViewportSizeX, CrossHairYLocation * ViewportSizeY);
	
	FVector LookDirection;
	if (GetLookDirection(ScreenLocation, LookDirection)) // 2nd parm OUT
	{
		if(GetLookVectorHitLocation(LookDirection, HitLocation)) // 2nd parm OUT
		{
			return true;
		}
	}
	return false;
}


bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& WorldDirection) const
{
	FVector CameraWorldLocation; // Discarded
	return DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, CameraWorldLocation, WorldDirection);
}


bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const
{
	FVector StartLocation = PlayerCameraManager->GetCameraLocation(); // Camera location
	FVector EndDirection = StartLocation + (LookDirection * LineTraceRange); // Camera location + Look direction (like a rotator or vector unit) * trace range
	FHitResult HitResult;
	if (GetWorld()->LineTraceSingleByChannel( // Line Tracer
		HitResult,
		StartLocation,
		EndDirection,
		ECollisionChannel::ECC_Visibility
	))
	{
		HitLocation = HitResult.Location;
		return true;
	}
	HitLocation = FVector(0);
	return false;
}