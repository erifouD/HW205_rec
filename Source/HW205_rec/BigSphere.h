// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "UnrealInterface.h"
#include "BigSphere.generated.h"

UCLASS()
class HW205_REC_API ABigSphere : public AActor, public IUnrealInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABigSphere();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void Interact(AActor* Interactor, bool DDHead) override;

};
