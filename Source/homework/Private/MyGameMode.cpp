#include "MyGameMode.h"
#include "UObject/ConstructorHelpers.h"
#include "GameFramework/Pawn.h"

AMyGameMode::AMyGameMode()
{
    static ConstructorHelpers::FClassFinder<APawn> PawnBP(
        TEXT("/Game/Blueprints/BP_MyThirdPersonPawn_New")
    );

    if (PawnBP.Class)
    {
        DefaultPawnClass = PawnBP.Class;
    }
}

//BeginPlay에 추가
void AMyGameMode::BeginPlay()
{
    Super::BeginPlay();

    if (DefaultPawnClass)
    {
        UE_LOG(LogTemp, Warning, TEXT("DefaultPawnClass: %s"), *DefaultPawnClass->GetName());
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("DefaultPawnClass is NULL!"));
    }
}
