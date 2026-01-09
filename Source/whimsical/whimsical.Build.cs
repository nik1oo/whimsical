using UnrealBuildTool;


public class whimsical : ModuleRules {
	public whimsical(ReadOnlyTargetRules Target) : base(Target) {
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput" });
		PrivateDependencyModuleNames.AddRange(new string[] {  });
		PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" }); } }

