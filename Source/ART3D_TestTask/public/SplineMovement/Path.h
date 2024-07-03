// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SplineComponent.h"
#include "Path.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAllCubesSpawnedSignature);

UCLASS()
class ART3D_TESTTASK_API APath : public AActor
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintAssignable) FOnAllCubesSpawnedSignature OnAllCubesSpawned;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Actor Components") USplineComponent* SplinePath;

public:	
	APath();
	UFUNCTION(BlueprintCallable, BlueprintPure) USplineComponent* GetSplineComponent() const { return SplinePath; }
	
	// @return Returns -1.0 if the given index of point is invalid (PointIndex < 0 or PointIndex >= NumberOfSplinePoints), otherwise returns distance to next point.
	UFUNCTION(BlueprintCallable, BlueprintPure) FVector GetPositionAtSpline(float CurrentDistanceOnSpline);	
	
	UFUNCTION(BlueprintCallable, BlueprintPure) float GetDistanceAtSplinePoint(int32 Index) { return SplinePath->GetDistanceAlongSplineAtSplinePoint(Index); }
	
	float GetSpeedMultipierBasedOnDistance(float Distance);

protected:
	virtual void BeginPlay() override;
};
