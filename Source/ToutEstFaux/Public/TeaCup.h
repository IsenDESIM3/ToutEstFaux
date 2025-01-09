// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interactable.h"
#include "Global/Select.h"
#include "Global/MyPlayerController.h"
#include "TeaBag.h"
#include "TeaCup.generated.h"

/**
 * 
 */
UCLASS()
class TOUTESTFAUX_API ATeaCup : public ASelect, public IInteractable
{
	GENERATED_BODY()

	public:
	ATeaCup();

	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsFilled = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bHasTeaBag = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AMyPlayerController* MyPlayerController;

	UPROPERTY()
	UStaticMeshComponent* TeaBagLocation;

	UFUNCTION()
	virtual void Interact() override;
};
