// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/Train.h"

#include "Kismet/GameplayStatics.h"

// Sets default values
ATrain::ATrain()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	Locomotive=CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Locomotive"));

}

// Called when the game starts or when spawned
void ATrain::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATrain::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(MyTrack)
	{
		SetLocomotivePos();

		_trackDistance = Speed * UGameplayStatics::GetWorldDeltaSeconds(GetWorld()) + _trackDistance ;
		_trackDistance = int(_trackDistance) % int(MyTrack->GetSpline()->GetSplineLength());
		
		UpdateWagonPos();
	}

}


// Called to bind functionality to input
void ATrain::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ATrain::UpdateWagonPos()
{
	if(MyTrack)
	{
		for (int i=0 ; i < Wagons.Num();i++)
		{
			if(Wagons[i])
			{
				float _wagonTrackDistance = i * -WagonSize - WagonSize + _trackDistance;

				if(_wagonTrackDistance<0)
				{
					_wagonTrackDistance += MyTrack->GetSpline()->GetSplineLength();
				}

				Wagons[i]->SetWorldLocationAndRotation(MyTrack->GetSpline()->GetLocationAtDistanceAlongSpline(_wagonTrackDistance,ESplineCoordinateSpace::World)
					,MyTrack->GetSpline()->GetRotationAtDistanceAlongSpline(_wagonTrackDistance,ESplineCoordinateSpace::World)+FRotator(0,-90,0));
			}
			
		}
	}
}

bool ATrain::SetLocomotivePos()
{
	if(MyTrack)
	{
		SetActorLocationAndRotation(MyTrack->GetSpline()->
			GetLocationAtDistanceAlongSpline(_trackDistance,ESplineCoordinateSpace::World)
				,MyTrack->GetSpline()->
				GetRotationAtDistanceAlongSpline(_trackDistance,ESplineCoordinateSpace::World)+
				FRotator(0,-90,0));
	}

	return MyTrack!=nullptr;
}

void ATrain::SetNewWagonColor(UStaticMeshComponent* NewWagon)
{
	NewWagon->SetMaterial(0,Materials[ColorIndex]);
	ColorIndex + 1 < Materials.Num() ? ColorIndex++ : ColorIndex = 0;
}

float ATrain::GetWagonSize()
{
	return -WagonSize;
}

