// Fill out your copyright notice in the Description page of Project Settings.


#include "SplineMovement/CubeManager.h"
#include "SplineMovement/Cube.h"

// Sets default values
ACubeManager::ACubeManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void ACubeManager::UpdateCubeColorByIndex(int32 Index, ECubeColor CubeColor, FLinearColor LinearColor)
{
	if (!CubesArray.IsValidIndex(Index)) return;
	CubesArray[Index]->SetCubeColor(CubeColor, LinearColor);
	CubesArray[Index]->UpdateWidgetInfo(CubeColor);
}

// Called when the game starts or when spawned
void ACubeManager::BeginPlay()
{
	Super::BeginPlay();
	
	if (!CubesClass) { UE_LOG(LogTemp, Error, TEXT("CubeClass is nullptr!")); return; }
	if (!CubesPath) { UE_LOG(LogTemp, Error, TEXT("CubesPath is nullptr!")); return; }

	for (int32 i = 0; i < CubesAmount; i++)	SpawnCube();
	OnCubesSpawned.Broadcast();

	GetWorldTimerManager().SetTimer(AppearCubesHandle, this, &ThisClass::ShowCube, 0.5f, true, 0.f);
}

void ACubeManager::SpawnCube()
{
	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	CubesArray.Add(GetWorld()->SpawnActor<ACube>(CubesClass, SpawnParams));
}

void ACubeManager::ShowCube()
{
	bool found = false;
	for (int32 i = 0; i < CubesAmount; i++)
	{
		if (CubesArray[i]->IsHidden())
		{
			CubesArray[i]->SetActorHiddenInGame(false);
			CubesArray[i]->Path = CubesPath;
			CubesArray[i]->BeginSplineMovement();
			found = true;
			break;
		}
	}

	if (!found)
	{
		GetWorldTimerManager().ClearTimer(AppearCubesHandle);
		AppearCubesHandle.Invalidate();
	}
}
