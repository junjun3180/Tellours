// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Tellours.h"
#include "Components/ActorComponent.h"
#include "TOEnemyStatComponent.generated.h"


DECLARE_MULTICAST_DELEGATE(FOnHPisZeroDelegate);
DECLARE_MULTICAST_DELEGATE(FOnHPChanagedDelegate);


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class TELLOURS_API UTOEnemyStatComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTOEnemyStatComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	virtual void InitializeComponent() override;



/*
* ���� ����
*/
public:
	FOnHPisZeroDelegate OnHPIsZero;
	FOnHPChanagedDelegate OnHPChanged;

	void SetNewLevel(int32 NewLevel);
	void SetDamage(float NewDamage);
	void SetHP(float NewHP);
	void SetAttack(float NewAttack);
	float GetAttack();
	float GetHPRatio();

private:
	struct FTOEnemyData* CurrentStatData = nullptr;

	UPROPERTY(EditInstanceOnly, Category = Stat, Meta = (AllowPrivateAccess = true))
		int32 Level;

	UPROPERTY(Transient, VisibleInstanceOnly, Category = Stat, Meta = (AllowPrivateAccess = true))
		float CurrentHP;

	UPROPERTY(Transient, VisibleInstanceOnly, Category = Stat, Meta = (AllowPrivateAccess = true))
		float CurrentAttack;
};