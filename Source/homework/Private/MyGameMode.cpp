#include "MyGameMode.h"
#include "UObject/ConstructorHelpers.h"
#include "GameFramework/Pawn.h"

AMyGameMode::AMyGameMode()
{
	static ConstructorHelpers::FClassFinder<APawn> PawnBP(
		TEXT("/Game/BP_MyThirdPersonPawn")
	);

	if (PawnBP.Class)
	{
		DefaultPawnClass = PawnBP.Class;
	}
}
