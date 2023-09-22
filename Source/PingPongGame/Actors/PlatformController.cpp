#include "PlatformController.h"

#include "PingPongGame/Actors/Platform.h"
#include "PingPongGame/PingPongGameGameModeBase.h"

#include "Camera/CameraActor.h"
#include "Net/UnrealNetwork.h"

#include "EngineUtils.h"

void APlatformController::BeginPlay()
{
    Super::BeginPlay();
}

void APlatformController::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME(APlatformController, TeamNumber);
    DOREPLIFETIME(APlatformController, bWaitingForPlayer);
}

void APlatformController::SetupInputComponent()
{
    Super::SetupInputComponent();

    InputComponent->BindAxis("OnMove", this, &APlatformController::OnRightMove);
}

void APlatformController::OnRightMove(float Input)
{
    if (LastMoveInput != Input)
    {
        OnMove(Input);
        LastMoveInput = Input;
    }
}

void APlatformController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (HasAuthority())
    {
        APawn* Platform = GetPawn();
        if (Platform != nullptr)
        {
            FVector RightVector = Platform->GetActorRightVector();
            RightVector.Normalize();
            FVector CurrentLocation = Platform->GetActorLocation();
            FVector NewLocation = CurrentLocation + RightVector * Speed * CurrentDirection;
            NewLocation.Y = FMath::Clamp(NewLocation.Y, YMin, YMax);
            Platform->SetActorLocation(NewLocation);
        }
    }
}

void APlatformController::AutoManageActiveCameraTarget(AActor* SuggestedTarget)
{
    ATeamSideDataActor* TeamSideData = nullptr;
    for (TActorIterator<ATeamSideDataActor> It(GetWorld()); It; ++It)
    {
        TeamSideData = *It;
    }

    if (TeamSideData && TeamSideData->TeamData.IsValidIndex(TeamNumber) && TeamSideData->TeamData[TeamNumber].Camera)
    {
        SetViewTarget(TeamSideData->TeamData[TeamNumber].Camera);
    }
    else
    {
        Super::AutoManageActiveCameraTarget(SuggestedTarget);
    }
}

void APlatformController::OnMove_Implementation(float Input)
{
    CurrentDirection = Input;
}

void APlatformController::OnRep_TeamNumber()
{

}

void APlatformController::OnRep_WaitingForPlayer()
{
    UpdateWaitingForPlayer();
}

void APlatformController::SetTeamNumber(int32 InTeamNumber)
{
    TeamNumber = InTeamNumber;
}

int32 APlatformController::GetTeamNumber() const
{
    return TeamNumber;
}

bool APlatformController::IsWaitingForPlayer() const
{
    return bWaitingForPlayer;
}

void APlatformController::SetWaitingForPlayer(bool bWaiting)
{
    bWaitingForPlayer = bWaiting;
}