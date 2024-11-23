// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Teletubbies.generated.h"

enum class ETeletubbies : uint8;
// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UTeletubbies : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class TOUTESTFAUX_API ITeletubbies
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	virtual ETeletubbies GetTeletubbiesType();
	virtual bool GetIfFigurineIsInRightPose();
};
