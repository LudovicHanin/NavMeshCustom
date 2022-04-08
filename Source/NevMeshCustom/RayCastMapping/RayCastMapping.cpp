#include "RayCastMapping.h"
#include "DrawDebugHelpers.h"
#include "NevMeshCustom/NevMeshCustomCharacter.h"

#pragma region UnrealMethods
URayCastMapping::URayCastMapping()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void URayCastMapping::BeginPlay()
{
	Super::BeginPlay();
	RegisterEvent();
	Init();
}

void URayCastMapping::BeginDestroy()
{
	Super::BeginDestroy();
}

void URayCastMapping::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	DrawVisualDebug();
}
#pragma endregion

#pragma region CustomMethods
#pragma region Private
/**
 * @brief Init variable and calculate launch location of all RayCast/LineTrace
 */
void URayCastMapping::Init()
{
	mWorld = GetWorld();
	CalculateLaunchLocation();
}

/**
 * @brief Add all methode to corresponding event
 */
void URayCastMapping::RegisterEvent()
{
	mOnLaunchPointCalculate.AddLambda([this](TArray<FVector> _locs)
	{
		mIsLaunchPointCalculated = true;
		StartRayCast();
	});
}

/**
 * @brief Calculate Launch location of all RayCast/LineTrace and stock them in mAllRayCastPosition
 */
void URayCastMapping::CalculateLaunchLocation()
{
	mAllRayCastPosition.Empty();

	if (mNumberOfRayCast % 100 != 0)
	{
		mNumberOfRayCast -= mNumberOfRayCast % 100;
		UE_LOG(LogTemp, Warning, TEXT("Number of raycast : %d"), mNumberOfRayCast);
	}
	const int _numberPerLine = mNumberOfRayCast / 10;
	const float _distanceLine = (((mLaunchPoint.X + mRadiusX) - mLaunchPoint.X) * 2) / (_numberPerLine - 1);
	const float _distanceColone = (((mLaunchPoint.Y + mRadiusY) - mLaunchPoint.Y) * 2) / (_numberPerLine - 1);

	TArray<FVector> _rayCastLocations = TArray<FVector>();

	for (uint8 c = 0; c < _numberPerLine; c++)
	{
		for (uint8 l = 0; l < _numberPerLine; l++)
		{
			//TODO Calculate launch location
			const FVector _launchPoint = FVector(mLaunchPoint.X - mRadiusX + (_distanceLine * l),
			                                     mLaunchPoint.Y - mRadiusY + (_distanceColone * c), mLaunchPoint.Z);
			//TODO Add location found in mAllRayCastPosition
			_rayCastLocations.Add(_launchPoint);
		}
	}
	mAllRayCastPosition = _rayCastLocations;
	mOnLaunchPointCalculate.Broadcast(_rayCastLocations);
}

/**
 * @brief If all RayCast Launch Location as been calculated Launch RayCast/LineTrace
 */
void URayCastMapping::LaunchRayCast()
{
	UE_LOG(LogTemp, Warning, TEXT("Launch RayCast"));
	if (!mIsLaunchPointCalculated) return;
	mOnLaunchRayCast.Broadcast();
	TArray<FHitResult> _results = TArray<FHitResult>();
	for (uint8 i = 0; i < mAllRayCastPosition.Num(); i++)
	{
		TArray<FHitResult> _tmp = TArray<FHitResult>();
		const FVector _location = mAllRayCastPosition[i];
		//TODO Launch LineTrace from mAllRayCastPosition[index] location
		mWorld->LineTraceMultiByChannel(_tmp, _location, _location - FVector(0, 0, mRadiusZ), mCollisionChannel);
		//TODO Add FHitResult to mAllHitResults
		_results += _tmp;
	}
	mAllHitResults = _results;
	mOnRayCastFinish.Broadcast(_results);
}

#pragma region Debug
/**
 * @brief Call all Debug Methods
 */
void URayCastMapping::DrawVisualDebug() const
{
	if (!mDisplayDebug)return;
	if (mDisplayRadius)DrawRadiusDebug();
	if (mDisplayRayCastPoint)DrawRayCastPosition();
}

/**
 * @brief Draw a Debug Box of the Radius of spawn of the RayCast/LineTrace
 */
void URayCastMapping::DrawRadiusDebug() const
{
	if (!mWorld)return;
	DrawDebugBox(mWorld, mLaunchPoint, FVector(mRadiusX, mRadiusY, mRadiusZ), FColor::Emerald);
}

/**
 * @brief Draw a Sphere at each launch position of RayCast/LineTrace
 */
void URayCastMapping::DrawRayCastPosition() const
{
	if (!mWorld)return;
	for (uint8 i = 0; i < mAllRayCastPosition.Num(); i++)
	{
		const FVector _location = mAllRayCastPosition[i];
		DrawDebugSphere(mWorld, _location, 5.0f, 32, FColor::Red);
	}
}
#pragma endregion

#pragma endregion

#pragma region Public

/**
 * @brief Start launching LineTrace from the top to the bottom to map and construct the NavMesh
 */
void URayCastMapping::StartRayCast()
{
	//TODO LaunchRayCast();
	LaunchRayCast();
}
#pragma endregion
#pragma endregion
