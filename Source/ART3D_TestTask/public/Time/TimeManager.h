// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Misc/Timespan.h"
#include "TimeManager.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDayEndSignature, bool, bDayEnd);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTimeChangedSignature, float, Hour);

UCLASS()
class ART3D_TESTTASK_API ATimeManager : public AActor
{
	GENERATED_BODY()
	
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly) float Time;
	UPROPERTY(BlueprintAssignable)	FOnDayEndSignature OnDayEnd;
	UPROPERTY(BlueprintAssignable)	FOnTimeChangedSignature OnTimeChanged;
protected:
	UPROPERTY(EditAnywhere)	float TimeSpeed;

	UPROPERTY(EditAnywhere)	uint32 Day;
	UPROPERTY(EditAnywhere)	uint32 Hour;
	UPROPERTY(EditAnywhere)	uint32 Minute;
	UPROPERTY(EditAnywhere)	uint32 Second;

	FTimerHandle TimeHandle;
public:
	ATimeManager();
	virtual void Tick(float DeltaTime) override;
	UFUNCTION(BlueprintCallable, BlueprintPure) float GetHour() { return ((int32)Time % 86400) / 3600.f; }
	UFUNCTION(BlueprintCallable, BlueprintPure) float GetDay() { return (int32)Time % 86400; }
	UFUNCTION(BlueprintCallable, BlueprintPure) FTimespan GetTimespan() { return FTimespan::FromSeconds(Time); }
protected:
	virtual void OnConstruction(const FTransform& Transform) override;
	virtual void BeginPlay() override;

	void ChangeTime()
	{
		Time += TimeSpeed * GetTimerRate();
		if (GetTimespan().GetHours() == 19 && GetTimespan().GetMinutes() == 59)
			OnDayEnd.Broadcast(true);
		else if (GetTimespan().GetHours() == 5 && GetTimespan().GetMinutes() == 59)
			OnDayEnd.Broadcast(false);
		OnTimeChanged.Broadcast(GetHour());
		UpdateAll(Time);
	}

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable) void UpdateAll(float CurrHour);

	float GetTimerRate() { float Rate = 1.f / TimeSpeed; return Rate < 0.01f ? 0.01f : Rate; }

private:
	void DisplayTime()
	{
		GEngine->AddOnScreenDebugMessage(INDEX_NONE, 0.f, FColor::Cyan, *FString::Printf(
			TEXT("Day: %i  Hour: %i  Min: %i  Sec: %i"),
			GetTimespan().GetDays(),
			GetTimespan().GetHours(),
			GetTimespan().GetMinutes(),
			GetTimespan().GetSeconds()));
	}
};
