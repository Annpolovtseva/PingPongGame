#pragma once

#include "GameFramework/PlayerController.h"

#include "PlatformController.generated.h"

class APlatform;

UCLASS(config = Game)
class PINGPONGGAME_API APlatformController : public APlayerController
{
    GENERATED_BODY()

public:

    virtual void BeginPlay() override;
    virtual void SetupInputComponent() override;
    virtual void Tick(float DeltaTime) override;
    virtual void AutoManageActiveCameraTarget(AActor* SuggestedTarget) override;

    void SetTeamNumber(int32 InTeamNumber);
    int32 GetTeamNumber() const;

    UFUNCTION(BlueprintCallable)
    bool IsWaitingForPlayer() const;
    void SetWaitingForPlayer(bool bWaiting);

    UFUNCTION(BlueprintImplementableEvent)
    void UpdateWaitingForPlayer();

private:

    UFUNCTION()
    void OnRep_TeamNumber();
    UFUNCTION()
    void OnRep_WaitingForPlayer();

    UFUNCTION(Server, reliable)
    void OnMove(float Input);

    void OnRightMove(float Input);

    float LastMoveInput = 0.0f;

    float CurrentDirection = 0.0f;

    UPROPERTY(EditAnywhere)
    float Speed = 30.0f;

    UPROPERTY(EditAnywhere)
    float YMin = -800.0f;

    UPROPERTY(EditAnywhere)
    float YMax = 800.0f;

    UPROPERTY(Transient, ReplicatedUsing = OnRep_TeamNumber)
    int32 TeamNumber = -1;

    UPROPERTY(Transient, ReplicatedUsing = OnRep_WaitingForPlayer)
    bool bWaitingForPlayer = false;
};