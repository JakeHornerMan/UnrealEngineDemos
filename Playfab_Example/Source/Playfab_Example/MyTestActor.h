// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyTestActor.generated.h"

UCLASS()
class PLAYFAB_EXAMPLE_API AMyTestActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMyTestActor();

	//Accessable anywhere
	//Read & Write variable 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="TestValues") 
	int32 ReadWriteValue;

	//Read Only variable 
	//Transient - that cannot be changes in BP Class
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Transient, Category = "TestValues")
	int32 TransientReadOnlyValue;

	//Basic Function
	UFUNCTION(BlueprintCallable, Category = "TestFunctions")
	int32 TestFunction();

	//Event funtion called in blue prints
	UFUNCTION(BlueprintImplementableEvent, Category = "TestFunctions")
	void OnTestFunctionEvent();

	//Event function with a input
	UFUNCTION(BlueprintImplementableEvent, Category = "TestFunctions")
	void OnTestFunctionEventVariablePass(int32 Value);

	//event function that ca n be called in code also. BlueprintNativeEvent
	UFUNCTION(BlueprintNativeEvent, Category = "TestFunctions")
	void OnTestFunctionEventCodeCall();

	UFUNCTION(BlueprintCallable, Category = "TestFunctions")
	void CastingTestFunction();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};


USTRUCT(BlueprintType)
struct FPlayerScore
{
	// Player Name
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player")
	FString PlayerName;

	// Player Score
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player")
	int32 PlayerScore;

	// Constructor
	FPlayerScore()
		: PlayerName(TEXT("Unknown")), PlayerScore(0) {
	}

	FPlayerScore(FString Name, int32 Score)
		: PlayerName(Name), PlayerScore(Score) {
	}
};