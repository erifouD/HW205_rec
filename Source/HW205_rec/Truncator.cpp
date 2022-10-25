// Fill out your copyright notice in the Description page of Project Settings.


#include "Truncator.h"
#include "SnakeActor.h"
#include "SnakeElementBase.h"

// Sets default values
ATruncator::ATruncator()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATruncator::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATruncator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATruncator::Interact(AActor* Interactor, bool DDHead)
{
	auto Snake = Cast<ASnakeActor>(Interactor);
	if (IsValid(Snake))
	{
		Snake->Truncate();
		Destroy();
	}
}

