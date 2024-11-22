// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ISelectable.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UISelectable : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class TOUTESTFAUX_API IISelectable
{
	GENERATED_BODY()
	public:
	
	
	virtual void Shrink(FVector cameraLocation);
	virtual void Increase();
	virtual void NewRotation(FRotator objectRotation);
	virtual void clicable();
	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
};
