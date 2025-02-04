// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Interfaces/IHttpResponse.h"
#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include <HttpModule.h>
#include "TimezoneApiService.generated.h"

/**
 * 
 */
UENUM(BlueprintType)
enum class ECity :uint8 {
	EC_Tokyo	UMETA(DisplayName = "Tokyo"),
	EC_Dublin	UMETA(DisplayName = "Dublin"),
	EC_NewYork	UMETA(DisplayName = "New York"),
	EC_Default	UMETA(DisplayName = "Default")
};

UCLASS()
class TIMEZONEAPI_API ATimezoneApiService : public AGameModeBase
{
	GENERATED_BODY()

public:
	ATimezoneApiService();

	UFUNCTION(BlueprintCallable)
	FText GetCurrentTime();

	UFUNCTION(BlueprintCallable)
	void SetCurrentCity(ECity CurrentCity);

protected:
	//Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//Used to send the Http request
	UFUNCTION()
	void SendHTTPGet();

	//Handle the HttpRequest Response
	void OnGetTimeResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bConnectedSuccessfully);

	void SwitchOnCity();

	void BreakTime();

	void SecondCounterCallback();



private:
	FHttpModule* Http;

	ECity City;

	FString CityURL;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Time, meta = (AllowPrivateAccess = "true"))
	FDateTime Time;

	int32 Hour;
	int32 Minute;
	int32 Second;

	FTimerHandle SecondCounter;
	float SecondCountFloat;
	
};
