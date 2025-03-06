#include "CppProject/Player/PlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "InputMappingContext.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/CharacterMovementComponent.h"


// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Player Camera"));
	Camera->SetupAttachment(RootComponent);
	Camera->bUsePawnControlRotation = true;

	BaseJumpZVelocity = 500.0f;
	JumpMultiplier = 0.0f;
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	SetupPlayerInput();
}

void APlayerCharacter::SetupPlayerInput()
{
	//Add mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem
			= ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			//Add input Context
			Subsystem->AddMappingContext(InputMapping, 0);
		}
	}
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	SetupPlayerInput();

	//PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);

	if (UEnhancedInputComponent* Input = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		Input->BindAction(MoveAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Move);
		Input->BindAction(LookAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Look);
		Input->BindAction(JumpAction, ETriggerEvent::Triggered, this, &APlayerCharacter::JumpInput);
		Input->BindAction(ChargeJumpAction, ETriggerEvent::Triggered, this, &APlayerCharacter::ChargeJumpInput);
	}
}

void APlayerCharacter::Move(const FInputActionValue& InputValue)
{
	FVector2D InputVector = InputValue.Get<FVector2D>();
	if (IsValid(Controller))
	{
		//Get foreward direction
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector ForewardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		//Add movements input
		AddMovementInput(ForewardDirection, InputVector.Y);
		AddMovementInput(RightDirection, InputVector.X);
	}
}

void APlayerCharacter::Look(const FInputActionValue& InputValue)
{
	FVector2D InputVector = InputValue.Get<FVector2D>();

	if (IsValid(Controller))
	{
		AddControllerYawInput(InputVector.X);
		AddControllerPitchInput(InputVector.Y);
	}
}

void APlayerCharacter::ChargeJumpInput()
{
	JumpMultiplier = FMath::Clamp(JumpMultiplier + JumpMultiplierInput, 0.0f, JumpMultiplierLimit);
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Blue, "Pressed Charge Jump Input Action, Multi: " + FString::SanitizeFloat(JumpMultiplier));
}

void APlayerCharacter::JumpInput()
{
	if (GetCharacterMovement())
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Blue, "Released Jump Input Action, Multi: " + FString::SanitizeFloat(JumpMultiplier));
		GetCharacterMovement()->JumpZVelocity = BaseJumpZVelocity + JumpMultiplier;
		Jump();
		JumpMultiplier = 0.f;
	}
}

