// Copyright Epic Games, Inc. All Rights Reserved.

#include "Playfab_ExamplePickUpComponent.h"

UPlayfab_ExamplePickUpComponent::UPlayfab_ExamplePickUpComponent()
{
	// Setup the Sphere Collision
	SphereRadius = 32.f;
}

void UPlayfab_ExamplePickUpComponent::BeginPlay()
{
	Super::BeginPlay();

	// Register our Overlap Event
	OnComponentBeginOverlap.AddDynamic(this, &UPlayfab_ExamplePickUpComponent::OnSphereBeginOverlap);
}

void UPlayfab_ExamplePickUpComponent::OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// Checking if it is a First Person Character overlapping
	APlayfab_ExampleCharacter* Character = Cast<APlayfab_ExampleCharacter>(OtherActor);
	if(Character != nullptr)
	{
		// Notify that the actor is being picked up
		OnPickUp.Broadcast(Character);

		// Unregister from the Overlap Event so it is no longer triggered
		OnComponentBeginOverlap.RemoveAll(this);
	}
}
