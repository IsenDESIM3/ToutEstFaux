// Fill out your copyright notice in the Description page of Project Settings.


#include "Cosplayer/Plinth.h"

#include "Cosplayer/Figurine.h"

// Sets default values
APlinth::APlinth()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	
	plinthCollider=CreateDefaultSubobject<UBoxComponent>("Plinth Collider 1");
	plinthCollider->SetupAttachment(RootComponent);

	plinthCollider->OnComponentBeginOverlap.AddDynamic(this,&APlinth::OnOverlapBegin);
	plinthCollider->OnComponentEndOverlap.AddDynamic(this,&APlinth::OnOverlapedEnd);
}

// Called when the game starts or when spawned
void APlinth::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlinth::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APlinth::CheckIfFigurineIsGood()
{
	if(_myTeletubbiesType==_figurine->GetTeletubbiesType())
	{
		
		if(_figurine->GetIfFigurineIsInRightPose())
		{
			GEngine->AddOnScreenDebugMessage(-1,1, FColor::Green, "Parfait");
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(-1,1, FColor::Red,"Pas la bonne pose");
		}
		
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1,1,FColor::Orange,"Pas Bon");
	}
}

void APlinth::RemoveFigurine()
{
	_figurine=nullptr;
	GEngine->AddOnScreenDebugMessage(-1,1,FColor::Red,"Ciao");
}




void APlinth::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
                                      UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFrontSweep, const FHitResult& SweepResult)
{
	if(OtherActor->Implements<UTeletubbies>() && !_figurine)
	{
		_figurine=TScriptInterface<ITeletubbies>(OtherActor);
		CheckIfFigurineIsGood();
	}
}


void APlinth::OnOverlapedEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if(OtherActor->Implements<UTeletubbies>() && _figurine==TScriptInterface<ITeletubbies>(OtherActor))
	{
		RemoveFigurine();
	}
}
