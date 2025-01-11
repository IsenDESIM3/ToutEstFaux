// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interactable.h"
#include "Global/Select.h"
#include "Global/MyPlayerController.h"
#include "TeaBag.h"
#include "TeaKettle.h"
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

	
	UPROPERTY()
	bool bIsFilled = false;

	UPROPERTY()
	bool bHasTeaBag = false;

	UPROPERTY(BlueprintReadWrite)
	AMyPlayerController* MyPlayerController;

	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* TeaBagLocation;

	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* TeaCupLocation;

	UPROPERTY()
	ATeaBag* TeaBag;
	
	UPROPERTY(EditDefaultsOnly)
	UMaterialInterface* TeaCupCorrectMaterial;

	UPROPERTY(EditDefaultsOnly)
	UMaterialInterface* TeaLiquidMaterial;

	UPROPERTY(EditDefaultsOnly)
	UMaterialInterface* TeaLiquidBaseMaterial;
	
	UFUNCTION()
	virtual void Interact() override;

	UFUNCTION()
	virtual void Clickable() override;

	virtual bool bCanInteract() override;


private:
	UPROPERTY(EditDefaultsOnly, Category="Sound")
	USoundBase* PutWaterSound;
	UPROPERTY(EditDefaultsOnly, Category="Sound")
	USoundBase* DrinkSound;
};
