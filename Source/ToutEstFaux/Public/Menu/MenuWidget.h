// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/CircularThrobber.h"
#include "Components/EditableText.h"
#include "Components/VerticalBox.h"
#include "MenuWidget.generated.h"

class AMenuGameMode;
/**
 * 
 */
UCLASS()
class TOUTESTFAUX_API UMenuWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	
	virtual void NativeConstruct() override;
	
protected:
	UPROPERTY(meta=(BindWidget))
	UVerticalBox* VB_Main;

	UPROPERTY(meta=(BindWidget))
	UVerticalBox* VB_Server;

	UPROPERTY(meta=(BindWidget))
	UVerticalBox* VB_ServerMenu;

	UPROPERTY(meta=(BindWidget))
	UVerticalBox* VB_CreateMenu;

	UPROPERTY(meta=(BindWidget))
	UVerticalBox* VB_ListOfServer;

	UPROPERTY(meta=(BindWidget))
	UVerticalBox* VB_Mapping;

	UPROPERTY(meta=(BindWidget))
	UVerticalBox* VB_Option;

	UPROPERTY(meta=(BindWidget))
	UButton* Btn_Play;

	UPROPERTY(meta=(BindWidget))
	UButton* Btn_Options;

	UPROPERTY(meta=(BindWidget))
	UButton* Btn_Quit;

	UPROPERTY(meta=(BindWidget))
	UButton* Btn_Back;

	UPROPERTY(meta=(BindWidget))
	UButton* Btn_CreateServer;

	UPROPERTY(meta=(BindWidget))
	UButton* Btn_Refresh;

	UPROPERTY(meta=(BindWidget))
	UButton* Btn_Create;

	UPROPERTY(meta=(BindWidget))
	UButton* Btn_BackOption;

	UPROPERTY(meta=(BindWidget),BlueprintReadOnly)
	UEditableText* ETB_HostName;

	UPROPERTY(meta=(BindWidget),BlueprintReadOnly)
	UEditableText* ETB_ServerName;

	UPROPERTY(meta=(BindWidget))
	UCircularThrobber* CT_Chargement;


public:
	void SetMenuGameMode(AMenuGameMode* GameMode);
	void AddServerSlot(UWidget* NewWidget);

	void AddInputSlot(UWidget* NewWidget);

	void ShowUnshowRefreshButton(bool bShow);

	UFUNCTION(BlueprintNativeEvent)
	void ChargementScreen();

private:
	
	UFUNCTION()
	void QuitTheGame();

	UFUNCTION()
	void Play();

	UFUNCTION()
	void Option();

	UFUNCTION()
	void Back();

	UFUNCTION()
	void ChangeMenu();

	UFUNCTION()
	void OpenCreateMenu();

	UFUNCTION()
	void RefreshServer();

	UFUNCTION()
	void CreateSession();

	UFUNCTION()
	void SaveInput();

	void CleanListOfServers();

	UPROPERTY()
	AMenuGameMode* _menuGameMode=nullptr;

	bool bAlreadyHaveInput=false;
};
