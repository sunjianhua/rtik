// Copyright (c) Henry Cooney 2017

// Provides animation utility functions (many blueprintable). All functions defined here are pure.

#pragma once

#include "CoreMinimal.h"
#include "AnimUtil.generated.h"

/**
 * 
 */
UCLASS()
class UE4IK_API UAnimUtil : public UObject
{
	GENERATED_BODY()
	
public:

	// Do a line trace from Source to Target. Code courtesy of Rama:
	// https://wiki.unrealengine.com/Trace_Functions
	static FORCEINLINE bool LineTrace(
		UWorld* World,
		AActor* ActorToIgnore,
		const FVector& Start,
		const FVector& End,
		FHitResult& HitOut,
		ECollisionChannel CollisionChannel = ECC_Pawn,
		bool ReturnPhysMat = false) 
	{ 
		FCollisionQueryParams TraceParams(FName(TEXT("Line Trace")), true, ActorToIgnore);
		TraceParams.bTraceComplex = true;
		//TraceParams.bTraceAsyncScene = true;
		TraceParams.bReturnPhysicalMaterial = ReturnPhysMat;
		
		//Ignore Actors
		TraceParams.AddIgnoredActor(ActorToIgnore);
		
		//Re-initialize hit info
		HitOut = FHitResult(ForceInit);
		
		//Trace!
		World->LineTraceSingleByChannel(
			HitOut,		//result
			Start,	//start
			End, //end
			CollisionChannel, //collision channel
			TraceParams
		);
 
		//Hit any Actor?
		return (HitOut.GetActor() != NULL);
	}
};
