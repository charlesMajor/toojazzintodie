// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperCharacter.h"
#include "PlayerCharacter.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT_API APlayerCharacter : public APaperCharacter
{
	GENERATED_BODY()
	
public:

	APlayerCharacter();

protected:

	virtual void BeginPlay() override;

public:

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:

	UPROPERTY(EditAnywhere)
	class UCameraComponent* camera;

	UPROPERTY(EditAnywhere)
	class USpringArmComponent* springArm;

	UPROPERTY(EditAnywhere)
	class UPaperFlipbookComponent* spriteComponent;

	class UPaperFlipbook* flipbookIdle;

	UPROPERTY(EditAnywhere, Category = "Flipbooks")
	class UPaperFlipbook* flipbookJump;

	UPROPERTY(EditAnywhere, Category = "Flipbooks")
	class UPaperFlipbook* flipbookRun;


	void MoveX(float inputValue);
	void MoveY(float inputValue);

	void ControlAnimation();
	void RotateAnimation();
};
