#include "PingPongGameState.h"

#include "Net/UnrealNetwork.h"

void APingPongGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME(APingPongGameState, ScorePlayer0);
    DOREPLIFETIME(APingPongGameState, ScorePlayer1);
}

void APingPongGameState::ResetScore()
{
    ScorePlayer0 = 0;
    ScorePlayer1 = 0;
}

void APingPongGameState::Player0Scored()
{
    ScorePlayer0++;
}

void APingPongGameState::Player1Scored()
{
    ScorePlayer1++;
}

int32 APingPongGameState::GetPlayer0Score() const
{
    return ScorePlayer0;
}

int32 APingPongGameState::GetPlayer1Score() const
{
    return ScorePlayer1;
}

void APingPongGameState::OnRep_ScorePlayer0()
{
    UpdateScore();
}

void APingPongGameState::OnRep_ScorePlayer1()
{
    UpdateScore();
}