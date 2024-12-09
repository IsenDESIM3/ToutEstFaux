// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/MyCharacters.h"

#include "EnhancedInputComponent.h"
#include "Camera/CameraActor.h"
#include "Components/BoxComponent.h"
#include "GameFramework/InputSettings.h"
#include "Global/MyPlayerController.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AMyCharacters::AMyCharacters()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"));
	CameraComp->SetupAttachment(GetMesh());
	itemPos = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ItemPos"));
	itemPos->SetupAttachment(CameraComp);
	itemPos->SetRelativeLocation(FVector(70,50,-20));
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
	UEnhancedInputComponent* EIC = Cast<UEnhancedInputComponent>(UGameplayStatics::GetPlayerController(GetWorld(),0)->InputComponent);
	
	AMyPlayerController* PC = GetController<AMyPlayerController>();
	check(EIC && PC);

	ULocalPlayer* LocalPlayer = UGameplayStatics::GetPlayerController(GetWorld(),0)->GetLocalPlayer();
	check(LocalPlayer);
	
	UEnhancedInputLocalPlayerSubsystem* Subsystem =
		LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();
	check(Subsystem);
	
	
	PC->SetInput(EIC,Subsystem);
	
	Subsystem->ClearAllMappings();
	Subsystem->AddMappingContext(PC->defaultMappingContext, 0);

	UWidget_Interaction* WidgetUse = CreateWidget<UWidget_Interaction>(PC, defaultWidget);
	if(WidgetUse)
	{
		WidgetUse->AddToViewport(0);
		PC->SetWidget(WidgetUse);
	}
	
}



