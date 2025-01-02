// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/Track.h"

#include "Components/SplineMeshComponent.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
ATrack::ATrack()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Spline = CreateDefaultSubobject<USplineComponent>(TEXT("Spline"));
	Spline->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void ATrack::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATrack::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

USplineComponent* ATrack::GetSpline()
{
	return Spline;
}

USplineMeshComponent* ATrack::GetNewMesh_Implementation()
{
	return nullptr;
}

void ATrack::SetUpMesh()
{
	float xLength=GetXSize();
	int maxIndex = Spline->GetSplineLength() / xLength;
	
	for(int i=0; i<=maxIndex ;i++)
	{
		USplineMeshComponent* NewMeshComponent = GetNewMesh();
		if(NewMeshComponent)
		{
			NewMeshComponent->SetForwardAxis(ESplineMeshAxis::X);
			NewMeshComponent->SetStaticMesh(TrackMesh);

			float StartDistance =i*xLength;
			FVector StartPos = Spline->GetLocationAtSplineInputKey(StartDistance,ESplineCoordinateSpace::Local);
			FVector StartTangentPos =UKismetMathLibrary::ClampVectorSize(Spline->GetTangentAtDistanceAlongSpline(StartDistance,ESplineCoordinateSpace::Local),0.f,xLength);

			float EndDistance =(i+1)*xLength;
			FVector EndPos = Spline->GetLocationAtSplineInputKey(EndDistance,ESplineCoordinateSpace::Local);
			FVector EndTangentPos =UKismetMathLibrary::ClampVectorSize(Spline->GetTangentAtDistanceAlongSpline(EndDistance,ESplineCoordinateSpace::Local),0.f,xLength);

			NewMeshComponent->SetStartAndEnd(StartPos,StartTangentPos,EndPos,EndTangentPos);
		}
		
		
	}
}

float ATrack::GetXSize()
{
	if(TrackMesh)
	{
		FVector MeshSize = UKismetMathLibrary::Vector_GetAbs(TrackMesh->GetBoundingBox().Min)+UKismetMathLibrary::Vector_GetAbs(TrackMesh->GetBoundingBox().Max);
		return MeshSize.X;
	}
	return 0;
}

int ATrack::GetMaxIndex()
{
	return Spline->GetSplineLength() / GetXSize();
}



