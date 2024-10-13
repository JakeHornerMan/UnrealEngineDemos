// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MovingPlatform.generated.h"

UCLASS()
class OBSTACLEASSAULT_API AMovingPlatform : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMovingPlatform();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere) int32 integer = 0;
	UPROPERTY(EditAnywhere) bool isMoving = true;
	UPROPERTY(EditAnywhere) float speed = 5.11;

	UPROPERTY(EditAnywhere) FVector vector3 = FVector(4,7,6); //Its a Vector3()
	UPROPERTY(EditAnywhere) float x;
	UPROPERTY(EditAnywhere) float y;
	UPROPERTY(EditAnywhere) float z;

};
