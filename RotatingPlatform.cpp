#include "RotatingPlatform.h"

ARotatingPlatform::ARotatingPlatform()
{
    PrimaryActorTick.bCanEverTick = true;

    Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
    RootComponent = Mesh;
}

void ARotatingPlatform::BeginPlay()
{
    Super::BeginPlay();
}

void ARotatingPlatform::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    //  매 프레임 RotationSpeed 사용 → Runtime 변경 즉시 반영
    AddActorLocalRotation(FRotator(0.f, RotationSpeed * DeltaTime, 0.f));
}
