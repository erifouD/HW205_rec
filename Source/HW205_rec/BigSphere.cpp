// Fill out your copyright notice in the Description page of Project Settings.


#include "BigSphere.h"
#include "SnakeActor.h"

// Sets default values
ABigSphere::ABigSphere()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABigSphere::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABigSphere::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABigSphere::Interact(AActor* Interactor, bool DDHead)
{
	if (DDHead)
	{
		auto Snake = Cast<ASnakeActor>(Interactor);
		if (IsValid(Snake))
		{
			Snake->AddSnakeElement(2);
			Snake->ScoreCount += 50;
			Snake->AddScore();
			Snake->eaten++;
		}
	}
	Destroy();
}

