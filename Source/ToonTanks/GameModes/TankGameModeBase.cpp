// Fill out your copyright notice in the Description page of Project Settings.


#include "TankGameModeBase.h"
#include "ToonTanks/Pawns/PawnTank.h"
#include "ToonTanks/Pawns/PawnTurret.h"
#include "Kismet/GameplayStatics.h"

#define OUT

void ATankGameModeBase::BeginPlay() {
    Super::BeginPlay();
    HandleGameStart();
}

void ATankGameModeBase::HandleGameStart() {
    TargetTurrets = GetTargetTurretCount();
    PlayerTank = Cast<APawnTank>(UGameplayStatics::GetPlayerPawn(this, 0));

    GameStart();
}


void ATankGameModeBase::ActorDied(AActor* DeadActor) {
    if (DeadActor == PlayerTank)
    {
        PlayerTank->HandleDestruction();
        HandleGameOver(false);
    }
    else if(APawnTurret* DestroyedTurret = Cast<APawnTurret>(DeadActor)){
        DestroyedTurret->HandleDestruction();

        if (--TargetTurrets <= 0)
        {
            HandleGameOver(true);            
        }      
    }   
}

void ATankGameModeBase::HandleGameOver(bool PlayerWon) {
    GameOver(PlayerWon);
}

int32 ATankGameModeBase::GetTargetTurretCount() {
    TArray<AActor*> TurretActors;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), APawnTurret::StaticClass(), OUT TurretActors);

    return TurretActors.Num();
}