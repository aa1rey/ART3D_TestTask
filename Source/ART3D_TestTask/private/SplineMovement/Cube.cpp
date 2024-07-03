// Fill out your copyright notice in the Description page of Project Settings.


#include "SplineMovement/Cube.h"
#include "SplineMovement/Path.h"
#include "Components/SplineComponent.h"
#include "Kismet/KismetMathLibrary.h"

ACube::ACube()
{
	PrimaryActorTick.bCanEverTick = true;
	CurrentDistanceAtSpline = 0.f;
	MaxMovementSpeed = 10.f;
	SetActorHiddenInGame(true);

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	SetRootComponent(StaticMeshComponent);
}

void ACube::BeginSplineMovement()
{
	CubeMaterial = UMaterialInstanceDynamic::Create(StaticMeshComponent->GetMaterial(0), this);
	StaticMeshComponent->SetMaterial(0, CubeMaterial);

	if (Path)
	{
		SplineLength = Path->GetSplineComponent()->GetSplineLength();
		SetActorLocation(Path->GetPositionAtSpline(Path->GetDistanceAtSplinePoint(0)));
		GetWorldTimerManager().SetTimer(PathMovementHandle, this, &ThisClass::MoveAlongPath, 0.01f, true, 0.f);
	}
	else UE_LOG(LogTemp, Error, TEXT("Cube needs a Path reference to be moved along! Path reference is none!"));
}

void ACube::SetCubeColor(ECubeColor ColorID, FLinearColor LinearColor)
{
	CubeColor = ColorID;
	if (CubeMaterial) CubeMaterial->SetVectorParameterValue("Color", LinearColor);
}

void ACube::BeginPlay()
{
	Super::BeginPlay();
}

void ACube::MoveAlongPath()
{
	float MovementSpeed = MaxMovementSpeed * Path->GetSpeedMultipierBasedOnDistance(CurrentDistanceAtSpline);

	CurrentDistanceAtSpline = UKismetMathLibrary::FInterpTo_Constant(
		CurrentDistanceAtSpline + MovementSpeed <= SplineLength ? CurrentDistanceAtSpline + MovementSpeed : 0.f,
		SplineLength,
		GetWorld()->GetDeltaSeconds(),
		0.5f);
	SetActorLocation(Path->GetPositionAtSpline(CurrentDistanceAtSpline));


}
