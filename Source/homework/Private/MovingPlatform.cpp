#include "MovingPlatform.h"

AMovingPlatform::AMovingPlatform()
{
    PrimaryActorTick.bCanEverTick = true;

    Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
    RootComponent = Mesh;
}

void AMovingPlatform::BeginPlay()
{
    Super::BeginPlay();
    StartLocation = GetActorLocation();
}

void AMovingPlatform::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    FVector NewLocation = GetActorLocation() + MoveDirection * MoveSpeed * DeltaTime;

    if (FVector::Dist(StartLocation, NewLocation) > MaxRange)
    {
        MoveDirection *= -1;
    }

    SetActorLocation(NewLocation);
}
