// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Global/Select.h"
#include "Klakette.generated.h"

/**
 * 
 */
UCLASS()
class TOUTESTFAUX_API AKlakette : public ASelect
{
	GENERATED_BODY()

public:
	AKlakette();
	virtual void BeginPlay() override;
	
	
	void Spawn();

protected:
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* Mesh;
};
