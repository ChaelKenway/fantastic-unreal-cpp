// Fill out your copyright notice in the Description page of Project Settings.


//#include "Actors/MyActor.h" ��Actors/ɾ����
#include "MyActor.h" //���ͷ�ļ�ʱ��������
#include "Components/StaticMeshComponent.h"

// Sets default values
AMyActor::AMyActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	// ������actor����Ҫtick���ܣ�����Ըĳ�false
	PrimaryActorTick.bCanEverTick = true;

	MyStaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MyStaticMesh"));

	InitLocation = FVector(0.0f);
	PlacedLocation = FVector(0.0f);

	bGoToInitLocation = false;
	WorldOrigin = FVector(0.0f);

	TickPositionOffset = FVector(0.0f);
	bShouldMove = false;

	InitForce = FVector(0.0f);
	InitTorque = FVector(0.0f);
	bAccelChange = false;
}

// Called when the game starts or when spawned
void AMyActor::BeginPlay()
{
	Super::BeginPlay(); // Super �Ը��෽ʽ����
	
	PlacedLocation = GetActorLocation();
	if (bGoToInitLocation)
	{
		SetActorLocation(InitLocation);
	}

	// MyStaticMesh->AddForce(InitForce, "NAME_None", bAccelChange);
	// MyStaticMesh->AddTorque(InitTorque, "NAME_None", bAccelChange);
}

// Called every frame
void AMyActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(bShouldMove)
	{
		FHitResult HitResult;
		AddActorLocalOffset(TickPositionOffset, true, &HitResult);
		UE_LOG(LogTemp, Warning, TEXT("X: %f, Y: %f, Z: %f "), HitResult.Location.X, HitResult.Location.Y, HitResult.Location.Z);
	}
}

