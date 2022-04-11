#include "MeshActor.h"

#include "MyMeshInfo.h"

// Sets default values
AMeshActor::AMeshActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	
	mMesh = CreateDefaultSubobject<UProceduralMeshComponent>(TEXT("Mesh"));
}

// Called when the game starts or when spawned
void AMeshActor::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AMeshActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

/**
 * @brief Create a mesh
 * @param _vertices 
 * @param _triangles 
 * @param _uvs 
 */
void AMeshActor::InitMesh(const TArray<FVector>& _vertices, const TArray<int32>& _triangles,
                          const TArray<FVector2d> _uvs)
{
	if (!mMesh)
	{
		UE_LOG(LogTemp, Error, TEXT("AMeshActor::InitMesh => No mesh"));
		return;
	}
	mMesh->CreateMeshSection_LinearColor(0, _vertices, _triangles, TArray<FVector>(), _uvs, TArray<FLinearColor>(),
	                                     TArray<FProcMeshTangent>(), false);
}

/**
 * @brief Create a mesh
 * @param _meshInfo Info of the mesh
 */
void AMeshActor::InitMesh(const FMyMeshInfo& _meshInfo)
{
	UE_LOG(LogTemp, Log, TEXT("AMeshActor::InitMesh => Enter"));
	
	if (!mMesh)
	{
		UE_LOG(LogTemp, Error, TEXT("AMeshActor::InitMesh => No Mesh"));
		return;
	}
	mMesh->CreateMeshSection_LinearColor(0, _meshInfo.GetVertices(), _meshInfo.GetTriangles(), TArray<FVector>(),
	                                     _meshInfo.GetUVS(), TArray<FLinearColor>(), TArray<FProcMeshTangent>(), false);
}
