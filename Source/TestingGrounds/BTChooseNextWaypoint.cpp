// Fill out your copyright notice in the Description page of Project Settings.

#include "BTChooseNextWaypoint.h"
#include "Runtime/AIModule/Classes/BehaviorTree/BlackboardComponent.h"
#include "Runtime/AIModule/Classes/AIController.h"

#include "PatrollingGuard.h"

void UBTChooseNextWaypoint::GetPatrolPoints(UBehaviorTreeComponent& OwnerComp)
{
	APatrollingGuard* Guard = Cast<APatrollingGuard>(OwnerComp.GetAIOwner()->GetPawn());

	if (Guard == nullptr) return;

	RoutePoints = Guard->GetPatrolPoints();
}

EBTNodeResult::Type UBTChooseNextWaypoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	GetPatrolPoints(OwnerComp);
	if(RoutePoints.Num() == 0)  return EBTNodeResult::Aborted;

	UBlackboardComponent* Blackboard = OwnerComp.GetBlackboardComponent();
	int32 Index = Blackboard->GetValueAsInt(NextWaypointIndex.SelectedKeyName);

	Blackboard->SetValueAsObject(Waypoint.SelectedKeyName, RoutePoints[Index]);
	Blackboard->SetValueAsInt(NextWaypointIndex.SelectedKeyName, (Index + 1) % RoutePoints.Num());
	
	return EBTNodeResult::Succeeded;
}
