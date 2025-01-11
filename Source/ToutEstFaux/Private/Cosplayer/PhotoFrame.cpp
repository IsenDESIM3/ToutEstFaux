// Fill out your copyright notice in the Description page of Project Settings.


#include "Cosplayer/PhotoFrame.h"

#include "Global/MainGameState.h"

APhotoFrame::APhotoFrame()
{
	PhotoFrameMeshComponent=CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Photo Frame"));
	PhotoFrameMeshComponent->SetupAttachment(RootComponent);
}

void APhotoFrame::BeginPlay()
{
	Super::BeginPlay();

	if(AMainGameState* GameState = Cast<AMainGameState>(GetWorld()->GetGameState()))
	{
		GameState->SetPhotoFrame(this);
	}
}

void APhotoFrame::ChangeMat()
{
	if(SolutionMaterial)
	{
		PhotoFrameMeshComponent->SetMaterial(0,SolutionMaterial);
	}
	
}
