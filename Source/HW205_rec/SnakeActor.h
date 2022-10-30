// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SnakeActor.generated.h"


class ASnakeElementBase;
class AFood;
class ATruncator;
class ABigSphere;

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

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ATruncator> TruncatorClass;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ABigSphere> BigSphereClass;

	EMovementDirection TickDirection;

	UPROPERTY(BlueprintReadWrite)
	int32 ScoreCount;

	UPROPERTY()
	TArray<ASnakeElementBase*> SnakeElements;

	UPROPERTY()
	ATruncator* TruncatorToDestroy;

	UPROPERTY()
	ABigSphere* BigSphereToDestroy;

	bool fUCkTHiSsHIt;

	UPROPERTY(EditDefaultsOnly)
	float ElemSize;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	int UltaChance = 5;

	int deez = 0;

	int eaten = 0;

	UPROPERTY()
	EMovementDirection LastMoveDirection;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float MovementSpeed;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UFUNCTION(BlueprintCallable)
	void AddSnakeElement(int32 ElemCount = 1);


	UFUNCTION(BlueprintCallable)
	void Move();

	void Teleport();

	UFUNCTION(BlueprintCallable)
	void CreateFood();

	UFUNCTION(BlueprintCallable)
	void CreateUlta();

	UFUNCTION(BlueprintImplementableEvent)
	void AddScore();

	UFUNCTION(BlueprintImplementableEvent)
	void UltaDestroy();

	UFUNCTION(BlueprintImplementableEvent)
	void UltaEvent();

	UFUNCTION(BlueprintCallable)
	void Truncate();

	UFUNCTION(BlueprintCallable)
	void FDestroyUlta();





	FTransform ProductPos(int xin, int yin);

	UFUNCTION()
	void SnakeElementOverlap(ASnakeElementBase* OverlappedBlock, AActor* Other);
};
