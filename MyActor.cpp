// Fill out your copyright notice in the Description page of Project Settings.


//#include "Actors/MyActor.h" 把Actors/删掉，
#include "MyActor.h" //添加头文件时往后新增
#include "Components/StaticMeshComponent.h"

// Sets default values
AMyActor::AMyActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	// 如果这个actor不需要tick功能，则可以改成false
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
	Super::BeginPlay(); // Super 以父类方式运行
	
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

