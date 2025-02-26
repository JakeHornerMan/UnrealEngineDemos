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

void ArrayOperations()
{
    // Define a TArray
    TArray<int32> Numbers = { 1, 2, 3, 4, 5 };

    // Add a new element
    Numbers.Add(6);

    // Remove an element (removing value 3)
    Numbers.Remove(3);

    // Print all elements using UE_LOG
    UE_LOG(LogTemp, Warning, TEXT("Array Elements:"));
    for (int32 Num : Numbers)
    {
        UE_LOG(LogTemp, Warning, TEXT("%d"), Num);
    }

    // Find an element (example: check if 4 exists)
    if (Numbers.Contains(4))
    {
        UE_LOG(LogTemp, Warning, TEXT("Number 4 is in the array."));
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Number 4 not found."));
    }
}

void MapOperations()
{
    // Define a TMap (Key: int32, Value: FString)
    TMap<int32, FString> PlayerScores;

    // Add key-value pairs
    PlayerScores.Add(1, TEXT("Alice"));
    PlayerScores.Add(2, TEXT("Bob"));
    PlayerScores.Add(3, TEXT("Charlie"));

    // Modify a value (Change Bob's name)
    PlayerScores[2] = TEXT("Bobby");

    // Remove an element (Remove Charlie)
    PlayerScores.Remove(3);

    // Print all key-value pairs
    UE_LOG(LogTemp, Warning, TEXT("Player Scores:"));
    for (const TPair<int32, FString>& Pair : PlayerScores)
    {
        UE_LOG(LogTemp, Warning, TEXT("ID: %d, Name: %s"), Pair.Key, *Pair.Value);
    }

    // Check if a key exists (Check if player with ID 2 exists)
    if (PlayerScores.Contains(2))
    {
        UE_LOG(LogTemp, Warning, TEXT("Player with ID 2 exists: %s"), *PlayerScores[2]);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Player with ID 2 not found."));
    }
}

//void ListOperationsWithPlayerScore()
//{
//    // Define a TDoubleLinkedList to store FPlayerScore
//    TDoubleLinkedList<FPlayerScore> PlayerList;
//
//    // Add players to the list
//    PlayerList.AddTail(FPlayerScore(TEXT("Alice"), 100));
//    PlayerList.AddTail(FPlayerScore(TEXT("Bob"), 150));
//    PlayerList.AddTail(FPlayerScore(TEXT("Charlie"), 200));
//
//    // Print all players in the list
//    UE_LOG(LogTemp, Warning, TEXT("Player List:"));
//    for (TDoubleLinkedList<FPlayerScore>::TIterator It(PlayerList.GetHead()); It; ++It)
//    {
//        UE_LOG(LogTemp, Warning, TEXT("Player: %s, Score: %d"), *It->PlayerName, It->PlayerScore);
//    }
//
//    // Remove a player (e.g., remove Bob)
//    for (TDoubleLinkedList<FPlayerScore>::TIterator It(PlayerList.GetHead()); It; ++It)
//    {
//        if (It->PlayerName == TEXT("Bob"))
//        {
//            PlayerList.RemoveNode(It.GetNode());
//            break; // Break after removing to avoid iterator invalidation
//        }
//    }
//
//    // Print updated player list
//    UE_LOG(LogTemp, Warning, TEXT("Updated Player List:"));
//    for (TDoubleLinkedList<FPlayerScore>::TIterator It(PlayerList.GetHead()); It; ++It)
//    {
//        UE_LOG(LogTemp, Warning, TEXT("Player: %s, Score: %d"), *It->PlayerName, It->PlayerScore);
//    }
//}

