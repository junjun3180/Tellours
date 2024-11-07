// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Tellours.h"
#include "BehaviorTree/BTDecorator.h"
#include "BTDecorator_BossIsInAttackRange.generated.h"

/**
 * 
 */
UCLASS()
class TELLOURS_API UBTDecorator_BossIsInAttackRange : public UBTDecorator
{
	GENERATED_BODY()
	
public:
	UBTDecorator_BossIsInAttackRange();

protected:
	// �Ÿ� �ȿ� ����� ���
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
};