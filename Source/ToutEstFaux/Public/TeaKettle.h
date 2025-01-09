// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Global/Select.h"
#include "TeaKettle.generated.h"

/**
 * 
 */
UCLASS()
class TOUTESTFAUX_API ATeaKettle : public ASelect
{
	GENERATED_BODY()

public:
	UFUNCTION()
	virtual AActor* GetItemTarget() override;

	UFUNCTION()
	virtual FVector GetReleasePos() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AActor* TeaCup;
	
};
