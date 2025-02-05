// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "AuthenticationSessionData.generated.h"

/**
 * 
 */
UCLASS()
class AUTHENTICATION_API UAuthenticationSessionData : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
public:
	FString GetPlayFabID()
	{
		return _playFabId;
	}

	void SetPlayFabID(const FString& PlayFabID)
	{
		_playFabId = PlayFabID;
	}

	FString GetUsername()
	{
		return _username;
	}

	void SetUsername(const FString& Username)
	{
		_username = Username;
	}

private:
	FString _playFabId;
	FString _username;
};
