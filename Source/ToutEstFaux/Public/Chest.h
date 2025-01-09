// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interactable.h"
#include "GameFramework/Actor.h"
#include "Chest.generated.h"

UCLASS()
class TOUTESTFAUX_API AChest : public AActor, public IInteractable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AChest();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* BotChest;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* TopChest;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	virtual void Interact() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsOpen = false;
	UPROPERTY(editAnywhere, Category="Sound")
	USoundBase* Sound;
};
