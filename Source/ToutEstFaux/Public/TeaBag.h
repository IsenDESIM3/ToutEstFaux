// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Global/Select.h"
#include "TeaBag.generated.h"

/**
 * 
 */
UCLASS()
class TOUTESTFAUX_API ATeaBag : public ASelect
{
	GENERATED_BODY()
	
public:
	UFUNCTION()
	virtual void Release(FVector newpos, FRotator newrot) override;

	UFUNCTION()
	virtual AActor* GetItemTarget() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AActor* TeaCup;
};
