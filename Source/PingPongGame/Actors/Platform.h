#pragma once

#include "GameFramework/Pawn.h"

#include "Platform.generated.h"

UCLASS(config = Game)
class PINGPONGGAME_API APlatform : public APawn
{
	GENERATED_BODY()

public:

	APlatform();

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* StaticMeshComponent;

private:

};