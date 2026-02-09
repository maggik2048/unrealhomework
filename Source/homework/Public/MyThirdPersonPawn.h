#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "InputActionValue.h"
#include "MyThirdPersonPawn.generated.h"

class UCapsuleComponent;
class USkeletalMeshComponent;
class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;

UCLASS()
class HOMEWORK_API AMyThirdPersonPawn : public APawn
{
	GENERATED_BODY()

public:
	AMyThirdPersonPawn();

protected:
	virtual void BeginPlay() override;
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	/* ===== Input ===== */
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputMappingContext* DefaultIMC;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* MoveAction;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* LookAction;

	/* ===== Components ===== */
	UPROPERTY(VisibleAnywhere)
	UCapsuleComponent* Capsule;

	UPROPERTY(VisibleAnywhere)
	USkeletalMeshComponent* Mesh;

	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere)
	UCameraComponent* Camera;

	/* ===== Movement ===== */
	UPROPERTY(EditAnywhere, Category = "Movement")
	float MoveSpeed = 500.f;

	UPROPERTY(EditAnywhere, Category = "Movement")
	float TurnSpeed = 90.f;

	UPROPERTY(EditAnywhere, Category = "Movement")
	float LookSpeed = 90.f;

	/* ===== Input Callbacks ===== */
	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
};
