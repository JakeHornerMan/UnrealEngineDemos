// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "PlayerCharacter.generated.h"

UCLASS()
class CPPPROJECT_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void SetupPlayerInput();

	UPROPERTY(EditAnywhere, Category = EnhancedInput)
	class UInputMappingContext* InputMapping;

	UPROPERTY(EditAnywhere)
	class UCameraComponent* Camera;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	//Move functionality START
	UPROPERTY(EditAnywhere, Category = EnhancedInput)
	class UInputAction* MoveAction;
	void Move(const FInputActionValue& InputValue);

	//Look functionality START
	UPROPERTY(EditAnywhere, Category = EnhancedInput)
	class UInputAction* LookAction;
	void Look(const FInputActionValue& InputValue);
	
	//Jump functionality START
	UPROPERTY(EditAnywhere, Category = EnhancedInput)
	class UInputAction* ChargeJumpAction;
	void ChargeJumpInput();

	float BaseJumpZVelocity;
	float JumpMultiplier;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float JumpMultiplierLimit;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float JumpMultiplierInput;

	UPROPERTY(EditAnywhere, Category = EnhancedInput)
	class UInputAction* JumpAction;
	void JumpInput();

};
