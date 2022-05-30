/*
 * =============================================================================
 * File:		  leadertag.inc
 * Type:		  Base
 * Description:   Plugin's base file.
 *
 * Copyright (C)   Anubis Edition. All rights reserved.
 * =============================================================================
 *
 * This program is free software; you can redistribute it and/or modify it under
 * the terms of the GNU General Public License, version 3.0, as published by the
 * Free Software Foundation.
 * 
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more
 * details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * As a special exception, AlliedModders LLC gives you permission to link the
 * code of this program (as well as its derivative works) to "Half-Life 2," the
 * "Source Engine," the "SourcePawn JIT," and any Game MODs that run on software
 * by the Valve Corporation.  You must obey the GNU General Public License in
 * all respects for all other code used.  Additionally, AlliedModders LLC grants
 * this exception to all derivative works.  AlliedModders LLC defines further
 * exceptions, found in LICENSE.txt (as of this writing, version JULY-31-2007),
 * or <http://www.sourcemod.net/license.php>.
 */

#define MAXSIZECLANTAG 16

char g_sClanTag[MAXPLAYERS+1][MAXSIZECLANTAG];

public Action OnClientSayCommand(int client, const char[] command, const char[] sArgs)
{
	if(client >= 1 && IsValidClient(client) && (g_iLeaderClient == client || g_iHelperClient == client))
	{
		char LeaderText[LENGTH_MIN_LINE];
		Format(LeaderText, sizeof(LeaderText), sArgs);
		StripQuotes(LeaderText);
		if(LeaderText[0] == '/' || LeaderText[0] == '@' || strlen(LeaderText) == 0 || IsChatTrigger())
		{
			return Plugin_Handled;
		}
		if(IsValidClient(client))
		{
			CPrintToChatAll("%t", "Leader Chat", client, LeaderText);
			return Plugin_Handled;
		}
	}
	return Plugin_Continue;
}

public void OnAllPluginsLoaded()
{
	CreateTimer(1.0, Timer_CheckDelay, _, TIMER_REPEAT);
}

//Get Client ClanTag on Connect
public void Event_PlayerConnectFull(Event hEvent, const char[] sName, bool bDontBroadcast)
{
	int client = GetClientOfUserId(GetEventInt(hEvent, "userid"));
	
	CS_GetClientClanTag(client, g_sClanTag[client], MAXSIZECLANTAG);
}

//Get Client ClanTag on Change
public void OnClientSettingsChanged(int client)
{
	if(IsValidClient(client)) CS_GetClientClanTag(client, g_sClanTag[client], MAXSIZECLANTAG);
}

public Action Timer_CheckDelay(Handle timer)
{

	for (int i = 0; i < MaxClients; i++)
	{
		if(IsValidClient(i))
		{
			CheckTag(i);
		}
	}
}

public void CheckTag(int client)
{
	if(IsValidClient(client))
	{
		char tag[40];
		if(Leader_CurrentLeader() == client)
		{
			tag = "[Leader]"; //hard-coded this for now
			CS_SetClientClanTag(client, tag);
		}
	}
}

public void RemoveTag(int client)
{
	if(IsValidClient(client))
	{
		//char tag[40];
		//tag = ""; //hard-coded this for now
		CS_SetClientClanTag(client, g_sClanTag[client]);
	}
}