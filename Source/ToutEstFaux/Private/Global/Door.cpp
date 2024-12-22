// Fill out your copyright notice in the Description page of Project Settings.


#include "Global/Door.h"

#include "Global/MainGameMode.h"
#include "Kismet/GameplayStatics.h"

#include "Net/UnrealNetwork.h"

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

//This is for the replication
void ADoor::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ADoor, bIsDoorOpened);
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
	OnRep_DoorOpened();
}


void ADoor::OnRep_DoorOpened()
{
	if(bIsDoorOpened)
	{
		//Door->SetRelativeRotation(FRotator(Door->GetRelativeRotation().Pitch,_maxRotation,Door->GetRelativeRotation().Roll));
		Server_OpenTheDoor();
	}
	else
	{
		//Door->SetRelativeRotation(FRotator(Door->GetRelativeRotation().Pitch,0,Door->GetRelativeRotation().Roll));
		Server_CloseTheDoor();
	}
}

void ADoor::OpenTheDoor()
{
	
	if(Door->GetRelativeRotation().Yaw * _multiplicateur < _maxRotation * _multiplicateur )
	{
		Door->SetRelativeRotation(FRotator(Door->GetRelativeRotation().Pitch,Door->GetRelativeRotation().Yaw + _multiplicateur,Door->GetRelativeRotation().Roll));
		GetWorldTimerManager().SetTimer(DoorHandler,this,&ADoor::Server_OpenTheDoor,0.02);
	}
}

void ADoor::CloseTheDoor()
{
	if(Door->GetRelativeRotation().Yaw * -_multiplicateur >=1 )
	{
		Door->SetRelativeRotation(FRotator(Door->GetRelativeRotation().Pitch,Door->GetRelativeRotation().Yaw + _multiplicateur,Door->GetRelativeRotation().Roll));
		GetWorldTimerManager().SetTimer(DoorHandler,this,&ADoor::Server_CloseTheDoor,0.02);
	}
	
}

bool ADoor::Server_OpenTheDoor_Validate()
{
	return true;
}

void ADoor::Server_OpenTheDoor_Implementation()
{
	Multi_OpenTheDoor();
}

bool ADoor::Multi_OpenTheDoor_Validate()
{
	return true;
}

void ADoor::Multi_OpenTheDoor_Implementation()
{
	OpenTheDoor();
}

bool ADoor::Server_CloseTheDoor_Validate()
{
	return true;
}

void ADoor::Server_CloseTheDoor_Implementation()
{
	Multi_CloseTheDoor();
}

bool ADoor::Multi_CloseTheDoor_Validate()
{
	return true;
}

void ADoor::Multi_CloseTheDoor_Implementation()
{
	CloseTheDoor();
}


