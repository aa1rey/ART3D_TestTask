// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Color/CubeColor.h"
#include "Cube.generated.h"

UCLASS()
class ART3D_TESTTASK_API ACube : public AActor
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Path Movement") class APath* Path;
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Actor Components") UStaticMeshComponent* StaticMeshComponent;
	UPROPERTY(EditDefaultsOnly) float MaxMovementSpeed;

	FTimerHandle PathMovementHandle;
	float CurrentDistanceAtSpline;
	float SplineLength;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly) ECubeColor CubeColor;
	UMaterialInstanceDynamic* CubeMaterial;
	FLinearColor CubeLinearColor;
public:	
	ACube();
	void BeginSplineMovement();
	UFUNCTION(BlueprintCallable) void SetCubeColor(ECubeColor ColorID, FLinearColor LinearColor);
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable) void SetWidgetVisible(bool bNewVisible);
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable) void UpdateWidgetInfo(ECubeColor Color);
protected:
	virtual void BeginPlay() override;
	void MoveAlongPath();
};
