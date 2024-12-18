// Fill out your copyright notice in the Description page of Project Settings.


#include "Global/Select.h"

#include "GameFramework/SpringArmComponent.h"
#include "Gameplay/MyCharacters.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
ASelect::ASelect()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASelect::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASelect::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASelect::Shrink()
{
	inialLocation = GetActorLocation();
	initialRotation = GetActorRotation();
	GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Turquoise, "Shrinking");
	SetActorScale3D(GetActorScale()*0.4);
}

void ASelect::Increase()
{
	GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Purple, "increasing");
	SetActorScale3D(GetActorScale()/0.4);
	SetActorLocation(inialLocation);
	SetActorRotation(initialRotation);
}

void ASelect::NewRotation(FRotator objectRotation)
{
	SetActorRotation(UKismetMathLibrary::ComposeRotators(GetActorRotation(), objectRotation));
}

void ASelect::Clickable()
{
	GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Yellow, "clicable");

	IISelectable::Clickable();
}


void ASelect::Grabbed(UStaticMeshComponent* mesh)
{
	initialRotation = GetActorRotation();
	AttachToComponent(mesh, FAttachmentTransformRules::KeepWorldTransform, NAME_None);
	GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Orange, "grabbing");	
	SetActorScale3D(GetActorScale()*0.4);

}
void ASelect::Release(FVector newpos, FRotator newrot)
{
	DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);		
	SetActorScale3D(GetActorScale()/0.4);
	SetActorLocation(newpos);
	SetActorRotation(newrot);
}

void ASelect::SetFrontCamera(FVector Vector)
{
	// DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
	UE_LOG(LogTemp, Warning, TEXT("%f, %f, %f"), Vector.X, Vector.Y, Vector.Z);
	SetActorLocation(FVector(Vector.X, Vector.Y, Vector.Z));
}

void ASelect::SetInTheHand()
{
	SetActorRelativeLocation(FVector(0,0,0));
}

AActor* ASelect::GetItemTarget()
{
	return IISelectable::GetItemTarget();
}

