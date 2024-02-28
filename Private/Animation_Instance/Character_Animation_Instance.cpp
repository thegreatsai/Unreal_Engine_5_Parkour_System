// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation_Instance/Character_Animation_Instance.h"
#include "Character/Technical_AnimatorCharacter.h"
#include "Components/Custom_Movement_Component.h"
#include "Kismet/KismetMathLibrary.h"
#include "Debug/DebugHelper.h"


void UCharacter_Animation_Instance::NativeInitializeAnimation()
{
    Super::NativeInitializeAnimation();

    Climbing_System_Character = Cast<ATechnical_AnimatorCharacter>(TryGetPawnOwner());

    if(Climbing_System_Character)
    {
        
        Custom_Movement_Component = Climbing_System_Character->Get_Custom_Movement_Component();
    }
}

void UCharacter_Animation_Instance::NativeUpdateAnimation(float DeltaSeconds)
{
    Super::NativeUpdateAnimation(DeltaSeconds);

    if(!Climbing_System_Character || !Custom_Movement_Component) return;

    Get_Ground_Speed();
    Get_Air_Speed();
    Get_Should_Move();
    Get_Is_Falling();
    Get_Is_Climbing();
    Get_Climb_Velocity();
    Get_Is_Taking_Cover();
    Get_Take_Cover_Velocity();
}

void UCharacter_Animation_Instance::Get_Ground_Speed()
{
   Ground_Speed = UKismetMathLibrary::VSizeXY(Climbing_System_Character->GetVelocity());
}

void UCharacter_Animation_Instance::Get_Air_Speed()
{
   Air_Speed = Climbing_System_Character->GetVelocity().Z;
}

void UCharacter_Animation_Instance::Get_Should_Move()
{
    bShould_Move =
    Custom_Movement_Component->GetCurrentAcceleration().Size()>0 && 
    Ground_Speed>5.f &&
    !bIs_Falling;
}

void UCharacter_Animation_Instance::Get_Is_Falling()
{
    bIs_Falling = Custom_Movement_Component->IsFalling();
}

void UCharacter_Animation_Instance::Get_Is_Climbing()
{
    bIs_Climbing = Custom_Movement_Component->Is_Climbing();
}

void UCharacter_Animation_Instance::Get_Climb_Velocity()
{
  Climb_Velocity = Custom_Movement_Component->Get_Unrotated_Climb_Velocity();
}

void UCharacter_Animation_Instance::Get_Is_Taking_Cover()
{
    bIs_Taking_Cover = Custom_Movement_Component->Is_Taking_Cover();
}

void UCharacter_Animation_Instance::Get_Take_Cover_Velocity()
{
    Take_Cover_Velocity = Custom_Movement_Component->Get_Unrotated_Take_Cover_Velocity();
}

void UCharacter_Animation_Instance::Set_Parkour_State_Implementation(const FGameplayTag &New_Parkour_State)
{
   Parkour_State = New_Parkour_State;
}

void UCharacter_Animation_Instance::Set_Parkour_Action_Implementation(const FGameplayTag &New_Parkour_Action)
{
    Parkour_Action = New_Parkour_Action;
}

void UCharacter_Animation_Instance::Set_Climb_Style_Implementation(const FGameplayTag &New_Climb_Style)
{
   Parkour_Climb_Style = New_Climb_Style;
}

void UCharacter_Animation_Instance::Set_Climb_Direction_Implementation(const FGameplayTag &New_Climb_Direction)
{
    Parkour_Direction = New_Climb_Direction;

    if(Parkour_Direction == FGameplayTag::RequestGameplayTag(FName(TEXT("Parkour.Direction.Right"))))
    Debug::Print("Parkour_Direction_Right");

    else if((Parkour_Direction == FGameplayTag::RequestGameplayTag(FName(TEXT("Parkour.Direction.Left")))))
    Debug::Print("Parkour_Direction_Left");

    if(Parkour_Direction == FGameplayTag::RequestGameplayTag(FName(TEXT("Parkour.Direction.None"))))
     Debug::Print("Parkour_Direction_None");
}
