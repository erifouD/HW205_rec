// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "UnrealInterface.h"
#include "SnakeElementBase.generated.h"

class UStaticMeshComponent;
class ASnakeActor;

UCLASS()
class HW205_REC_API ASnakeElementBase : public AActor, public IUnrealInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASnakeElementBase();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* StaticMeshComponent;

	UPROPERTY()
	ASnakeActor* SnakeOwner;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintNativeEvent)
	void FirstElement();
	void FirstElement_Implementation();

	virtual void Interact(AActor* Interactor, bool DDHead) override;

	UFUNCTION()
	void HandleBeginOverlap(UPrimitiveComponent* OverlappedComponent, 
		AActor* OtherActor, 
		UPrimitiveComponent* OtherComp, 
		int32 OtherBodyIndex, 
		bool bFromSweep, const 
		FHitResult &SweepResult);

	UFUNCTION()
	void ToggleCol();

};
