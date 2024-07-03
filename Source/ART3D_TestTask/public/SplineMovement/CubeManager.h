// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Color/CubeColor.h"
#include "CubeManager.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCubesSpawnedSignature);

UCLASS()
class ART3D_TESTTASK_API ACubeManager : public AActor
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintAssignable) FOnCubesSpawnedSignature OnCubesSpawned;
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Cubes|Path") class APath* CubesPath;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Cubes") int32 CubesAmount;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Cubes") UClass* CubesClass;
	
	UPROPERTY(BlueprintReadOnly) TArray<class ACube*> CubesArray;
	FTimerHandle AppearCubesHandle;
public:	
	// Sets default values for this actor's properties
	ACubeManager();
	UFUNCTION(BlueprintCallable) void UpdateCubeColorByIndex(int32 Index, ECubeColor CubeColor, FLinearColor LinearColor);
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void SpawnCube();
	void ShowCube();
};
