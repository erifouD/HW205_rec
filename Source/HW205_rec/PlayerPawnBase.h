// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PlayerPawnBase.generated.h"


class UCameraComponent;
class ASnakeActor;

UCLASS()
class HW205_REC_API APlayerPawnBase : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APlayerPawnBase();

	UPROPERTY(BlueprintReadWrite)
	UCameraComponent* PawnCamera;

	UPROPERTY(BlueprintReadWrite)
	ASnakeActor* SnakeActorBase;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ASnakeActor> SnakeActorClass;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void CreateSnakeActor();


	UFUNCTION()
	void HPIVert(float value);

	UFUNCTION()
	void HPIHor(float value);

};
