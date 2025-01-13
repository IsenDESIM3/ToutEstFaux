// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/Klakette.h"

#include "Global/MainGameState.h"

AKlakette::AKlakette()
{
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Klaket"));
	Mesh->SetupAttachment(RootComponent);
}

void AKlakette::BeginPlay()
{
	Super::BeginPlay();
	SetActorLocation(GetActorLocation()+FVector(0,0,-100));

	if(AMainGameState* GS = Cast<AMainGameState>(GetWorld()->GetGameState()))
	{
		GS->AddKlaket(this);
	}
}

void AKlakette::Spawn()
{
	SetActorLocation(GetActorLocation()+FVector(0,0,100));
}
