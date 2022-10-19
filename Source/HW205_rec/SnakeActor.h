// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SnakeActor.generated.h"


class ASnakeElementBase;
class AFood;

UENUM()
enum class EMovementDirection
{
	UP,
	DOWN,
	LEFT,
	RIGHT
};

UCLASS()
class HW205_REC_API ASnakeActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASnakeActor();

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ASnakeElementBase> SnakeElementClass;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AFood> FoodClass;

	EMovementDirection TickDirection;


	UPROPERTY()
	TArray<ASnakeElementBase*> SnakeElements;

	UPROPERTY(EditDefaultsOnly)
	float ElemSize;

	UPROPERTY()
	EMovementDirection LastMoveDirection;

	UPROPERTY(EditDefaultsOnly)
	float MovementSpeed;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UFUNCTION(BlueprintCallable)
	void AddSnakeElement(int ElemNum = 1);
	UFUNCTION(BlueprintCallable)
	void Move();

	UFUNCTION()
	void SnakeElementOverlap(ASnakeElementBase* OverlappedBlock, AActor* Other);
};
