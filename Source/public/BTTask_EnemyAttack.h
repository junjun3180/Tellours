// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Tellours.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_EnemyAttack.generated.h"

/**
 * 
 */
UCLASS()
class TELLOURS_API UBTTask_EnemyAttack : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	UBTTask_EnemyAttack();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

protected:
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSecondes) override;

private:
	bool IsAttacking = false;
};
