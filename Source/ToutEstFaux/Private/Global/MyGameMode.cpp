// Fill out your copyright notice in the Description page of Project Settings.


#include "Global/MyGameMode.h"
#include "Global/MyPlayerController.h"
#include "Kismet/GameplayStatics.h"

void AMyGameMode::BeginPlay()
{
	Super::BeginPlay();
	PlayerController = Cast<AMyPlayerController> (UGameplayStatics::GetPlayerController(GetWorld(),0));
}
