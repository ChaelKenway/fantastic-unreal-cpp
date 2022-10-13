// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPawn.h"
#include "Components/ActorComponent.h"
#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"//����������
#include "GameFramework/SpringArmComponent.h"
#include "UObject/ConstructorHelpers.h"//�����࣬��������


// Sets default values
AMyPawn::AMyPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//���������
	//RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	//MyStaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MyStaticMesh"));
	//MyStaticMesh->SetupAttachment(GetRootComponent());//���ӵ��������

	MyStaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MyStaticMesh"));
	RootComponent = MyStaticMesh;//��������ָ��Ϊ�����
	MyStaticMesh->SetCollisionProfileName(TEXT("Pawn"));

	//���ؾ�̬������Ͳ���
	static ConstructorHelpers::FObjectFinder<UStaticMesh> StaticMeshAsset(TEXT("StaticMesh'/Engine/BasicShapes/Sphere.Sphere'"));
	static ConstructorHelpers::FObjectFinder<UMaterialInterface> MaterialAsset(TEXT("Material'/Game/StarterContent/Materials/M_Metal_Gold.M_Metal_Gold'"));
	if (StaticMeshAsset.Succeeded() && MaterialAsset.Succeeded())
	{
		MyStaticMesh->SetStaticMesh(StaticMeshAsset.Object);
		MyStaticMesh->SetMaterial(0, MaterialAsset.Object);
		MyStaticMesh->SetWorldScale3D(FVector(0.5f));
	}

	//���������ҡ��
	MySpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("MySpringArm"));
	MySpringArm->SetupAttachment(GetStaticMeshComponent());
	MySpringArm->SetRelativeRotation(FRotator(-45.0f, 0.0f, 0.0f));
	MySpringArm->TargetArmLength = 400.0f;
	MySpringArm->bEnableCameraLag = true;
	MySpringArm->CameraLagSpeed = 3.0f;

	//���������
	MyCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("MyCamera"));
	MyCamera->SetupAttachment(GetSpringArmComponent());
	MyCamera->SetRelativeLocation(FVector(0.0f));
	MyCamera->SetRelativeRotation(FRotator(0.0f));

	//��ȡ���0
	AutoPossessPlayer = EAutoReceiveInput::Player0;

	//controller�̳�
	bUseControllerRotationYaw = true;

	MaxSpeed = 100.0f;
	Velocity = FVector::ZeroVector;
	MouseInput = FVector2D::ZeroVector;
}	

// Called when the game starts or when spawned
void AMyPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	AddActorLocalOffset(Velocity * DeltaTime, true);//�ƶ�

	AddControllerYawInput(MouseInput.X);//������ת�ӽ�

	//X-Roll, Y-Pitch, Z-Yaw
	FRotator NewSpringArmRotator = MySpringArm->GetComponentRotation();
	NewSpringArmRotator.Pitch = FMath::Clamp(NewSpringArmRotator.Pitch + MouseInput.Y, -80.0f, 0.0f);
	MySpringArm->SetWorldRotation(NewSpringArmRotator);//������ת�ӽ�
}

// Called to bind functionality to input
void AMyPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//����ӳ�䵽����
	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &AMyPawn::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &AMyPawn::MoveRight);
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &AMyPawn::LookUp);
	PlayerInputComponent->BindAxis(TEXT("LookRight"), this, &AMyPawn::LookRight);
}

void AMyPawn::MoveForward(float value)
{
	Velocity.X = FMath::Clamp(value, -1.0f, 1.0f) * MaxSpeed;
}

void AMyPawn::MoveRight(float value)
{
	Velocity.Y = FMath::Clamp(value, -1.0f, 1.0f) * MaxSpeed;
}

void AMyPawn::LookUp(float value)
{
	MouseInput.Y = FMath::Clamp(value, -1.0f, 1.0f);
}

void AMyPawn::LookRight(float value)
{
	MouseInput.X = FMath::Clamp(value, -1.0f, 1.0f);
}
