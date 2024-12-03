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
	
	
	virtual void Shrink();
	virtual void Grabed(UStaticMeshComponent* mesh);
	virtual void Release(FVector newpos);
	virtual void SetFrontCamera(FVector camera);
	virtual void SetInTheHand();
	virtual void Increase();
	virtual void NewRotation(FRotator objectRotation);
	virtual void Clikcable();
	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
};
