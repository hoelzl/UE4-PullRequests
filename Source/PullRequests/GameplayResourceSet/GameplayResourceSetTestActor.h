// Copyright 2017 Dr. Matthais Hölzl

#pragma once

#include "ObjectMacros.h"
#include "GameplayTask.h"
#include "GameplayTaskResource.h"
#include "GameFramework/Actor.h"
#include "GameplayResourceSetTestActor.generated.h"


UCLASS()
class UGTR1 : public UGameplayTaskResource
{
	GENERATED_BODY()
public:
};

UCLASS()
class UGTR2 : public UGameplayTaskResource
{
	GENERATED_BODY()
public:
};
UCLASS()
class UGTR3 : public UGameplayTaskResource
{
	GENERATED_BODY()
public:
};



UCLASS()
class PULLREQUESTS_API AGameplayResourceSetTestActor : public AActor
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override
	{
		Super::BeginPlay();

		uint8 ID1{ UGameplayTaskResource::GetResourceID<UGTR1>() };
		uint8 ID2{ UGameplayTaskResource::GetResourceID<UGTR2>() };
		uint8 ID3{ UGameplayTaskResource::GetResourceID<UGTR3>() };

		RS1.AddID(ID1);
		RS2.AddID(ID2);
		RS3.AddID(ID3);
		RS12.AddID(ID1).AddID(ID2);
		RS13.AddID(ID1).AddID(ID3);
		RS23.AddID(ID2).AddID(ID3);
		RS123.AddID(ID1).AddID(ID2).AddID(ID3);

		UE_LOG(LogPullRequest, Log, TEXT("Starting tests..."));

		ensureAlways(FGameplayResourceSet::AllResources().HasAllIDs(FGameplayResourceSet::NoResources()));
		ensureAlways(FGameplayResourceSet::AllResources().HasAllIDs(RS123));
		ensureAlways(FGameplayResourceSet::AllResources().HasAllIDs(FGameplayResourceSet::AllResources()));

		ensureAlways(FGameplayResourceSet::NoResources().HasAllIDs(FGameplayResourceSet::NoResources()));
		ensureAlways(!FGameplayResourceSet::NoResources().HasAllIDs(RS123));
		ensureAlways(!FGameplayResourceSet::NoResources().HasAllIDs(FGameplayResourceSet::AllResources()));

		ensureAlways(RS12.HasAllIDs(RS1));
		ensureAlways(RS12.HasAllIDs(RS2));
		ensureAlways(RS12.HasAllIDs(RS12));

		ensureAlways(!RS12.HasAllIDs(RS3));
		ensureAlways(!RS12.HasAllIDs(RS13));
		ensureAlways(!RS12.HasAllIDs(RS23));
		ensureAlways(!RS12.HasAllIDs(RS123));

		ensureAlways(RS13.HasAllIDs(RS1));
		ensureAlways(RS13.HasAllIDs(RS3));
		ensureAlways(RS13.HasAllIDs(RS13));

		ensureAlways(RS23.HasAllIDs(RS2));
		ensureAlways(RS23.HasAllIDs(RS3));
		ensureAlways(RS23.HasAllIDs(RS23));

		ensureAlways(RS123.HasAllIDs(RS1));
		ensureAlways(RS123.HasAllIDs(RS2));
		ensureAlways(RS123.HasAllIDs(RS3));
		ensureAlways(RS123.HasAllIDs(RS12));
		ensureAlways(RS123.HasAllIDs(RS13));
		ensureAlways(RS123.HasAllIDs(RS23));
		ensureAlways(RS123.HasAllIDs(RS123));

		UE_LOG(LogPullRequest, Log, TEXT("Done."));

	}

	FGameplayResourceSet RS1;
	FGameplayResourceSet RS2;
	FGameplayResourceSet RS3;
	FGameplayResourceSet RS12;
	FGameplayResourceSet RS13;
	FGameplayResourceSet RS23;
	FGameplayResourceSet RS123;
};

/*
Expected result:

LogPullRequest: Starting tests...
LogPullRequest: Done.


Result with current engine:

LogPullRequest: Starting tests...
LogOutputDevice:Error: Ensure condition failed: FGameplayResourceSet::AllResources().HasAllIDs(FGameplayResourceSet::NoResources()) [File:d:\unreal\projects\tests\pullrequestsbinary\source\pullrequests\gameplayresourceset\GameplayResourceSetTestActor.h] [Line: 58]
LogStats:             FDebug::EnsureFailed -  0.000 s
LogOutputDevice:Error: Ensure condition failed: FGameplayResourceSet::AllResources().HasAllIDs(RS123) [File:d:\unreal\projects\tests\pullrequestsbinary\source\pullrequests\gameplayresourceset\GameplayResourceSetTestActor.h] [Line: 59]
LogStats:             FDebug::EnsureFailed -  0.000 s
LogOutputDevice:Error: Ensure condition failed: !FGameplayResourceSet::NoResources().HasAllIDs(RS123) [File:d:\unreal\projects\tests\pullrequestsbinary\source\pullrequests\gameplayresourceset\GameplayResourceSetTestActor.h] [Line: 63]
LogStats:             FDebug::EnsureFailed -  0.000 s
LogOutputDevice:Error: Ensure condition failed: !FGameplayResourceSet::NoResources().HasAllIDs(FGameplayResourceSet::AllResources()) [File:d:\unreal\projects\tests\pullrequestsbinary\source\pullrequests\gameplayresourceset\GameplayResourceSetTestActor.h] [Line: 64]
LogStats:             FDebug::EnsureFailed -  0.000 s
LogOutputDevice:Error: Ensure condition failed: RS12.HasAllIDs(RS1) [File:d:\unreal\projects\tests\pullrequestsbinary\source\pullrequests\gameplayresourceset\GameplayResourceSetTestActor.h] [Line: 66]
LogStats:             FDebug::EnsureFailed -  0.000 s
LogOutputDevice:Error: Ensure condition failed: RS12.HasAllIDs(RS2) [File:d:\unreal\projects\tests\pullrequestsbinary\source\pullrequests\gameplayresourceset\GameplayResourceSetTestActor.h] [Line: 67]
LogStats:             FDebug::EnsureFailed -  0.000 s
LogOutputDevice:Error: Ensure condition failed: !RS12.HasAllIDs(RS123) [File:d:\unreal\projects\tests\pullrequestsbinary\source\pullrequests\gameplayresourceset\GameplayResourceSetTestActor.h] [Line: 73]
LogStats:             FDebug::EnsureFailed -  0.000 s
LogOutputDevice:Error: Ensure condition failed: RS13.HasAllIDs(RS1) [File:d:\unreal\projects\tests\pullrequestsbinary\source\pullrequests\gameplayresourceset\GameplayResourceSetTestActor.h] [Line: 75]
LogStats:             FDebug::EnsureFailed -  0.002 s
LogOutputDevice:Error: Ensure condition failed: RS13.HasAllIDs(RS3) [File:d:\unreal\projects\tests\pullrequestsbinary\source\pullrequests\gameplayresourceset\GameplayResourceSetTestActor.h] [Line: 76]
LogStats:             FDebug::EnsureFailed -  0.001 s
LogOutputDevice:Error: Ensure condition failed: RS23.HasAllIDs(RS2) [File:d:\unreal\projects\tests\pullrequestsbinary\source\pullrequests\gameplayresourceset\GameplayResourceSetTestActor.h] [Line: 79]
LogStats:             FDebug::EnsureFailed -  0.002 s
LogOutputDevice:Error: Ensure condition failed: RS23.HasAllIDs(RS3) [File:d:\unreal\projects\tests\pullrequestsbinary\source\pullrequests\gameplayresourceset\GameplayResourceSetTestActor.h] [Line: 80]
LogStats:             FDebug::EnsureFailed -  0.002 s
LogOutputDevice:Error: Ensure condition failed: RS123.HasAllIDs(RS1) [File:d:\unreal\projects\tests\pullrequestsbinary\source\pullrequests\gameplayresourceset\GameplayResourceSetTestActor.h] [Line: 83]
LogStats:             FDebug::EnsureFailed -  0.002 s
LogOutputDevice:Error: Ensure condition failed: RS123.HasAllIDs(RS2) [File:d:\unreal\projects\tests\pullrequestsbinary\source\pullrequests\gameplayresourceset\GameplayResourceSetTestActor.h] [Line: 84]
LogStats:             FDebug::EnsureFailed -  0.002 s
LogOutputDevice:Error: Ensure condition failed: RS123.HasAllIDs(RS3) [File:d:\unreal\projects\tests\pullrequestsbinary\source\pullrequests\gameplayresourceset\GameplayResourceSetTestActor.h] [Line: 85]
LogStats:             FDebug::EnsureFailed -  0.001 s
LogOutputDevice:Error: Ensure condition failed: RS123.HasAllIDs(RS12) [File:d:\unreal\projects\tests\pullrequestsbinary\source\pullrequests\gameplayresourceset\GameplayResourceSetTestActor.h] [Line: 86]
LogStats:             FDebug::EnsureFailed -  0.000 s
LogOutputDevice:Error: Ensure condition failed: RS123.HasAllIDs(RS13) [File:d:\unreal\projects\tests\pullrequestsbinary\source\pullrequests\gameplayresourceset\GameplayResourceSetTestActor.h] [Line: 87]
LogStats:             FDebug::EnsureFailed -  0.001 s
LogOutputDevice:Error: Ensure condition failed: RS123.HasAllIDs(RS23) [File:d:\unreal\projects\tests\pullrequestsbinary\source\pullrequests\gameplayresourceset\GameplayResourceSetTestActor.h] [Line: 88]
LogStats:             FDebug::EnsureFailed -  0.001 s
LogPullRequest: Done.
*/