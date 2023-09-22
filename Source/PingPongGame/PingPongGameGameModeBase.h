#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "PingPongGameGameModeBase.generated.h"

class APlatform;
class ATriggerBox;
class APlayerStart;
class APingPongBall;
class APlatformController;

USTRUCT(BlueprintType, Blueprintable)
struct FTeamData
{
	GENERATED_BODY()

		UPROPERTY(EditAnywhere)
		ACameraActor* Camera;
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		ATriggerBox* Goal;
	UPROPERTY(EditAnywhere)
		APlayerStart* PlayerStart;
};

UCLASS(config = Game)
class PINGPONGGAME_API ATeamSideDataActor : public AActor
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		TArray<FTeamData> TeamData;

	UPROPERTY(EditAnywhere)
		AActor* StartBallLocationActor;
};

UCLASS(config = Game)
class PINGPONGGAME_API APingPongGameGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:

	virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override;
	virtual void BeginPlay() override;
	virtual void PostLogin(APlayerController* NewPlayer) override;

	virtual AActor* ChoosePlayerStart_Implementation(AController* Player) override;
	UFUNCTION()
	virtual void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

protected:

	void SpawnBall();

	UPROPERTY(Transient, BlueprintReadOnly)
	ATeamSideDataActor* TeamSideDataActor;

private:

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<APingPongBall> BallClass;

	UPROPERTY(Transient)
	APingPongBall* Ball;

	UPROPERTY(Transient)
	TArray<APlatformController*> Controllers;

	int32 NextPlayerTeamNumber = 0;
};
