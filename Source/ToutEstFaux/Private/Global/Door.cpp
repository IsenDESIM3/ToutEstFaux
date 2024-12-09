// Fill out your copyright notice in the Description page of Project Settings.


#include "Global/Door.h"

#include "Global/MainGameMode.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ADoor::ADoor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DoorFrame = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Door Frame"));
	DoorFrame->SetupAttachment(RootComponent);

	Door = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Door"));
	Door->SetupAttachment(DoorFrame);

}

// Called when the game starts or when spawned
void ADoor::BeginPlay()
{
	Super::BeginPlay();

	AMainGameMode* _mainGameMode = Cast<AMainGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	if(_mainGameMode)
	{
		_mainGameMode->SetDoors(bIsAnExitDoor,this);
	}

	switch (TypeOfOpening)
	{
		case ETypeOfOpening::E_FrontOpening :
		_maxRotation=90.f;
		break;

		case ETypeOfOpening::E_BackOpening :
		_maxRotation=-90.f;
		break;
		
	}
	
}

// Called every frame
void ADoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void ADoor::SetOpenDoor()
{
	_multiplicateur = -_multiplicateur;
	bIsDoorOpened=!bIsDoorOpened;
	bIsDoorOpened ? OpenTheDoor() : CloseTheDoor();
}


void ADoor::OpenTheDoor()
{
	GEngine->AddOnScreenDebugMessage(-1,1,FColor::Orange,"Going to Add");
	if(Door->GetRelativeRotation().Yaw * _multiplicateur < _maxRotation * _multiplicateur )
	{
		GEngine->AddOnScreenDebugMessage(-1,1,FColor::Green,"Add");
		Door->SetRelativeRotation(FRotator(Door->GetRelativeRotation().Pitch,Door->GetRelativeRotation().Yaw + _multiplicateur,Door->GetRelativeRotation().Roll));
		GetWorldTimerManager().SetTimer(DoorHandler,this,&ADoor::OpenTheDoor,0.02);
	}
	
}

void ADoor::CloseTheDoor()
{
	GEngine->AddOnScreenDebugMessage(-1,1,FColor::Red,"remove");
	if(Door->GetRelativeRotation().Yaw * -_multiplicateur >=1 )
	{
		Door->SetRelativeRotation(FRotator(Door->GetRelativeRotation().Pitch,Door->GetRelativeRotation().Yaw + _multiplicateur,Door->GetRelativeRotation().Roll));
		GetWorldTimerManager().SetTimer(DoorHandler,this,&ADoor::CloseTheDoor,0.02);
	}
	
}


