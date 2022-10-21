// Fill out your copyright notice in the Description page of Project Settings.


#include "SnakeActor.h"
#include "SnakeElementBase.h"
#include "Food.h"
#include "UnrealInterface.h"


// Sets default values
ASnakeActor::ASnakeActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	ElemSize = 100.f;
	MovementSpeed = 10.f;
	LastMoveDirection = EMovementDirection::DOWN;
	ScoreCount = 0;
}

// Called when the game starts or when spawned
void ASnakeActor::BeginPlay()
{
	Super::BeginPlay();
	AddSnakeElement(CountOfElementsOnStart);
	SetActorTickInterval(MovementSpeed);
	CreateFood();
}


// Called every frame
void ASnakeActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Move();
	TickDirection = LastMoveDirection;
}

void ASnakeActor::AddSnakeElement(int32 ElemCount)
{
	FVector PreLoc;

	for (int i = 0; i < ElemCount; i++)
	{
		if ((SnakeElements.Num() == 0) || ElemCount > 2)
		{
			PreLoc = FVector(SnakeElements.Num() * ElemSize, 0, 0);
		}
		else
		{
			PreLoc = FVector(SnakeElements.Last()->GetActorLocation());
		}
		

		//FVector NewLoc(PreLoc);
		FTransform NewTransform(PreLoc);
		ASnakeElementBase* NewSnakeElement = GetWorld()->SpawnActor<ASnakeElementBase>(SnakeElementClass, NewTransform);
		NewSnakeElement->SnakeOwner = this;
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
	
	if (LastMoveDirection == EMovementDirection::UP)
	{
		MovementVector = FVector(MovementSpeed, 0, 0);
	}
	switch (LastMoveDirection)
	{
	case EMovementDirection::UP:
		MovementVector.X = ElemSize;
		break;

	case EMovementDirection::DOWN:
		MovementVector.X -= ElemSize;
		break;

	case EMovementDirection::LEFT:
		MovementVector.Y += ElemSize;
		break;

	case EMovementDirection::RIGHT:
		MovementVector.Y -= ElemSize;
		break;
	}

	//AddActorWorldOffset(MovementVector);
	SnakeElements[0]->ToggleCol();

	for (int i = SnakeElements.Num() - 1; i > 0; i--) 
	{
		auto CurEl = SnakeElements[i];
		auto PreEl = SnakeElements[i - 1];
		FVector PreLoc = PreEl->GetActorLocation();
		CurEl->SetActorLocation(PreLoc);
	}

	SnakeElements[0]->AddActorWorldOffset(MovementVector);
	SnakeElements[0]->ToggleCol();
}

void ASnakeActor::Teleport()
{
	FVector SecLocation = SnakeElements[1]->GetActorLocation();

	if (LastMoveDirection == EMovementDirection::DOWN || LastMoveDirection == EMovementDirection::UP)
	{
		SnakeElements[0]->SetActorLocation(FVector(SecLocation.X * -1, SecLocation.Y, SecLocation.Z));
	}
	else if (LastMoveDirection == EMovementDirection::LEFT || LastMoveDirection == EMovementDirection::RIGHT)
	{
		SnakeElements[0]->SetActorLocation(FVector(SecLocation.X, SecLocation.Y * -1, SecLocation.Z));
	}
}

void ASnakeActor::CreateFood()
{
	int32 x = FMath::FRandRange(-10, 10);
	int32 y = FMath::FRandRange(-21, 21);

	x = x * ElemSize;
	y = y * ElemSize;
	FVector Locati(x, y, 0);
	FTransform FoodTrans(Locati);
	AFood* NewFood = GetWorld()->SpawnActor<AFood>(FoodClass, FoodTrans);
}

void ASnakeActor::SnakeElementOverlap(ASnakeElementBase* OverlappedBlock, AActor* Other)
{
	if (IsValid(OverlappedBlock))
	{
		int32 ElemIndex;
		SnakeElements.Find(OverlappedBlock, ElemIndex);
		bool first = ElemIndex == 0;
		IUnrealInterface* InInter = Cast<IUnrealInterface>(Other);
		if (InInter)
		{			
			InInter->Interact(this, first);
		}
	}
}

