/*
 * =============================================================================
 * File:		  mute.inc
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

void MuteOnCommandsCreate()
{
	RegConsoleCmd("sm_lmute", Command_Mute);
}

public void MuteOnClientPutInServer(int client)
{
	if (IsValidClient(client) && g_bMuteStatus)
	{
		//BaseComm_SetClientMute(client, true);
		SetClientListeningFlags(client, VOICE_MUTED);
		g_bMuteClient[client] = true;
	}
	else if (IsValidClient(client) && !g_bMuteStatus)
	{
		g_bMuteClient[client] = false;
	}
}

public Action Command_Mute(int client, int args)
{
	if(IsValidClient(client) && (g_iLeaderClient == client || g_iHelperClient == client))
	{
		if(g_bMuteStatus)
		{
			RemoveMute();
		}
		else
		{
			AddMute(client);
		}
	}
	else
	{
		PrintToChat(client, "%t", "No Access");
	}
	return Plugin_Handled;
}

public void ToggleMute(int client)
{
	if(g_bMuteStatus) RemoveMute();
	else AddMute(client);
}

stock void AddMute(int client)
{
	if(!g_eCvarsList.g_bCVAR_DISABLE)
	{
		CReplyToCommand(client, "%t", "Leader is disabled");
		return;
	}

	if (!g_bMuteStatus)
	{
		g_bMuteStatus = true;
		for (int i = 1; i <= MaxClients; ++i)
		{
			if (IsValidClient(i) && i != g_iLeaderClient && i != g_iHelperClient)
			{
				SetClientListeningFlags(i, VOICE_MUTED);
				//BaseComm_SetClientMute(i, true);
				g_bMuteClient[i] = true;
			}
		}
		CreateTimer(g_eCvarsList.g_fCVAR_TIMER_REMOVE_MUTE, TimerRemoveMute, TIMER_DATA_HNDL_CLOSE|TIMER_FLAG_NO_MAPCHANGE);
		CPrintToChatAll("%t", "Mute All");
	}
}

public Action TimerRemoveMute(Handle sTime)
{
	if(g_bMuteStatus) RemoveMute();
}

stock void RemoveMute()
{
	// Is alltalk enabled?
	bool alltalk = GetConVarBool(FindConVar("sv_alltalk"));
	
	// Determine new voice flags based off of alltalk.
	int voiceflags = alltalk ? VOICE_SPEAKALL | VOICE_LISTENALL : VOICE_TEAM | VOICE_LISTENTEAM;
	
	if (g_bMuteStatus)
	{
		g_bMuteStatus = false;
		// x = Client index.
		for (int i = 1; i <= MaxClients + 1; ++i)
		{
			if (IsValidClient(i) && g_bMuteClient[i])
			{
				// Apply new voice flags.
				SetClientListeningFlags(i, voiceflags);
				//BaseComm_SetClientMute(i, false);
				g_bMuteClient[i] = false;
			}
		}
		CPrintToChatAll("%t", "Remove Mute All");
	}
}

public void MuteOnClientDisconnect(int client)
{
	if (g_iLeaderClient == client || g_iHelperClient == client)
	{
		RemoveMute();
	}
	else if (g_bMuteClient[client])
	{
		g_bMuteClient[client] = false;
	}

	g_iVoteCount[client] = 0;
}

void MuteOnMapEndStart()
{
	RemoveMute();
}

void MuteEventRoundStartEnd()
{
	RemoveMute();
}