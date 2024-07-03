// Fill out your copyright notice in the Description page of Project Settings.


#include "SplineMovement/Path.h"

APath::APath()
{
	PrimaryActorTick.bCanEverTick = true;

	SplinePath = CreateDefaultSubobject<USplineComponent>("Spline Path");
	SetRootComponent(SplinePath);
}

void APath::BeginPlay()
{
	Super::BeginPlay();
}



FVector APath::GetPositionAtSpline(float CurrentDistanceOnSpline)
{
	//SplinePath->GetDistanceAlongSplineAtLocation();

	SplinePath->GetSplineLength();
	FVector AtSplinePosition = SplinePath->GetLocationAtDistanceAlongSpline(CurrentDistanceOnSpline, ESplineCoordinateSpace::World);

	return AtSplinePosition + FVector(0.f, 0.f, 100.f);
}

float APath::GetSpeedMultipierBasedOnDistance(float Distance)
{
	if (Distance >= 0.f && Distance <= GetDistanceAtSplinePoint(1) || Distance >= GetDistanceAtSplinePoint(4) && Distance <= GetDistanceAtSplinePoint(5))
		return 1.f;
	else
		return 0.5f;
}
