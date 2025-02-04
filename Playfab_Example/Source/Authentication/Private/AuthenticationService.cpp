#include "Authentication/Public/AuthenticationService.h"

UAuthenticationService* UAuthenticationService::SignIn(const FString& username)
{
	UAuthenticationService* AuthenticationService = NewObject<UAuthenticationService>();
	PlayFab::ClientModels::FLoginWithCustomIDRequest Request;
	Request.CreateAccount = true;
	Request.CustomId = username;

	PlayFab::UPlayFabClientAPI::FLoginWithCustomIDDelegate OnSuccess;
	OnSuccess.BindUObject(AuthenticationService, &UAuthenticationService::LoginSuccess);

	PlayFab::FPlayFabErrorDelegate OnError;
	OnError.BindUObject(AuthenticationService, &UAuthenticationService::LoginError);

	PlayFab::UPlayFabClientAPI().LoginWithCustomID(Request);
	
	return AuthenticationService;
}

void UAuthenticationService::LoginSuccess(const PlayFab::ClientModels::FLoginResult& Result)
{
	/*if (Result.NewlyCreated)
	{
		PlayFab::ClientModels::FUpdateUserTitleDisplayNameRequest Request;
		Request.DisplayName = Result.PlayFabId;
		PlayFab::UPlayFabClientAPI().UpdateUserTitleDisplayName(Request);
	}*/

	OnSuccess.Broadcast();
}

void UAuthenticationService::LoginError(const PlayFab::FPlayFabCppError& Result)
{
	OnFailure.Broadcast();
}