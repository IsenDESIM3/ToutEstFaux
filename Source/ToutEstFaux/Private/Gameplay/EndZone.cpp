// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/EndZone.h"

#include "Global/MainGameState.h"
#include "Global/PlayerInterface.h"

// Sets default values
AEndZone::AEndZone()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	EndBox = CreateDefaultSubobject<UBoxComponent>(TEXT("End Box"));
	EndBox->SetupAttachment(RootComponent);

	EndBox->OnComponentBeginOverlap.AddDynamic(this,&AEndZone::OnOverlapBegin);

}

// Called when the game starts or when spawned
void AEndZone::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEndZone::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEndZone::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFrontSweep, const FHitResult& SweepResult)
{
	if(OtherActor->Implements<UPlayerInterface>())
	{
		PlayerFinish(TScriptInterface<IPlayerInterface>(OtherActor)->GetPlayerController());
	}
}

void AEndZone::PlayerFinish(AMyPlayerController* Pc)
{
	if(Pc)
	{
		if(AMainGameState* GameState = Cast<AMainGameState>(GetWorld()->GetGameState()))
		{
			GameState->PlayerFinsih(Pc,Camera);
		}
	}
}

