// Copyright 2017 Dr. Matthias Hölzl

#pragma once

#include "GameFramework/Actor.h"
#include "GAPTestActor.generated.h"

class UAbilitySystemComponent;
class UGAPTestAttributeSet;

UCLASS()
class PULLREQUESTS_API AGAPTestActor : public AActor
{
	GENERATED_BODY()
	
public:	
	AGAPTestActor();

protected:
	virtual void BeginPlay() override;

	UPROPERTY()
	UDataTable* PropertyDataTable;

	UPROPERTY()
	UGAPTestAttributeSet* TestAttributeSet;

	UPROPERTY()
	UAbilitySystemComponent* AbilitySystemComponent;
};
