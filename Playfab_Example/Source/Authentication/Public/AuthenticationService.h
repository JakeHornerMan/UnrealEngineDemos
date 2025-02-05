#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "UObject/Object.h"
#include "PlayFabClientAPI.h"
#include "AuthenticationService.generated.h"


UCLASS(Blueprintable)
class AUTHENTICATION_API UAuthenticationService : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FAuthenticationResponse);
	UPROPERTY(BlueprintAssignable)
	FAuthenticationResponse OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FAuthenticationResponse OnFailure;


	UFUNCTION(BlueprintCallable, meta=(BlueprintInternalUseOnly = "false", WorldContext="WorldContextObject"), Category = "Authentication")
	static UAuthenticationService* SignIn(UObject* WorldContextObject, const FString& Username);

private:
	UObject* _worldContextObject;
	void LoginSuccess(const PlayFab::ClientModels::FLoginResult& Result);
	void LoginError(const PlayFab::FPlayFabCppError& Result);
};
