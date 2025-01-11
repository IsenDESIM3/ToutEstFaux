// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Global/Select.h"
#include "PhotoFrame.generated.h"

/**
 * 
 */
UCLASS()
class TOUTESTFAUX_API APhotoFrame : public ASelect
{
	GENERATED_BODY()

public:
	APhotoFrame();
	virtual void BeginPlay() override;
	void ChangeMat();

protected:
	
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* PhotoFrameMeshComponent;
	
private:
	UPROPERTY(EditDefaultsOnly,meta=(AllowPrivateAccess))
	UMaterialInstance* SolutionMaterial;
	
};
