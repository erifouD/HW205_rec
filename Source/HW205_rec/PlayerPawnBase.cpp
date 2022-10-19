// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerPawnBase.h"
#include "Engine/Classes/Camera/CameraComponent.h"
#include "SnakeActor.h"
#include "Components/InputComponent.h"

// Sets default values
APlayerPawnBase::APlayerPawnBase()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PawnCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("PawnCamera"));
	RootComponent = PawnCamera;
}
// Called when the game starts or when spawned
void APlayerPawnBase::BeginPlay()
{
	Super::BeginPlay();
	SetActorRotation(FRotator(-90, 0, 0));
	SetActorLocation(FVector(0, 0, 1200));
	CreateSnakeActor();
	
}

// Called every frame
void APlayerPawnBase::Tick(float DeltaTime)
{Super::Tick(DeltaTime);}

// Called to bind functionality to input
void APlayerPawnBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("Vert", this, &APlayerPawnBase::HPIVert);
	PlayerInputComponent->BindAxis("Hor", this, &APlayerPawnBase::HPIHor);
}

void APlayerPawnBase::CreateSnakeActor()
{
	SnakeActorBase = GetWorld()->SpawnActor<ASnakeActor>(SnakeActorClass, FTransform());
}

void APlayerPawnBase::HPIVert(float value)
{
	if (IsValid(SnakeActorBase))
	{
		if (value > 0 && SnakeActorBase->TickDirection != EMovementDirection::DOWN)
		{
			SnakeActorBase->LastMoveDirection = EMovementDirection::UP;
		}
		else if (value < 0 && SnakeActorBase->TickDirection != EMovementDirection::UP)
		{
			SnakeActorBase->LastMoveDirection = EMovementDirection::DOWN;
		}
	}
}

void APlayerPawnBase::HPIHor(float value)
{
	if (IsValid(SnakeActorBase))
	{
		if (value < 0 && SnakeActorBase->TickDirection != EMovementDirection::RIGHT)
		{
			SnakeActorBase->LastMoveDirection = EMovementDirection::LEFT;
		}
		else if (value > 0 && SnakeActorBase->TickDirection != EMovementDirection::LEFT)
		{
			SnakeActorBase->LastMoveDirection = EMovementDirection::RIGHT;
		}
	}
}

