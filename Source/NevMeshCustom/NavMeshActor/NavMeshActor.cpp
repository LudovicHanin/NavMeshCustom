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
		// TArray<FVector> _loc = TArray<FVector>();
		// for(uint8 i = 0; i < _array.Num(); i++)
		// 	_loc.Add(_array[i].Location);
		// _meshG->CreateMesh(_loc, 0, mRayCastMapping->GetNumberPerLine());
		
	});
	
	mRayCastMapping->StartRayCast();

}
