// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Global/Select.h"
#include "Manga.generated.h"

/**
 * 
 */
UENUM(BlueprintType)
enum class ETome : uint8
{
	E_Tome0 UMETA(DisplayName="Tome 0"),
	E_Tome1 UMETA(DisplayName="Tome 1"),
	E_Tome2 UMETA(DisplayName="Tome 2"),
	E_Tome3 UMETA(DisplayName="Tome 3"),
	E_Tome4 UMETA(DisplayName="Tome 4"),
	E_Tome5 UMETA(DisplayName="Tome 5"),
	E_Tome6 UMETA(DisplayName="Tome 6"),
	E_Tome7 UMETA(DisplayName="Tome 7"),
	E_Tome8 UMETA(DisplayName="Tome 8"),
	E_Tome9 UMETA(DisplayName="Tome 9"),
	
};
UCLASS()
class TOUTESTFAUX_API AManga : public ASelect
{

	GENERATED_BODY()
private:
	UPROPERTY(EditAnywhere,BlueprintReadOnly,meta=(AllowPrivateAccess))
	ETome MyCover = ETome::E_Tome0;
	
};
