// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MyGameMode.generated.h"

/**
 * 
 */
UCLASS()
class TOUTESTFAUX_API AMyGameMode : public AGameModeBase
{
	GENERATED_BODY()

	protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	public:
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	class AMyPlayerController* PlayerController;

	
};
