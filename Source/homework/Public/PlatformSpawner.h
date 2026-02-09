#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PlatformSpawner.generated.h"

class ARotatingPlatform;
class AMovingPlatform;

UCLASS()
class HOMEWORK_API APlatformSpawner : public AActor
{
    GENERATED_BODY()

public:
    APlatformSpawner();

protected:
    virtual void BeginPlay() override;

public:
    UPROPERTY(EditAnywhere, Category = "Spawn")
    int32 RotatingPlatformCount = 5;

    UPROPERTY(EditAnywhere, Category = "Spawn")
    int32 MovingPlatformCount = 5;

    UPROPERTY(EditAnywhere, Category = "Spawn")
    TSubclassOf<ARotatingPlatform> RotatingPlatformClass;

    UPROPERTY(EditAnywhere, Category = "Spawn")
    TSubclassOf<AMovingPlatform> MovingPlatformClass;

    UPROPERTY(EditAnywhere, Category = "Spawn")
    FVector SpawnArea = FVector(2000, 2000, 0);
};
