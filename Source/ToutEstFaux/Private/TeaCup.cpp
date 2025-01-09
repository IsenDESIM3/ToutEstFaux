// Fill out your copyright notice in the Description page of Project Settings.


#include "TeaCup.h"


ATeaCup::ATeaCup()
{
	TeaBagLocation = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TeaBagLocation"));
	TeaBagLocation->SetupAttachment(GetRootComponent());
	TeaBagLocation->SetRelativeLocation(FVector(3, -2, 5));
}

void ATeaCup::Interact()
{
	if (bHasTeaBag) return;

	GEngine->AddOnScreenDebugMessage(-1,1, FColor::Red, "Interact");

	if (ATeaBag* TeaBag = Cast<ATeaBag>(MyPlayerController->selected->GetActor()))
	{
		if (TeaBag->Tags[0] == "Feur") UE_LOG(LogTemp, Warning, TEXT("CouCou"));
	}
	bHasTeaBag = true;
	
	IInteractable::Interact();
}
