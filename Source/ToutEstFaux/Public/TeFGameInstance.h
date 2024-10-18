// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "TeFGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class TOUTESTFAUX_API UTeFGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UTeFGameInstance();

protected:
	virtual void Init() override;
	
};
