// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MainGameMode.generated.h"

class ADoor;
class UWidget_Interaction;
class AMyCharacters;
class APlinth;

UENUM(BlueprintType)
enum class ETeletubbies : uint8
{
	E_Po UMETA(DisplayName="Po_Red"),
	E_Dispy UMETA(DisplayName="Dispy_Green"),
	E_Laalaa UMETA(DisplayName="Laalaa_Yellow"),
	E_Tinkywinky UMETA(DisplayName="Tinkywinky")
};

USTRUCT(BlueprintType)
struct FTeletubbiesMatData
{
	GENERATED_BODY()
	UPROPERTY(EditDefaultsOnly)
	ETeletubbies teletubbies=ETeletubbies::E_Po;

	UPROPERTY(EditDefaultsOnly)
	UMaterialInstance* bodyMat=nullptr;

	UPROPERTY(EditDefaultsOnly)
	UMaterialInstance* earMat=nullptr;

	UPROPERTY(EditDefaultsOnly)
	UMaterialInstance* faceMat=nullptr;

	UPROPERTY(EditAnywhere)
	UStaticMesh* teletubbiesAntMesh=nullptr;

	UPROPERTY(EditAnywhere)
	int32 goodPoseNumber;
	
};
/**
 * 
 */
UCLASS()
class TOUTESTFAUX_API AMainGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	//Cosplayer Enigma
	void SetPlinths(APlinth* newPlinth);
	void CheckIfCosplayerEnigmaFinish();
	void SetDoors(bool bIsExitDoor,ADoor* NewDoors);

	FTeletubbiesMatData GetTeletubbiesRightData(ETeletubbies TeletubbiesType);

	//Controllers
	
	//Call when a player join the game 
	virtual void OnPostLogin(AController* NewPlayer) override;
	//Call when a player quit the game
	virtual void Logout(AController* Exiting) override;
	
private:
	
	//Cosplayer Enigma
	TArray<APlinth*> _listOfAllPlinths{};

	UPROPERTY(EditDefaultsOnly,Category="All Teletubbies Configuration",meta=(AllowPrivateAccess))
	TArray<FTeletubbiesMatData> _listOfTeletubbiesMatData{};

	bool bIsCosplayerEnigmaFinish=false;

	//Controllers
	UPROPERTY()
	TArray<class AMyPlayerController*> _listOfPlayerController;

	UPROPERTY(EditDefaultsOnly,meta=(AllowPrivateAccess))
	TSubclassOf<AMyCharacters> _characterClass=nullptr;

	UPROPERTY()
	TArray<AMyCharacters*> _listOfCharacter{};

	UPROPERTY()
	TArray<ADoor*>_dressingDoors{};

	UPROPERTY()
	TArray<ADoor*>_exitDoors{};
};
