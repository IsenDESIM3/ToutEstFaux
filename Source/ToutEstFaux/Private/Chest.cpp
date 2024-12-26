// Fill out your copyright notice in the Description page of Project Settings.


#include "Chest.h"

// Sets default values
AChest::AChest()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BotChest=CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BotChest"));
	BotChest->SetupAttachment(RootComponent);
	
	TopChest=CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TopChest"));
	TopChest->SetupAttachment(BotChest);

}

// Called when the game starts or when spawned
void AChest::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AChest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AChest::Interact()
{
	TopChest->SetRelativeRotation(FRotator(170, 0, 0));
	bIsOpen = true;
}

