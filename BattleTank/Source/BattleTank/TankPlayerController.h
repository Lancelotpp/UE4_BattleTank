// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Tank.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h" // Must be the last include

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
private:

	virtual void BeginPlay() override;
	virtual void Tick( float DeltaSeconds ) override;

	ATank* GetControlledTank() const;

	// Start the tank moving the barrel so that shot would hit 
	// where the crosshair intersects the world
	void AimTowardsCrosshair();

	// True if ray hit landscape, out parameter of hit location
	bool GetSightRayHitLocation(FVector &HitLocation) const;
	// "De-project" crosshair position to a world direction 
	bool GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const;
	// Location of the look direction is hitting
	bool GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const;

	UPROPERTY(EditAnywhere)
	float CrossHairXLocation = 0.50;
	UPROPERTY(EditAnywhere)
	float CrossHairYLocation = 0.33;
	UPROPERTY(EditAnywhere)
	float LineTraceRange = 1000000; // in Cm : 10Km
};
