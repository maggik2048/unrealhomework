#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MovingPlatform.generated.h"

UCLASS()
class HOMEWORK_API AMovingPlatform : public AActor
{
    GENERATED_BODY()

public:
    AMovingPlatform();

    virtual void Tick(float DeltaTime) override;

protected:
    virtual void BeginPlay() override;

private:
    FVector StartLocation;
    FVector MoveDirection = FVector(1, 0, 0);

public:
    UPROPERTY(VisibleAnywhere)
    UStaticMeshComponent* Mesh;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Platform Settings")
    float MoveSpeed = 200.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Platform Settings")
    float MaxRange = 500.f;
};
