// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CubeColor.generated.h"

UENUM(BlueprintType)
enum class ECubeColor : uint8
{
	White = 0	UMETA(DisplayName = "White"),
	Black = 1	UMETA(DisplayName = "Black"),
	Red	  = 2	UMETA(DisplayName = "Red"),
	Green = 3	UMETA(DisplayName = "Green"),
	Blue  = 4	UMETA(DisplayName = "Blue"),
};
