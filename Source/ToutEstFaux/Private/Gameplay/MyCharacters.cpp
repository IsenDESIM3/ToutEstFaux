// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/MyCharacters.h"

#include "Camera/CameraActor.h"
#include "GameFramework/InputSettings.h"

// Sets default values
AMyCharacters::AMyCharacters()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"));
	CameraComp->SetupAttachment(GetMesh());
}

// Called when the game starts or when spawned
void AMyCharacters::BeginPlay()
{
	Super::BeginPlay();
	
}

FVector AMyCharacters::GetCameraLocation()
{
	return CameraComp->GetComponentLocation();
}

FVector AMyCharacters::GetCameraForward()
{
	return GetActorForwardVector();
}

// Called every frame
void AMyCharacters::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMyCharacters::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
}



