// Fill out your copyright notice in the Description page of Project Settings.


#include "Food.h"
#include "SnakeActor.h"
#include "Engine/Classes/Components/StaticMeshComponent.h"

// Sets default values
AFood::AFood()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));
	MeshComp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	MeshComp->SetCollisionResponseToAllChannels(ECR_Overlap);
}

// Called when the game starts or when spawned
void AFood::BeginPlay()
{
	Super::BeginPlay();	
}

// Called every frame
void AFood::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AFood::Interact(AActor* Interactor, bool DDHead)
{
	if (DDHead)
	{
		auto Snake = Cast<ASnakeActor>(Interactor);
		if (IsValid(Snake))
		{
			Snake->eaten++;
			Snake->AddSnakeElement();
			Snake->CreateFood();
			Snake->ScoreCount += 10;
			Snake->AddScore();
			Snake->CreateTruncator();
			if (Snake->MovementSpeed > 0.01 && Snake->eaten % 10 == 0.f)
			{
				Snake->MovementSpeed -= 0.01;
				Snake->SetActorTickInterval(Snake->MovementSpeed);
				Snake->BigSpSpawn();
			}

		}		
	}
	Destroy();

}
