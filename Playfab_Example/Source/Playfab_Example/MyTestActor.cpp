// Fill out your copyright notice in the Description page of Project Settings.


#include "MyTestActor.h"
#include <Kismet/GameplayStatics.h>

// Sets default values
AMyTestActor::AMyTestActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	ReadWriteValue = 100;
	TransientReadOnlyValue = 101;
}

// Called when the game starts or when spawned
void AMyTestActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyTestActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

int32 AMyTestActor::TestFunction()
{
	int32 answer = ReadWriteValue * TransientReadOnlyValue;
	OnTestFunctionEvent();
	OnTestFunctionEventVariablePass(answer);
	OnTestFunctionEventCodeCall();

	return answer;
}

void AMyTestActor::OnTestFunctionEventCodeCall_Implementation()
{
	//Printing a string
	GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Emerald, TEXT("OnTestFunctionEventCodeCall_Implementation"));
}

void AMyTestActor::CastingTestFunction()
{
	AMyTestActor* testActor = Cast<AMyTestActor>(this);
	if (testActor != nullptr) {
		GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Blue, TEXT("CastingTestFunction, This is a AMyTestActor class"));
		testActor->TestFunction();
	}
	else {
		GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, TEXT("CastingTestFunction, This is not a AMyTestActor class"));
	}
}

