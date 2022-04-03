/*
 * =============================================================================
 * File:		  votes.inc
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

void VotesOnCommandsCreate()
{
	RegConsoleCmd("sm_voteleader", Command_VoteLeader, "Usage: sm_voteleader <player>");
	RegConsoleCmd("sm_vl", Command_VoteLeader, "Usage: sm_vl <player>");
	RegConsoleCmd("sm_voteremoveleader", Command_VoteRemoveLeader, "Usage: sm_voteremoveleader <player>");
	RegConsoleCmd("sm_vrl", Command_VoteRemoveLeader, "Usage: sm_vrl <player>");
}

public Action Command_VoteLeader(int client, int argc)
{
	if(!IsValidClient(client)) return Plugin_Handled;

	if(!g_eCvarsList.g_bCVAR_ALLOW_VOTING)
	{
		CReplyToCommand(client, "%t", "Voting for leader is disabled");
		return Plugin_Handled;
	}

	if(IsValidClient(g_iLeaderClient))
	{
		CReplyToCommand(client, "%t", "There is already a leader");
		return Plugin_Handled;
	}

	if(GetClientTeam(client) == 2)
	{
		CReplyToCommand(client, "%t", "You are not a human only humans vote");
		return Plugin_Handled;
	}

	if(argc < 1)
	{
		Menu_VoteLeader_Remove(client);
		return Plugin_Handled;
	}

	else
	{
		char arg[64];
		GetCmdArg(1, arg, sizeof(arg));
		int target = FindTarget(client, arg, true, false);
		if (target == -1)
		{
			return Plugin_Handled;
		}
		VoteLeader(client, target);
	}

	return Plugin_Handled;
}

public Action VoteLeader(int client, int target)
{
	if(!g_eCvarsList.g_bCVAR_ALLOW_VOTING)
	{
		CReplyToCommand(client, "%t", "Voting for leader is disabled");
		return Plugin_Handled;
	}

	if(IsValidClient(g_iLeaderClient))
	{
		CReplyToCommand(client, "%t", "There is already a leader");
		return Plugin_Handled;
	}

	if(GetClientFromSerial(g_iVotedFor[client]) == target)
	{
		CReplyToCommand(client, "%t", "You ve already voted for this person");
		return Plugin_Handled;
	}

	if(GetClientTeam(target) == 2)
	{
		CReplyToCommand(client, "%t", "You have to vote for a human");
		return Plugin_Handled;
	}

	if(GetClientTeam(client) == 2)
	{
		CReplyToCommand(client, "%t", "You are not a human only humans vote");
		return Plugin_Handled;
	}

	if(GetClientFromSerial(g_iVotedFor[client]) != 0)
	{
		if(IsValidClient(GetClientFromSerial(g_iVotedFor[client]))) {
			g_iVoteCount[GetClientFromSerial(g_iVotedFor[client])]--;
		}
	}
	g_iVoteCount[target]++;
	g_iVotedFor[client] = GetClientSerial(target);
	CPrintToChatAll("%t", "Has voted for", client, target, g_iVoteCount[target], GetCtCount()/5);

	if(g_iVoteCount[target] >= GetCtCount()/5)
	{
		SetLeader(target);
		CPrintToChatAll("%t", "Has been voted to be the new leader", target);
		LeaderMenu(target);
	}

	return Plugin_Handled;
}

public Action Command_VoteRemoveLeader(int client, int argc)
{
	if(!IsValidClient(client)) return Plugin_Handled;

	if(!g_eCvarsList.g_bCVAR_ALLOW_VOTING)
	{
		CReplyToCommand(client, "%t", "Voting to remove leader is disabled");
		return Plugin_Handled;
	}

	if(!IsValidClient(g_iLeaderClient))
	{
		CReplyToCommand(client, "%t", "No current leader");
		return Plugin_Handled;
	}

	if(GetClientTeam(client) == 2)
	{
		CReplyToCommand(client, "%t", "You are not a human only humans vote");
		return Plugin_Handled;
	}

	if(argc < 1)
	{
		Menu_VoteLeader_Remove(client, true);
		return Plugin_Handled;
	}

	else
	{
		char arg[64];
		GetCmdArg(1, arg, sizeof(arg));
		int target = FindTarget(client, arg, true, false);
		if (target == -1)
		{
			return Plugin_Handled;
		}
		VoteRemoveLeader(client, target);
	}
	return Plugin_Handled;
}

public Action VoteRemoveLeader(int client, int target)
{
	if(!g_eCvarsList.g_bCVAR_ALLOW_VOTING)
	{
		CReplyToCommand(client, "%t", "Voting for leader is disabled");
		return Plugin_Handled;
	}

	if(!IsValidClient(g_iLeaderClient))
	{
		CReplyToCommand(client, "%t", "No current leader");
		return Plugin_Handled;
	}

	if(GetClientFromSerial(g_iVotedRemovedFor[client]) == target)
	{
		CReplyToCommand(client, "%t", "You ve already voted for this person");
		return Plugin_Handled;
	}

	if(GetClientTeam(target) == 2)
	{
		CReplyToCommand(client, "%t", "You have to vote for a human");
		return Plugin_Handled;
	}

	if(GetClientTeam(client) == 2)
	{
		CReplyToCommand(client, "%t", "You are not a human only humans vote");
		return Plugin_Handled;
	}

	if(g_iLeaderClient != target)
	{
		CReplyToCommand(client, "%t", "This Player is not the current leader");
		return Plugin_Handled;
	}

	if(GetClientFromSerial(g_iVotedRemovedFor[client]) != 0)
	{
		if(IsValidClient(GetClientFromSerial(g_iVotedRemovedFor[client]))) {
			g_iVoteRemoveCount[GetClientFromSerial(g_iVotedRemovedFor[client])]--;
		}
	}
	g_iVoteRemoveCount[target]++;
	g_iVotedRemovedFor[client] = GetClientSerial(target);
	CPrintToChatAll("%t", "Has voted for Remove", client, target, g_iVoteRemoveCount[target], GetCtCount()/5);

	if(g_iVoteRemoveCount[target] >= GetCtCount()/5)
	{
		RemoveTheLeader(target, 0);
	}

	return Plugin_Handled;
}

void VotesOnMapEndStart()
{
	for (int i = 1; i <= MAXPLAYERS; i++)
	{
		g_iVotedFor[i] = -1;
		g_iVotedRemovedFor[i] = -1;
		g_iVoteCount[i] = 0;
		g_iVoteRemoveCount[i] = 0;
	}
}

void VotesEventRoundStartEnd()
{
	for (int i = 1; i <= MAXPLAYERS; i++)
	{
		g_iVotedFor[i] = -1;
		g_iVotedRemovedFor[i] = -1;
		g_iVoteCount[i] = 0;
		g_iVoteRemoveCount[i] = 0;
	}
}

void Menu_VoteLeader_Remove(int client, bool b_RemoveLeader = false)
{
	if(!IsValidClient(client))
	{
		return;
	}

	Menu VoteLeaderRemove = new Menu(MenuHandler_VoteLeaderRemove);
	SetGlobalTransTarget(client);
	if (g_Game == Game_CSGO)
	{
		SendConVarValue(client, CVAR_MP_MAXMONEY, "0");
		SendConVarValue(client, CVAR_SV_DISABLE_RADAR, "1");
	}

	char m_title[LENGTH_MAX_TEXT];
	char strClientID[LENGTH_MIN_TEXT];
	char strClientName[LENGTH_MED_TEXT];

	if (b_RemoveLeader)
	{

		Format(m_title, sizeof(m_title), "%t\n ", "Menu Vote Remove Leader");

		VoteLeaderRemove.SetTitle(m_title);
		VoteLeaderRemove.ExitButton = true;

		if(IsValidClient(g_iLeaderClient))
		{
			IntToString(GetClientUserId(g_iLeaderClient), strClientID, sizeof(strClientID));
			FormatEx(strClientName, sizeof(strClientName), "%N - %t", g_iLeaderClient, "Players Menu", g_iVoteRemoveCount[g_iLeaderClient], GetCtCount()/5);
			VoteLeaderRemove.AddItem(strClientID, strClientName);
		}
	}
	else
	{
		int[] alphabetClients = new int[MaxClients+1];

		Format(m_title, sizeof(m_title), "%t\n ", "Leader Menu Vote Player");

		VoteLeaderRemove.SetTitle(m_title);
		VoteLeaderRemove.ExitButton = true;

		for (int aClient = 1; aClient <= MaxClients; aClient++)
		{
			if (IsValidClient(aClient) && GetClientTeam(aClient) == 3)
			{
				alphabetClients[aClient] = aClient;
				GetClientName(alphabetClients[aClient], g_sClientNames[alphabetClients[aClient]], sizeof(g_sClientNames[]));
			}
		}

		SortCustom1D(alphabetClients, MaxClients, SortByPlayerName);

		for (int i = 0; i < MaxClients; i++)
		{
			if (alphabetClients[i]!=0) 
			{
				IntToString(GetClientUserId(alphabetClients[i]), strClientID, sizeof(strClientID));
				FormatEx(strClientName, sizeof(strClientName), "%N - %t", alphabetClients[i], "Players Menu", g_iVoteCount[i], GetCtCount()/5);
				VoteLeaderRemove.AddItem(strClientID, strClientName);
			}
		}
	}
	if (VoteLeaderRemove.ItemCount == 0) 
	{
		delete(VoteLeaderRemove);
	}
	else
	{
		VoteLeaderRemove.ExitBackButton = true;
		//VoteLeaderRemove.ExitBackButton = (VoteLeaderRemove.ItemCount > 7);
		DisplayMenu(VoteLeaderRemove, client, MENU_TIME_FOREVER);
	}
}

public int MenuHandler_VoteLeaderRemove(Menu VoteLeaderRemove, MenuAction action, int client, int itemNum)
{
	if (action == MenuAction_End)
	{
		delete VoteLeaderRemove;
	}

	if (action == MenuAction_Select)
	{
		char info[32], name[32];
		int userid, target;
		
		GetMenuItem(VoteLeaderRemove, itemNum, info, sizeof(info), _, name, sizeof(name));
		userid = StringToInt(info);

		if ((target = GetClientOfUserId(userid)) == 0)
		{
			PrintToChat(client, "[SM] %s", "Player no longer available");
		}
		else
		{
			if(IsValidClient(g_iLeaderClient)) VoteRemoveLeader(client, target);
			else VoteLeader(client, target);
		}
	}

	if (action == MenuAction_Cancel && itemNum != MenuCancel_ExitBack)
	{
		if (IsValidClient(client))
		{
			SendConVarValue(client, CVAR_MP_MAXMONEY, g_eCvarsList.g_sCVAR_VALUE_MP_MAXMONEY);
			SendConVarValue(client, CVAR_SV_DISABLE_RADAR, g_eCvarsList.g_sCVAR_VALUE_SV_DISABLE_RADAR);
		}
	}
	return 0;
}

public void VoteOnClientDisconnect(int client)
{
	g_iVoteCount[client] = 0;
}