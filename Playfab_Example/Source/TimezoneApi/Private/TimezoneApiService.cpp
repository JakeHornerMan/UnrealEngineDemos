// Fill out your copyright notice in the Description page of Project Settings.


#include "TimezoneApiService.h"
#include "Kismet/KismetMathLibrary.h"

ATimezoneApiService::ATimezoneApiService() :
	City(ECity::EC_Tokyo),
	SecondCountFloat(1.f)
{
	// set default pawn class to our Blueprinted character
	/*static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;*/

	//Time API Http Requests
	Http = &FHttpModule::Get();
}

FText ATimezoneApiService::GetCurrentTime()
{
	FString Hours;
	FString Minutes;
	FString Seconds;

	if (Hour < 10) {
		Hours = FString("0").Append(FString::FromInt(Hour));
	}
	else {
		Hours = FString::FromInt(Hour);
	}

	if (Minute < 10) {
		Minutes = FString("0").Append(FString::FromInt(Minute));
	}
	else {
		Minutes = FString::FromInt(Minute);
	}

	if (Second < 10) {
		Seconds = FString("0").Append(FString::FromInt(Second));
	}
	else {
		Seconds = FString::FromInt(Second);
	}

	FString ReturnString = Hours.Append(FString(":")).Append(Minutes).Append(FString(":")).Append(Seconds);

	return FText::FromString(ReturnString);
}

void ATimezoneApiService::SetCurrentCity(ECity CurrentCity)
{
	City = CurrentCity;
	SendHTTPGet();
}

void ATimezoneApiService::BeginPlay()
{
	Super::BeginPlay();
	SendHTTPGet();

	GetWorldTimerManager().SetTimer(SecondCounter, this, &ATimezoneApiService::SecondCounterCallback, SecondCountFloat);
}

void ATimezoneApiService::SendHTTPGet()
{

	UE_LOG(LogTemp, Warning, TEXT("SendHTTPGet"));
	//Defines URL for each city
	SwitchOnCity();

	//created a request
	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request = Http->CreateRequest();

	//bind reponse funtion to request 
	Request->OnProcessRequestComplete().BindUObject(this, &ATimezoneApiService::OnGetTimeResponse);
	//Setting URL and HTTP method
	Request->SetURL(CityURL);
	Request->SetVerb("GET");
	//Defining headre with the request agent and the response/request data type
	Request->SetHeader("User-Agent", "X-UnrealEngine-Agent");
	Request->SetHeader("Content-Type", "application/json");
	//fulfilling the request by sending
	Request->ProcessRequest();
}

void ATimezoneApiService::OnGetTimeResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bConnectedSuccessfully)
{
	//Created teh Json Obj
	TSharedPtr<FJsonObject> JsonObject;
	//check if we are successful
	if (Response->GetResponseCode() == 200)
	{
		//store response body
		const FString ResponseBody = Response->GetContentAsString();
		//create a reader for the response body
		TSharedRef<TJsonReader<>>Reader = TJsonReaderFactory<>::Create(ResponseBody);
		//check if it was sucessful in reading the json
		if (FJsonSerializer::Deserialize(Reader, JsonObject))
		{
			UKismetMathLibrary::DateTimeFromIsoString(*JsonObject->GetStringField("dateTime"), Time);
			BreakTime();
		}
	}
}

void ATimezoneApiService::SwitchOnCity()
{
	CityURL = FString("https://timeapi.io/api/Time/current/zone?timeZone=");

	switch (City)
	{
	case ECity::EC_Tokyo:
		CityURL.Append("Asia/Tokyo");
		break;
	case ECity::EC_Dublin:
		CityURL.Append("Europe/London");
		break;
	case ECity::EC_NewYork:
		CityURL.Append("America/New_York");
		break;
	default:
		break;
	}
}

void ATimezoneApiService::BreakTime()
{
	int32 Year;
	int32 Month;
	int32 Day;
	int32 MiliSecond;

	//Break the Time Variable and store the data withing the individual Variables
	UKismetMathLibrary::BreakDateTime(Time, Year, Month, Day, Hour, Minute, Second, MiliSecond);
}

void ATimezoneApiService::SecondCounterCallback()
{
	UE_LOG(LogTemp, Warning, TEXT("SecondCounterCallback"));
	Time += FTimespan::FromSeconds(1);
	BreakTime();

	GetWorldTimerManager().SetTimer(SecondCounter, this, &ATimezoneApiService::SecondCounterCallback, SecondCountFloat);
}
