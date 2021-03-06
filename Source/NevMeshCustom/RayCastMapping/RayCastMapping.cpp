#include "RayCastMapping.h"
#include "DrawDebugHelpers.h"
#include "NevMeshCustom/NevMeshCustomCharacter.h"
#include "NevMeshCustom/Utils/Debug/Debug.h"

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
		// StartRayCast();
	});

	// mOnRayCastFinish.BindLambda([this] (TArray<FHitResult> _results)
	// {
	// 	//UE_LOG(LogTemp, Warning, TEXT("RayCast Finish"));
	// });
	
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
	mNumberPerLine = (int)FMath::Sqrt<float>(mNumberOfRayCast);
	const float _distanceLine = (((mLaunchPoint.X + mRadiusX) - mLaunchPoint.X) * 2) / (mNumberPerLine - 1);
	const float _distanceColone = (((mLaunchPoint.Y + mRadiusY) - mLaunchPoint.Y) * 2) / (mNumberPerLine - 1);

	TArray<FVector> _rayCastLocations = TArray<FVector>();

	for (size_t c = 0; c < mNumberPerLine; c++)
	{
		for (size_t l = 0; l < mNumberPerLine; l++)
		{
			const FVector _launchPoint = FVector(mLaunchPoint.X - mRadiusX + (_distanceLine * l),
			                                     mLaunchPoint.Y - mRadiusY + (_distanceColone * c), mLaunchPoint.Z);
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
	for (size_t i = 0; i < mAllRayCastPosition.Num(); i++)
	{
		UDebug::LogWarning(FString::FromInt(i));
		TArray<FHitResult> _tmp = TArray<FHitResult>();
		const FVector _location = mAllRayCastPosition[i];
		mWorld->LineTraceMultiByChannel(_tmp, _location, _location - FVector(0, 0, mRadiusZ), mCollisionChannel);
		_results += _tmp;
	}
	mAllHitResults = _results;
	UE_LOG(LogTemp, Warning, TEXT("URayCastMapping::LaunchRayCast => Call mOnRayCastFinish"));
	bool _value = mOnRayCastFinish.ExecuteIfBound(_results);
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
	for (size_t i = 0; i < mAllRayCastPosition.Num(); i++)
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
	LaunchRayCast();
}
#pragma endregion
#pragma endregion
