// Fill out your copyright notice in the Description page of Project Settings.


#include "MyProject/Player/PlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "PaperFlipbookComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

APlayerCharacter::APlayerCharacter() 
{
	springArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	springArm->SetupAttachment(RootComponent);

	camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Player Camera"));
	camera->SetupAttachment(springArm);
}

void APlayerCharacter::BeginPlay() 
{
	Super::BeginPlay();

	spriteComponent = this->GetSprite();
	flipbookIdle = spriteComponent->GetFlipbook();
}

void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	APlayerCharacter::ControlAnimation();
	APlayerCharacter::RotateAnimation();
}

void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAxis("MoveX", this, &APlayerCharacter::MoveX);
	PlayerInputComponent->BindAxis("MoveY", this, &APlayerCharacter::MoveY);
}

void APlayerCharacter::MoveX(float inputValue)
{
	FVector yDirection = GetActorForwardVector();
	AddMovementInput(yDirection, inputValue);
}

void APlayerCharacter::MoveY(float inputValue)
{
	FVector xDirection = GetActorRightVector();
	AddMovementInput(xDirection, inputValue);
}

void APlayerCharacter::ControlAnimation()
{
	if (GetCharacterMovement()->IsFalling())
	{
		spriteComponent->SetFlipbook(flipbookJump);
	}
	else if (APlayerCharacter::GetVelocity().Length() > 0)
	{
		spriteComponent->SetFlipbook(flipbookRun);
	}
	else
	{
		spriteComponent->SetFlipbook(flipbookIdle);
	}
}

void APlayerCharacter::RotateAnimation()
{
	if (APlayerCharacter::GetVelocity().X > 0)
	{
		spriteComponent->SetRelativeRotation(FRotator(0, 0, 0));
	}
	else if (APlayerCharacter::GetVelocity().X < 0)
	{
		spriteComponent->SetRelativeRotation(FRotator(0, 180, 0));
	}
}
