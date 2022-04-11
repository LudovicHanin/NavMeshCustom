#include "MeshGenerator.h"

#pragma region UnrealMethods
UMeshGenerator::UMeshGenerator()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UMeshGenerator::BeginPlay()
{
	Super::BeginPlay();
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
	const uint8 _index = mVertices.Num();
	const FVector _offset = FVector(0, 0, 50.0f);
	mVertices.Add(_vertex1 + _offset);
	mVertices.Add(_vertex2 + _offset);
	mVertices.Add(_vertex3 + _offset);

	mTriangles.Add(_index);
	mTriangles.Add(_index + 1);
	mTriangles.Add(_index + 2);
}

/**
 * @brief Display mMesh
 */
void UMeshGenerator::DisplayMesh()
{
	TArray<FVector2d> _uvs = TArray<FVector2d>();

	mMesh->CreateMeshSection_LinearColor(0, mVertices, mTriangles, TArray<FVector>(), _uvs, TArray<FLinearColor>(),
	                                     TArray<FProcMeshTangent>(), true);
}

void UMeshGenerator::Init(const TArray<FHitResult>& _array, const uint8& _nbPerLine)
{
	TArray<FVector> _loc = TArray<FVector>();
	for(uint8 i = 0; i < _array.Num(); i++)
		_loc.Add(_array[i].Location);
	
	CreateMesh(_loc, 0, _nbPerLine);
}

/**
 * @brief Create recursively the Mesh of the NavMesh
 * @param _hitLocation Array that contains all location of the point touch by the RayCast/LineTrace
 * @param _index Current Index in the Array HitLocation
 * @param _nbPerLine Number of point per line
 */
void UMeshGenerator::CreateMesh(const TArray<FVector> _hitLocation, const uint8 _index, const uint8 _nbPerLine)
{
	UE_LOG(LogTemp, Warning, TEXT("UMeshGenerator::CreateMesh => Enter"));
	if (!_hitLocation.IsValidIndex(_index + 1))
	{
		mOnMeshInfoCreate.Broadcast();
		return;
	}


	if (_index % (_nbPerLine - 1) == 0) CreateMesh(_hitLocation, _index + 1, _nbPerLine);

	//Create Top Left Triangle
	CreateTriangle(_hitLocation[_index], _hitLocation[_index + 1], _hitLocation[_index + _nbPerLine]);

	if (!_hitLocation.IsValidIndex(_index + _nbPerLine + 1)) return;

	//Create Bottom Right Triangle
	CreateTriangle(_hitLocation[_index + _nbPerLine + 1], _hitLocation[_index + _nbPerLine], _hitLocation[_index + 1]);

	CreateMesh(_hitLocation, _index + 1, _nbPerLine);
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
