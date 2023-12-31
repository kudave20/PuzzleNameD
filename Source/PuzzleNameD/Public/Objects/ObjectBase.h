// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/InteractableInterface.h"
#include "Components/TimelineComponent.h"
#include "ObjectBase.generated.h"

class UBoxComponent;

UCLASS()
class PUZZLENAMED_API AObjectBase : public AActor, public IInteractableInterface
{
	GENERATED_BODY()
	
public:	
	AObjectBase();
	virtual void Tick(float DeltaTime) override;
	virtual float MeasureTotalMass(TArray<IInteractableInterface*>& DetectedObjects) override;
	virtual void SetCollisionResponse(ECollisionResponse NewResponse) override;

protected:
	virtual void BeginPlay() override;
	virtual void OnPreview() override;
	virtual void OnPlace() override;
	virtual void OnDisappear() override;
	virtual UStaticMeshComponent* GetMesh() override { return Mesh; }
	virtual float GetMass() override { return Mass; }
	virtual bool IsDuplicatable() override { return bIsDuplicatable; }
	virtual void BecomeDuplicatable(bool bDuplicatable) override { bIsDuplicatable = bDuplicatable; }
	virtual bool IsGrabbed() override { return bIsGrabbed; }
	virtual void SetIsGrabbed(bool bGrabbed) override { bIsGrabbed = bGrabbed; }

	UPROPERTY(EditAnywhere, Category = "Material")
	TArray<UMaterialInstance*> PreviewMaterials;

	UPROPERTY(EditAnywhere, Category = "Material")
	TArray<UMaterialInstance*> OriginalMaterials;

private:
	UPROPERTY(VisibleAnywhere, Category = "Components")
	TObjectPtr<UStaticMeshComponent> Mesh;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	TObjectPtr<UBoxComponent> AreaBox;

	UPROPERTY(EditAnywhere, Category = "Properties")
	float Mass;

	UPROPERTY(EditAnywhere, Category = "Properties")
	float Width = 30.f;

	UPROPERTY(EditAnywhere, Category = "Properties")
	float TraceLength = 1.f;

	UPROPERTY(EditAnywhere, Category = "Properties")
	int32 NumberOfLines = 5;

	/*
	* Use it for calculating pulley.
	*/
	float TotalMass = 0.f;

	/*
	* Disappear Effect
	*/
	UPROPERTY(VisibleAnywhere, Category = "Components")
	TObjectPtr<UTimelineComponent> DisappearTimeline;
	FOnTimelineFloat DisappearTrack;
	FOnTimelineEvent DisappearTimelineFinished;

	UPROPERTY(EditAnywhere, Category = "Curves")
	UCurveFloat* DisappearCurve;

	void StartDisappear();
	
	UFUNCTION()
	void ClearAll(float DisappearValue);

	UFUNCTION()
	void DisappearFinished();

	UPROPERTY()
	TArray<AObjectBase*> DuplicatedObjects;

	bool bIsDuplicatable = true;

	FTimerHandle DuplicateTimer;

	bool bIsGrabbed;

public:
	FORCEINLINE FTimerHandle& GetDuplicateTimer() { return DuplicateTimer; }
};
