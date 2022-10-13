// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyActor.generated.h" //添加头文件时往这个之前新增

UCLASS()
class CPPBASICTRAINING_API AMyActor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties 默认的构造函数
	AMyActor();

	// 实例可编辑，只有actor放在了地图中才能编辑变量
	UPROPERTY(EditInstanceOnly, Category = "My Actor Properties | Vector") // | 子分类
	FVector InitLocation;

	//实例只读
	UPROPERTY(VisibleInstanceOnly, Category = "My Actor Properties | Vector")
	FVector PlacedLocation; //游戏开始时实例的位置

	//只能在蓝图类模板中设置，会应用到这个蓝图类的所有实例
	UPROPERTY(EditDefaultsOnly, Category = "My Actor Properties | Vector")
	bool bGoToInitLocation; //需要去到初始位置吗？布尔变量必须由b开头，但是虚幻会自动去掉b

	//模板只读，等于没用，做参考
	UPROPERTY(VisibleDefaultsOnly, Category = "My Actor Properties | Vector")
	FVector WorldOrigin;

	// 任何地方都可见 不要将指针指定成editanywhere
	UPROPERTY(VisibleAnywhere, Category = "MyActorComponents")
	class UStaticMeshComponent *MyStaticMesh; // 静态网格体组件

	//任何地方都可见且可编辑
	UPROPERTY(EditAnywhere, Category = "My Actor Properties | Vector", meta = (ClampMin = -5.0f, ClampMax = 5.0f, UIMin = -5.0f, UIMax = 5.0f))// UI控制实例的区间
	FVector TickPositionOffset; //每帧移动

	UPROPERTY(EditAnywhere, Category = "My Actor Properties | Vector")
	bool bShouldMove;

	UPROPERTY(EditInstanceOnly, Category = "My Actor Properties | Physics")
	FVector InitForce; // 初始力
	
	UPROPERTY(EditInstanceOnly, Category = "My Actor Properties | Physics")
	FVector InitTorque; // 初始力矩
	
	UPROPERTY(EditInstanceOnly, Category = "My Actor Properties | Physics")
	bool bAccelChange; //是否忽略质量


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	// DeltaTime是上一帧到这一帧的时间
	virtual void Tick(float DeltaTime) override;
};
