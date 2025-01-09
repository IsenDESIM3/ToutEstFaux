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
	virtual void Grabbed(UStaticMeshComponent* mesh);
	virtual void Release(FVector newpos, FRotator newrot);
	virtual void SetFrontCamera(FVector vector);
	virtual void SetInTheHand();
	virtual void Increase();
	virtual void NewRotation(FRotator objectRotation);
	virtual void Clickable();
	virtual AActor* GetActor();
	virtual AActor* GetItemTarget();
	virtual FVector GetReleasePos();
	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
};
