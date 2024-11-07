// Fill out your copyright notice in the Description page of Project Settings.


#include "TOEnemySpawner.h"
#include "TOEnemy.h"
#include "TOEnemyStatComponent.h"
#include "TOItem.h"
#include "Level2Field1.h"
#include "EngineUtils.h"


// Sets default values
ATOEnemySpawner::ATOEnemySpawner()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	EnemySpawner = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ENEMYSPAWNER"));

	EnemySpawnTime = 3;
	NumberOfSpawn = 1;
	SpawnRadius = 400;
	SpawnNum = -1;
	SpawnCount = 1;
	KillCount = 0;
	MotherNPC = nullptr;
}

// Called when the game starts or when spawned
void ATOEnemySpawner::BeginPlay()
{
	Super::BeginPlay();

	GetWorld()->GetTimerManager().SetTimer(EnemySpawnDelay, FTimerDelegate::CreateLambda([&]() {
		for(int i=0; i< NumberOfSpawn; i++)
			EnemySpawn();
		GetWorld()->GetTimerManager().ClearTimer(EnemySpawnDelay);
		}), 2, false);
}

// Called every frame
void ATOEnemySpawner::Tick(float DeltaTime) 
{
	Super::Tick(DeltaTime);

}

/*
* 스폰 구현
*/
void ATOEnemySpawner::EnemySpawn()
{
	if (!(SpawnNum<0 || SpawnNum>SpawnCount)) Destroy();
	SpawnCount++;
	FVector2D RandXY = FMath::RandPointInCircle(SpawnRadius);
	ATOEnemy* SpawnedEnemy = (ATOEnemy*)GetWorld()->SpawnActor<ATOEnemy>(GetActorLocation() + FVector(RandXY.X, RandXY.Y, 88), FRotator::ZeroRotator);
	SpawnedEnemy->SetEnemyType(NewEnemyType);

	for (ALevel2Field1* Level2Field1 : TActorRange<ALevel2Field1>(GetWorld()))
	{
		if (Level2Field1->GetPhase2End())
		{
			SpawnedEnemy->GetEnemyStat()->SetAttack(20);
			SpawnedEnemy->GetEnemyAnim()->SetPhaseMontage(3);
		}
		else if (Level2Field1->GetPhase1End())
		{
			SpawnedEnemy->GetEnemyStat()->SetAttack(5);
			SpawnedEnemy->GetEnemyAnim()->SetPhaseMontage(2);
		}
	}

	SpawnedEnemy->EnemyStat->OnHPIsZero.AddLambda([this, SpawnedEnemy]() -> void {
		GetWorld()->GetTimerManager().SetTimer(SpawnedEnemy->EnemyDeadTimeHandle, FTimerDelegate::CreateLambda([&]() {SpawnedEnemy->Destroy();}), 2, false);
		GetWorld()->GetTimerManager().SetTimer(SpawnedEnemy->EnemySpawnTimeHandle, FTimerDelegate::CreateUObject(this, &ATOEnemySpawner::EnemySpawn), EnemySpawnTime, false);
		KillCount++;

		if (SpawnNum == KillCount && MotherNPC != nullptr)
			MotherNPC->SetQuestClear(true);

		if (SpawnNum == KillCount)
			AllKill.Broadcast();
		});
}

void ATOEnemySpawner::SetSpawnType(EnemyType Type)
{
	NewEnemyType = Type;
}

void ATOEnemySpawner::SetNumberOfSpawn(int32 Num)
{
	NumberOfSpawn = Num;
}

void ATOEnemySpawner::SetSpawnNum(int32 Num)
{
	SpawnNum = Num;
}

void ATOEnemySpawner::SetMotherNPC(ATONPC* TONPC)
{
	MotherNPC = TONPC;
}
