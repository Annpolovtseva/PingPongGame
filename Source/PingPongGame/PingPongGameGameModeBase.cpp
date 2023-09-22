#include "PingPongGameGameModeBase.h"

#include "Actors/Platform.h"
#include "Actors/PlatformController.h"
#include "Actors/PingPongBall.h"
#include "Actors/PingPongGameState.h"

#include "Components/CapsuleComponent.h"
#include "GameFramework/PlayerStart.h"
#include "Camera/CameraActor.h"
#include "Engine/TriggerBox.h"
#include "EngineUtils.h"

void APingPongGameGameModeBase::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
    NextPlayerTeamNumber = 0;
    Controllers.Empty();
    if (APingPongGameState* PingPongGameState = GetGameState<APingPongGameState>())
    {
        PingPongGameState->ResetScore();
    }

    Super::InitGame(MapName, Options, ErrorMessage);

    for (TActorIterator<ATeamSideDataActor> It(GetWorld()); It; ++It)
    {
        TeamSideDataActor = *It;
    }
}

void APingPongGameGameModeBase::BeginPlay()
{
    Super::BeginPlay();

    if (TeamSideDataActor != nullptr)
    {
        for (const FTeamData& TeamData : TeamSideDataActor->TeamData)
        {
            if (TeamData.Goal != nullptr)
            {
                TeamData.Goal->GetCollisionComponent()->OnComponentBeginOverlap.AddDynamic(this, &APingPongGameGameModeBase::OnOverlapBegin);
            }
        }
    }
}

void APingPongGameGameModeBase::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    int32 PlayerMissGoal = 0;

    AActor* Actor = OverlappedComp->GetOwner();
    if (TeamSideDataActor)
    {
        for (int32 Index = 0; Index < TeamSideDataActor->TeamData.Num(); Index++)
        {
            if (TeamSideDataActor->TeamData[Index].Goal == Actor)
            {
                PlayerMissGoal = Index;
                break;
            }
        }

        if (Ball && TeamSideDataActor->StartBallLocationActor)
        {
            Ball->Destroy();
            SpawnBall();
        }
    }

    if (APingPongGameState* PingPongGameState = GetGameState<APingPongGameState>())
    {
        if (PlayerMissGoal == 0)
        {
            PingPongGameState->Player1Scored();
        }
        else if (PlayerMissGoal == 1)
        {
            PingPongGameState->Player0Scored();
        }
    }
}

void APingPongGameGameModeBase::PostLogin(APlayerController* NewPlayer)
{
    APlatformController* PlatformController = CastChecked<APlatformController>(NewPlayer);
    PlatformController->SetTeamNumber(NextPlayerTeamNumber);

    if (NextPlayerTeamNumber == 0)
    {
        PlatformController->SetWaitingForPlayer(true);
    }
    Controllers.Add(PlatformController);

    NextPlayerTeamNumber++;

    Super::PostLogin(NewPlayer);

    if (NextPlayerTeamNumber == 2)
    {
        if (Controllers.Num() != 0)
        {
            Controllers[0]->SetWaitingForPlayer(false);
        }

        SpawnBall();
    }
}

void APingPongGameGameModeBase::SpawnBall()
{
    if (BallClass && TeamSideDataActor && TeamSideDataActor->StartBallLocationActor)
    {
        FActorSpawnParameters SpawnInfo;
        SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
        SpawnInfo.bNoFail = true;

        AActor* StartBallLocationActor = TeamSideDataActor->StartBallLocationActor;

        FTransform Transform;
        Transform.SetLocation(StartBallLocationActor->GetActorLocation());
        Ball = GetWorld()->SpawnActor<APingPongBall>(BallClass, Transform, SpawnInfo);

        Ball->SetDirection(StartBallLocationActor->GetActorRotation().Vector());
    }
}

AActor* APingPongGameGameModeBase::ChoosePlayerStart_Implementation(AController* Player)
{
    if (TeamSideDataActor && TeamSideDataActor->TeamData.IsValidIndex(NextPlayerTeamNumber))
    {
        return TeamSideDataActor->TeamData[NextPlayerTeamNumber].PlayerStart;
    }

    return nullptr;
}