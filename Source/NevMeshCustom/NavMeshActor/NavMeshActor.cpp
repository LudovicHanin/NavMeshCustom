#include "NavMeshActor.h"

ANavMeshActor::ANavMeshActor()
{
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>("RootComponent");
	
	mRayCastMapping = CreateDefaultSubobject<URayCastMapping>(TEXT("RayCastMapping"));
	AddOwnedComponent(mRayCastMapping);

	mMeshGenerator = CreateDefaultSubobject<UMeshGenerator>(TEXT("MeshGenerator"));
	AddOwnedComponent(mMeshGenerator);
}

void ANavMeshActor::BeginPlay()
{
	Super::BeginPlay();
	
	StartRayCast();
}

void ANavMeshActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ANavMeshActor::StartRayCast()
{
	if(!mRayCastMapping)return;
	
	UE_LOG(LogTemp, Warning, TEXT("ANavMeshActor::StartRayCast => Before verif"));
	
	if(!mMeshGenerator)return;
	
	UE_LOG(LogTemp, Warning, TEXT("ANavMeshActor::StartRayCast => After verif"));
	
	UMeshGenerator* _meshG = mMeshGenerator;
	mRayCastMapping->GetOnRayCastFinish().BindLambda([this, _meshG](const TArray<FHitResult>& _array)
	{
		UE_LOG(LogTemp, Warning, TEXT("ANavMeshActor::StartRayCast => Event Call"));

		_meshG->Init(_array, mRayCastMapping->GetNumberPerLine());
	});
	
	mRayCastMapping->StartRayCast();

}
