// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ObjectBase.h"
#include "PuzzleNameD/Interfaces/UnGrabbableInterface.h"
#include "Fan.generated.h"

/**
 * 
 */
UCLASS()
class PUZZLENAMED_API AFan : public AObjectBase, public IUnGrabbableInterface
{
	GENERATED_BODY()

public:
	AFan();
	virtual void Tick(float DeltaTime) override;
	virtual void SetCollisionResponse(ECollisionResponse NewResponse) override;

protected:
	virtual void BeginPlay() override;
	virtual void OnPreview_Implementation() override;
	virtual void OnPlace_Implementation() override;

private:
	UPROPERTY(VisibleAnywhere, Category = "Components")
	UStaticMeshComponent* Blade;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	class UBoxComponent* Range;

	UPROPERTY(EditAnywhere, Category = "Material")
	UMaterialInstance* BladePreviewMaterial;

	UPROPERTY(EditAnywhere, Category = "Material")
	UMaterialInstance* BladeOriginalMaterial;
	
	float RangeX;
	float RangeY;
	float RangeZ;

	/*
	UPROPERTY(EditAnywhere)
	float DistanceBetweenLines;'
	*/

	UPROPERTY(EditAnywhere, Category = "Wind")
	float MaxForce;

	UPROPERTY(EditAnywhere, Category = "Wind")
	float StartRadius;

	UPROPERTY(EditAnywhere, Category = "Wind")
	float Tangent;

	/*
	* Degree between two lines in a circle
	*/
	UPROPERTY(EditAnywhere, Category = "Wind")
	float DegreeBetweenLines;

	/*
	* Number of lines in a row
	*/
	UPROPERTY(EditAnywhere, Category = "Wind")
	int32 UnitNumberOfLines;

	void Push();

	//bool bIsPushingCharacter;
};
