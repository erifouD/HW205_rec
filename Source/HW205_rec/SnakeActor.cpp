// Fill out your copyright notice in the Description page of Project Settings.


#include "SnakeActor.h"
#include "SnakeElementBase.h"

// Sets default values
ASnakeActor::ASnakeActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	ElemSize = 100.f;
	MovementSpeed = 10.f;
	LastMoveDirection = EMovementDirection::DOWN;

}

// Called when the game starts or when spawned
void ASnakeActor::BeginPlay()
{
	Super::BeginPlay();
	AddSnakeElement(5);
	SetActorTickInterval(MovementSpeed);
	
}

// Called every frame
void ASnakeActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Move();
}

void ASnakeActor::AddSnakeElement(int ElemNum)
{

	for (int i = 0; i < ElemNum; i++)
	{
		FVector NewLoc(SnakeElements.Num() * ElemSize, 0, 0);
		FTransform NewTransform(NewLoc);
		ASnakeElementBase* NewSnakeElement = GetWorld()->SpawnActor<ASnakeElementBase>(SnakeElementClass, NewTransform);
		int32 ElIndex = SnakeElements.Add(NewSnakeElement);
		if (ElIndex == 0)
		{
			NewSnakeElement->FirstElement();
		}
	}
	
}

void ASnakeActor::Move()
{
	FVector MovementVector(ForceInitToZero);
	MovementSpeed = ElemSize;
	if (LastMoveDirection == EMovementDirection::UP)
	{
		MovementVector = FVector(MovementSpeed, 0, 0);
	}
	switch (LastMoveDirection)
	{
	case EMovementDirection::UP:
		MovementVector.X = MovementSpeed;
		break;

	case EMovementDirection::DOWN:
		MovementVector.X -= MovementSpeed;
		break;

	case EMovementDirection::LEFT:
		MovementVector.Y += MovementSpeed;
		break;

	case EMovementDirection::RIGHT:
		MovementVector.Y -= MovementSpeed;
		break;
	}

	//AddActorWorldOffset(MovementVector);

	for (int i = SnakeElements.Num() - 1; i > 0; i--) 
	{
		auto CurEl = SnakeElements[i];
		auto PreEl = SnakeElements[i - 1];
		FVector PreLoc = PreEl->GetActorLocation();
		CurEl->SetActorLocation(PreLoc);
	}

	SnakeElements[0]->AddActorWorldOffset(MovementVector);
}

