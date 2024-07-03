// Fill out your copyright notice in the Description page of Project Settings.


#include "Time/TimeManager.h"

ATimeManager::ATimeManager()
{
	PrimaryActorTick.bCanEverTick = true;

	Time = 0;
	Second = 0; Minute = 0; Hour = 0; Day = 0;
}

void ATimeManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	DisplayTime();
}

void ATimeManager::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	if (TimeSpeed < 0.f) TimeSpeed = 0.f;
	Time += Day * 86400 + Hour * 3600 + Minute * 60 + Second;
	ChangeTime();
}

void ATimeManager::BeginPlay()
{
	Super::BeginPlay();
	GetWorldTimerManager().SetTimer(TimeHandle, this, &ThisClass::ChangeTime, GetTimerRate(), true);
}