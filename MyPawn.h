// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "MyPawn.generated.h"

UCLASS()
class CPPBASICTRAINING_API AMyPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AMyPawn();

	UPROPERTY(VisibleAnywhere, Category = "My Pawn Components")
	class UStaticMeshComponent* MyStaticMesh;

	UPROPERTY(VisibleAnywhere, Category = "My Pawn Components")
	class UCameraComponent* MyCamera;

	UPROPERTY(VisibleAnywhere, Category = "My Pawn Components")
	class USpringArmComponent* MySpringArm;

	UPROPERTY(EditAnywhere, Category = "My Pawn Movement")
	float MaxSpeed;

	FORCEINLINE UStaticMeshComponent* GetStaticMeshComponent() const {return MyStaticMesh;}
	FORCEINLINE USpringArmComponent* GetSpringArmComponent() const {return MySpringArm;}

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	void MoveForward(float value);
	void MoveRight(float value);
	FVector Velocity;

	void LookUp(float value);
	void LookRight(float value);
	FVector2D MouseInput;
};
