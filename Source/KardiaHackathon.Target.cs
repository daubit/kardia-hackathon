// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;
using System.Collections.Generic;

public class KardiaHackathonTarget : TargetRules
{
    public KardiaHackathonTarget(TargetInfo Target) : base(Target)
    {
        Type = TargetType.Game;

        ExtraModuleNames.AddRange(new string[] { "KardiaHackathon" });

        //PublicDependencyModuleNames.AddRange(new string[] { "BlockchainLink" });
    }
}