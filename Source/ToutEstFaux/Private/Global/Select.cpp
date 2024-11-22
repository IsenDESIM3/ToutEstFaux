// Fill out your copyright notice in the Description page of Project Settings.


#include "Global/Select.h"

#include "Kismet/KismetMathLibrary.h"

// Sets default values
ASelect::ASelect()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASelect::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASelect::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASelect::Shrink(FVector cameraLocation)
{
	inialLocation = GetActorLocation();
	initialRotation = GetActorRotation();
	GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Turquoise, "Shrinking");
	SetActorScale3D(GetActorScale()*0.1);
	SetActorLocation(cameraLocation);
}

void ASelect::Increase()
{
	GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Purple, "increasing");
	SetActorScale3D(GetActorScale()*10);
	SetActorLocation(inialLocation);
	SetActorRotation(initialRotation);
}

void ASelect::NewRotation(FRotator objectRotation)
{
	SetActorRotation(UKismetMathLibrary::ComposeRotators(GetActorRotation(), objectRotation));
}

void ASelect::clicable()
{
	GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Yellow, "clicable");
}

