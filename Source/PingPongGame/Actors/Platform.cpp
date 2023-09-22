#include "Platform.h"

#include "Components/StaticMeshComponent.h"

APlatform::APlatform()
{
    StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
    RootComponent = StaticMeshComponent;
}
