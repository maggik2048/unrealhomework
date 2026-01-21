#include "PlatformSpawner.h"
#include "homework/RotatingPlatform.h"
#include "MovingPlatform.h"

APlatformSpawner::APlatformSpawner()
{
    PrimaryActorTick.bCanEverTick = false;
}

void APlatformSpawner::BeginPlay()
{
    Super::BeginPlay();

    UE_LOG(LogTemp, Warning, TEXT("Spawner BeginPlay called"));

    if (!GetWorld()) return;

    for (int32 i = 0; i < RotatingPlatformCount; i++)
    {
        FVector Location = GetActorLocation() +
            FVector(
                FMath::RandRange(-SpawnArea.X, SpawnArea.X),
                FMath::RandRange(-SpawnArea.Y, SpawnArea.Y),
                0
            );

        auto* Platform = GetWorld()->SpawnActor<ARotatingPlatform>(
            RotatingPlatformClass,
            Location,
            FRotator::ZeroRotator
        );

        if (Platform)
        {
            Platform->RotationSpeed = FMath::RandRange(30.f, 180.f);
        }
    }

    for (int32 i = 0; i < MovingPlatformCount; i++)
    {
        FVector Location = GetActorLocation() +
            FVector(
                FMath::RandRange(-SpawnArea.X, SpawnArea.X),
                FMath::RandRange(-SpawnArea.Y, SpawnArea.Y),
                0
            );

        auto* Platform = GetWorld()->SpawnActor<AMovingPlatform>(
            MovingPlatformClass,
            Location,
            FRotator::ZeroRotator
        );

        if (Platform)
        {
            Platform->MoveSpeed = FMath::RandRange(100.f, 400.f);
            Platform->MaxRange = FMath::RandRange(300.f, 800.f);
        }
    }
}
