#include "NavMeshActor.h"

ANavMeshActor::ANavMeshActor()
{
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>("RootComponent");
	
	mRayCastMapping = CreateDefaultSubobject<URayCastMapping>(TEXT("RayCastMapping"));
	AddOwnedComponent(mRayCastMapping);
}

void ANavMeshActor::BeginPlay()
{
	Super::BeginPlay();
	
}

void ANavMeshActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ANavMeshActor::StartRayCast()
{
	if(!mRayCastMapping)return;
	mRayCastMapping->StartRayCast();
}

