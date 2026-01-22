#include "MyThirdPersonPawn.h"

#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

AMyThirdPersonPawn::AMyThirdPersonPawn()
{
	PrimaryActorTick.bCanEverTick = false;

	/* Capsule (Root) */
	Capsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule"));
	SetRootComponent(Capsule);
	Capsule->SetSimulatePhysics(false);

	Capsule->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	Capsule->SetCollisionObjectType(ECC_Pawn);
	Capsule->SetCollisionResponseToAllChannels(ECR_Block);


	/* Mesh */
	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Capsule);
	Mesh->SetSimulatePhysics(false);

	/* SpringArm */
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(Capsule);
	SpringArm->TargetArmLength = 300.f;
	SpringArm->bUsePawnControlRotation = false;

	/* Camera */
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);

	AutoPossessPlayer = EAutoReceiveInput::Player0;
}

void AMyThirdPersonPawn::BeginPlay()
{
	Super::BeginPlay();

	// Enhanced Input IMC 등록
	if (APlayerController* PC = Cast<APlayerController>(GetController()))
	{
		if (ULocalPlayer* LP = PC->GetLocalPlayer())
		{
			if (UEnhancedInputLocalPlayerSubsystem* Subsystem =
				LP->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
			{
				Subsystem->AddMappingContext(DefaultIMC, 0);
			}
		}

		
		PC->bShowMouseCursor = false;
		PC->SetInputMode(FInputModeGameOnly());
	}
}


void AMyThirdPersonPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	if (UEnhancedInputComponent* EIC = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EIC->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AMyThirdPersonPawn::Move);
		EIC->BindAction(LookAction, ETriggerEvent::Triggered, this, &AMyThirdPersonPawn::Look);
	}
}

void AMyThirdPersonPawn::Move(const FInputActionValue& Value)
{
	const FVector2D Input = Value.Get<FVector2D>();
	const float DeltaTime = GetWorld()->GetDeltaSeconds();

	const FVector Forward = GetActorForwardVector();
	const FVector Right = GetActorRightVector();

	FVector MoveDirection =
		(Forward * Input.Y + Right * Input.X) * MoveSpeed * DeltaTime;

	FHitResult Hit;
	AddActorWorldOffset(MoveDirection, true, &Hit);

	if (Hit.bBlockingHit)
	{
		UE_LOG(LogTemp, Warning, TEXT("Hit Actor: %s"), *Hit.GetActor()->GetName());
	}
}



void AMyThirdPersonPawn::Look(const FInputActionValue& Value)
{
	const FVector2D Input = Value.Get<FVector2D>();
	const float DeltaTime = GetWorld()->GetDeltaSeconds();

	// ===== Pawn Yaw 회전 (좌우) =====
	AddActorLocalRotation(
		FRotator(0.f, Input.X * TurnSpeed * DeltaTime, 0.f)
	);

	// ===== SpringArm Pitch 회전 (상하) =====
	FRotator ArmRot = SpringArm->GetRelativeRotation();
	ArmRot.Pitch = FMath::Clamp(
		ArmRot.Pitch + Input.Y * LookSpeed * DeltaTime,
		-80.f,
		20.f
	);
	SpringArm->SetRelativeRotation(ArmRot);
}


