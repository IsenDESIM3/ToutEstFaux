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
	ATeaBag();

	virtual void BeginPlay() override;
	
public:
	UFUNCTION()
	virtual void Release(FVector newpos, FRotator newrot) override;

	UFUNCTION()
	virtual bool GetIfINeedToBeDestroy() override;

	UFUNCTION()
	virtual AActor* GetItemTarget() override;

	UFUNCTION()
	virtual FVector GetReleasePos() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AActor* TeaCup;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* TeaBagMesh;


private:
	FVector BoxPos {0,0,0};
};
