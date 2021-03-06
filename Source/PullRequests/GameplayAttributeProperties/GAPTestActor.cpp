// Copyright 2017 Dr. Matthias Hölzl

#include "PullRequests.h"
#include "GAPTestActor.h"
#include "Engine/DataTable.h"
#include "AbilitySystemComponent.h"
#include "GAPTestAttributeSet.h"

AGAPTestActor::AGAPTestActor()
{
	static ConstructorHelpers::FObjectFinder<UDataTable> DataTableFinder{ TEXT("DataTable'/Game/Data/DT_GameplayAttributeProperties.DT_GameplayAttributeProperties'") };
	if (DataTableFinder.Succeeded())
	{
		PropertyDataTable = DataTableFinder.Object;
	}

	TestAttributeSet = CreateDefaultSubobject<UGAPTestAttributeSet>("TestAttributeSet");
	if (PropertyDataTable)
	{
		UE_LOG(LogPullRequest, Log, TEXT("Initializing TestAttributeSet from data table."));
		TestAttributeSet->InitFromMetaDataTable(PropertyDataTable);
	}

	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>("AbilitySystemComponent");
}

void AGAPTestActor::BeginPlay()
{
	Super::BeginPlay();

	if (TestAttributeSet)
	{
		UE_LOG(LogPullRequest, Log, TEXT("Checking attribute values..."));

		ensureAlways(TestAttributeSet->MyFloatProperty == 1.f);

		FGameplayAttributeData AttributeData{ TestAttributeSet->MyGameplayAttributeDataProperty };
		ensureAlways(AttributeData.GetBaseValue() == 2.f);

		UE_LOG(LogPullRequest, Log, TEXT("Done."));

	}
	else
	{
		UE_LOG(LogPullRequest, Warning, TEXT("TestAttributeSet not initialized."));
	}

	
	UE_LOG(LogPullRequest, Log, TEXT("Checking GetAllAttributes..."));

	AbilitySystemComponent->AddSet<UGAPTestAttributeSet>();

	TArray<FGameplayAttribute> AllAttributes;
	AbilitySystemComponent->GetAllAttributes(AllAttributes);

	ensureAlways(AllAttributes.Num() == 2);

	UE_LOG(LogPullRequest, Log, TEXT("Done."));
}
