// Fill out your copyright notice in the Description page of Project Settings.


#include "ObjectsWithValideSurfaces.h"

// Sets default values
AObjectsWithValideSurfaces::AObjectsWithValideSurfaces()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AObjectsWithValideSurfaces::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AObjectsWithValideSurfaces::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

float AObjectsWithValideSurfaces::getActorHeight()
{
	FBox actorBox = GetComponentsBoundingBox();
	
	return 2*actorBox.GetExtent().Z;
}

