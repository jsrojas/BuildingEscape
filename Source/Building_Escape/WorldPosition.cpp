// Fill out your copyright notice in the Description page of Project Settings.

#include "WorldPosition.h"
#include "GameFramework/Actor.h"
#include "Math/Vector.h"

// Sets default values for this component's properties
UWorldPosition::UWorldPosition()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// Called when the game starts
void UWorldPosition::BeginPlay()
{
	Super::BeginPlay();

	// FString Log = TEXT("Hello!");
	// FString* PtrLog = &Log;

	// // Two ways to access members or functions of a variable through a pointer
	// (*PtrLog).Len();
	// PtrLog -> Len();

	// // How to print the value of an FString accessed through a pointer using the overloaded operator and de Dereferencing (same *)
	// UE_LOG(LogTemp, Warning, TEXT("%s"), **PtrLog);

	FString ObjectName = GetOwner()->GetName();

	// Approach Number 1 for Actor Location
	FString ObjectPosition = GetOwner()->GetActorLocation().ToString();

	UE_LOG(LogTemp, Warning, TEXT("%s position is: %s"), *ObjectName, *ObjectPosition);

	// Approach Number 2 for Actor Location
	//FString ObjectPosition = GetOwner()->GetActorTransform().GetLocation().ToString();
	
	// Approach Number 3 for Actor Location
	//FString ObjectPosition = GetOwner()->GetTargetLocation().ToString();

	// Approach Number 4 for Actor Location
	//FVector ObjectVector = GetOwner()->GetActorLocation();

	//UE_LOG(LogTemp, Warning, TEXT("Object is at coordinates X: % f, Y: % f, Z: % f"),ObjectVector.X, ObjectVector.Y, ObjectVector.Z);	
}

// Called every frame
void UWorldPosition::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}
