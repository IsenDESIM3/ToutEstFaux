// Fill out your copyright notice in the Description page of Project Settings.


#include "Global/Door.h"

#include "Global/MainGameMode.h"
#include "Global/MainGameState.h"
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
	DOREPLIFETIME(ADoor, _actualRotation);
}

// Called when the game starts or when spawned
void ADoor::BeginPlay()
{
	Super::BeginPlay();

	AMainGameState* _mainGameState = Cast<AMainGameState>(GetWorld()->GetGameState());
	if(_mainGameState)
	{
		_mainGameState->SetDoor(this);
	}

	switch (TypeOfOpening)
	{
		case ETypeOfOpening::E_FrontOpening :
		_maxRotation=90.f;
		break;

		case ETypeOfOpening::E_BackOpening :
		_maxRotation=-90.f;
		_multiplicator=-_multiplicator;
		break;
		
	}
}


void ADoor::SetOpenDoor()
{
	_multiplicator = -_multiplicator;
	bIsDoorOpened=!bIsDoorOpened;
	OnRep_DoorOpened();
}

ETypeOfDoor ADoor::GetTypeOfDoor()
{
	return MyTypeOfDoor;
}


void ADoor::OnRep_DoorOpened()
{
	if(bIsDoorOpened)
	{
		_RotationGoal=_maxRotation*_multiplicator;
		OpenTheDoor();
	}
	else
	{
		_RotationGoal=1*_multiplicator;
		OpenTheDoor();
	}
}

void ADoor::OpenTheDoor()
{
	
	if(_actualRotation * _multiplicator < _RotationGoal )
	{
		_actualRotation=Door->GetRelativeRotation().Yaw + _multiplicator;
		OnRep_ChangeRot();
		GetWorldTimerManager().SetTimer(DoorHandler,this,&ADoor::OpenTheDoor,0.02);
	}
}

void ADoor::OnRep_ChangeRot()
{
	Door->SetRelativeRotation(FRotator(Door->GetRelativeRotation().Pitch,_actualRotation,Door->GetRelativeRotation().Roll));
}

