// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Chest.h"
#include "Global/Select.h"
#include "Screwdriver.generated.h"

/**
 * 
 */
UCLASS()
class TOUTESTFAUX_API AScrewdriver : public ASelect
{
	GENERATED_BODY()


public:
	UFUNCTION()
	virtual void Release(FVector newpos) override;

	UFUNCTION()
	virtual AActor* GetItemTarget() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AChest* Target;
};
