#include <sourcemod>
#include <sdktools>
#include <sdkhooks>
 
public Plugin myinfo =
{
	name = "My First Plugin",
	author = "Me",
	description = "My first plugin ever",
	version = "1.0.0.0",
	url = "http://www.sourcemod.net/"
}

public OnPluginStart()
{
	HookEvent("round_start", onRoundStart);
	PrintToServer("OnPluginStart");
}

public onRoundStart(Event event, const char[] name, bool dontBroadcast)
{
	CreateTimer(25.0, onTimeEnd);
	PrintToServer("onRoundStart");
}

public Action onTimeEnd(Handle hTimer)
{
	PrintToServer("onTimeEnd");
	ServerCommand("quit");
}
