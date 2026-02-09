#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RotatingPlatform.generated.h"

UCLASS()
class HOMEWORK_API ARotatingPlatform : public AActor
{
    GENERATED_BODY()

public:
    ARotatingPlatform();

    virtual void Tick(float DeltaTime) override;

protected:
    virtual void BeginPlay() override;

public:
    UPROPERTY(VisibleAnywhere)
    UStaticMeshComponent* Mesh;

    // 👉 Reflection 핵심
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Platform Settings")
    float RotationSpeed = 90.f;
};
