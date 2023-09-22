#pragma once

#include "GameFramework/Actor.h"

#include "PingPongBall.generated.h"

class UStaticMeshComponent;
class UProjectileMovementComponent;

UCLASS(config = Game)
class PINGPONGGAME_API APingPongBall : public AActor
{
	GENERATED_BODY()

public:

	APingPongBall();

	void SetDirection(const FVector& Direction);

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* StaticMeshComponent;

	UPROPERTY(VisibleAnywhere, Category = Movement)
	UProjectileMovementComponent* ProjectileMovementComponent;
};