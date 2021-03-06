// Copyright 2017 Dr. Matthias Hölzl

#pragma once

#include "AttributeSet.h"
#include "GAPTestAttributeSet.generated.h"

/**
 * An attribute set that contains a float attribute and a FGameplayAttributeData attribute to test the new implementation
 */
UCLASS()
class PULLREQUESTS_API UGAPTestAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
	
public:
	UPROPERTY()
	float MyFloatProperty;

	UPROPERTY()
	FGameplayAttributeData MyGameplayAttributeDataProperty;
};
