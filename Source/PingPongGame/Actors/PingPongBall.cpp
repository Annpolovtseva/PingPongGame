#include "PingPongBall.h"

#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

APingPongBall::APingPongBall()
{
    StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
    RootComponent = StaticMeshComponent;

    ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
    ProjectileMovementComponent->SetUpdatedComponent(RootComponent);
    ProjectileMovementComponent->InitialSpeed = 2000.0f;
    ProjectileMovementComponent->MaxSpeed = 2000.0f;
    ProjectileMovementComponent->bRotationFollowsVelocity = true;
    ProjectileMovementComponent->bShouldBounce = true;
    ProjectileMovementComponent->Bounciness = 1.0f;
    ProjectileMovementComponent->ProjectileGravityScale = 0.0f;

    SetRemoteRoleForBackwardsCompat(ROLE_SimulatedProxy);
    PrimaryActorTick.bCanEverTick = true;
    PrimaryActorTick.TickGroup = TG_PrePhysics;
    bReplicates = true;
    SetReplicatingMovement(true);
}

void APingPongBall::SetDirection(const FVector& Direction)
{
    if (ProjectileMovementComponent)
    {
        ProjectileMovementComponent->Velocity = Direction * ProjectileMovementComponent->InitialSpeed;
    }
}