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
			Snake->AddSnakeElement();
		}
		int32 x = FMath::FRandRange(-8, 8);
		int32 y = FMath::FRandRange(-8, 8);

		x = x * Snake->ElemSize;
		y = y * Snake->ElemSize;
		FVector Locati(x, y, 0);
		FTransform FoodTrans(Locati);

		AFood* NewFood = GetWorld()->SpawnActor<AFood>(Snake->FoodClass, FoodTrans);
		Snake->ScoreCount += 10;
		Snake->AddScore();
		
	}
	Destroy();

}
