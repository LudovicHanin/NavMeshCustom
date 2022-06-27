#include "MeshGenerator.h"

#include "NevMeshCustom/Utils/Debug/Debug.h"


#pragma region UnrealMethods
UMeshGenerator::UMeshGenerator()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UMeshGenerator::BeginPlay()
{
	Super::BeginPlay();
	RegisterEvent();
}

void UMeshGenerator::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}
#pragma  endregion

#pragma region CustomMethods
#pragma region Private

/**
 * @brief Add all methode to corresponding event
 */
void UMeshGenerator::RegisterEvent()
{
	mOnMeshInfoCreate.AddLambda([this]
	{
		DisplayMesh();
	});
}

/**
 * @brief Make an array the will contains all vertex given
 * @param _vertex1 Location of the first vertices
 * @param _vertex2 Location of the second vertices
 * @param _vertex3 Location of the third vertices
 * @return An Array that contains the three vertex
 */
void UMeshGenerator::CreateTriangle(const FVector& _vertex1, const FVector& _vertex2,
                                    const FVector& _vertex3)
{
	const FVector _offset = FVector(0, 0, 50.0f);

	TArray<FVector> _vertices = TArray<FVector>();
	_vertices.Add(_vertex1 + _offset);
	_vertices.Add(_vertex2 + _offset);
	_vertices.Add(_vertex3 + _offset);

	TArray<int32> _triangles = TArray<int32>();
	_triangles.Add(0);
	_triangles.Add(1);
	_triangles.Add(2);

	const FMyMeshInfo _meshInfo = FMyMeshInfo(_vertices, _triangles);
	mMeshInfos.Add(_meshInfo);
}

/**
 * @brief Display mMesh
 */
void UMeshGenerator::DisplayMesh()
{
	mAllMeshActor.Empty();
	UDebug::LogWarning("Enter");
	UWorld* _world = GetWorld();
	if (!_world)
	{
		UE_LOG(LogTemp, Error, TEXT("UMeshGenerator::DisplayMesh => No world"));
		return;
	}

	if (!mMeshActor)
	{
		UE_LOG(LogTemp, Error, TEXT("UMeshGenerator::DisplayMesh => No ref MeshActor"));
		return;
	}
	UDebug::Log(FString("Number of Mesh info " + FString::FromInt(mMeshInfos.Num())));
	for (size_t i = 0; i < mMeshInfos.Num(); i++)
	{
		UDebug::Log(FString("Spawn"));
		AMeshActor* _meshActor = _world->SpawnActor<AMeshActor>(mMeshActor, mMeshInfos[i].GetVertices()[0],
		                                                        FRotator::ZeroRotator);
		if (!_meshActor)
		{
			UDebug::LogError("UMeshGenerator::DisplayMesh => Can't create MeshActor");
			return;
		}
		_meshActor->InitMesh(mMeshInfos[i]);
		mAllMeshActor.Add(_meshActor);
	}

	// mMesh->CreateMeshSection_LinearColor(0, mVertices, mTriangles, TArray<FVector>(), _uvs, TArray<FLinearColor>(),
	//                                      TArray<FProcMeshTangent>(), true);
}

/**
 * @brief Create an Array of FVector from an Array of FHitResult and Call CreateMesh methods
 * @param _array Array of the Result of the RayCast
 * @param _nbPerLine Number of RayCast per line
 */
void UMeshGenerator::Init(const TArray<FHitResult>& _array, const int& _nbPerLine)
{
	TArray<FVector> _loc = TArray<FVector>();
	for (size_t i = 0; i < _array.Num(); i++)
		_loc.Add(_array[i].Location);

	CreateMesh(_loc, 0, _nbPerLine);
}

/**
 * @brief Create recursively the Mesh of the NavMesh
 * @param _hitLocation Array that contains all location of the point touch by the RayCast/LineTrace
 * @param _index Current Index in the Array HitLocation
 * @param _nbPerLine Number of point per line
 */
void UMeshGenerator::CreateMesh(const TArray<FVector> _hitLocation, const int _index, const int _nbPerLine)
{
	UDebug::LogError(FString::FromInt(_index));

	if (!_hitLocation.IsValidIndex(_index + 1))
	{
		UE_LOG(LogTemp, Warning, TEXT("UMeshGenerator::CreateMesh => Enter"));
		mOnMeshInfoCreate.Broadcast();
		return;
	}


	if (_index % (_nbPerLine - 1) == 0)
	{
		CreateMesh(_hitLocation, _index + 1, _nbPerLine);
		return;
	}

	//Create Top Left Triangle
	if (_hitLocation.IsValidIndex(_index + _nbPerLine))
		CreateTriangle(_hitLocation[_index], _hitLocation[_index + 1],
		               _hitLocation[_index + _nbPerLine]);

	//Create Bottom Right Triangle
	if (_hitLocation.IsValidIndex(_index + _nbPerLine + 1))
		CreateTriangle(_hitLocation[_index + _nbPerLine + 1], _hitLocation[_index + _nbPerLine],
		               _hitLocation[_index + 1]);

	return CreateMesh(_hitLocation, _index + 1, _nbPerLine);
}

/**
 * @brief Make an array the will contains the UV
 * @param _uvX X value of the UV
 * @param _uvY Y value of the UV
 * @return An Array of UV
 */
TArray<FVector2d> UMeshGenerator::CreateUV(const float& _uvX, const float& _uvY)
{
	TArray<FVector2d> _uvs = TArray<FVector2d>();
	_uvs.Add(FVector2d(_uvX, _uvY));
	return _uvs;
}
#pragma endregion

#pragma region Public
#pragma endregion
#pragma endregion
