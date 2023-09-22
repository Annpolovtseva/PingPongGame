#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "PingPongGameState.generated.h"

UCLASS()
class PINGPONGGAME_API APingPongGameState : public AGameStateBase
{
	GENERATED_BODY()

public:

	void ResetScore();

	UFUNCTION(BlueprintImplementableEvent)
	void UpdateScore();

	void Player0Scored();
	void Player1Scored();

	UFUNCTION(BlueprintCallable)
	int32 GetPlayer0Score() const;
	UFUNCTION(BlueprintCallable)
	int32 GetPlayer1Score() const;

protected:

	UFUNCTION()
	void OnRep_ScorePlayer0();
	UFUNCTION()
	void OnRep_ScorePlayer1();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, ReplicatedUsing = OnRep_ScorePlayer0)
	int32 ScorePlayer0 = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, ReplicatedUsing = OnRep_ScorePlayer1)
	int32 ScorePlayer1 = 0;
};
