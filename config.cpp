class CfgPatches
{
	class DayZ_Expansion_AI_Aiming_scripts
	{
		requiredAddons[] = {"DayZExpansion_AI_Scripts"};
	};
};
class CfgMods
{
	class DayZ_Expansion_AI_Aiming
	{
		action = "";
		hideName = 0;
		hidePicture = 0;
		name = "AI Aiming";
		credits = "DayZ Expansion and dolphin";
		author = "Dolphin";
		authorID = "";
		version = "0.1";
		extra = 0;
		type = "servermod";
		dependencies[] = {"World"};
		class defs
		{
			class worldScriptModule
			{
				value = "";
				files[] = {"dolphin/DayZ-Expansion-AI-Aiming/Scripts/4_World"};
			};
		};
	};
};
