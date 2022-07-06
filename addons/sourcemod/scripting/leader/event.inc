/*
 * =============================================================================
 * File:		  event.inc
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

void EventInit()
{
	EventsHook();
}

void EventsHook(bool unhook = false)
{
	if (unhook)
	{
		UnhookEvent("round_start", EventRoundStart);
		UnhookEvent("round_end", EventRoundEnd);
		UnhookEvent("player_death", EventPlayerDeath);		
		return;
	}

	HookEvent("round_start", EventRoundStart);
	HookEvent("round_end", EventRoundEnd);
	HookEvent("player_death", EventPlayerDeath);
}

public Action EventRoundStart(Handle event, const char[] name, bool dontBroadcast)
{
	VotesEventRoundStartEnd();
	MuteEventRoundStartEnd();
	BeaconEventRoundStartEnd();
	LeaderManagerEventRoundStartEnd();
}

public Action EventRoundEnd(Handle event, const char[] name, bool dontBroadcast)
{
	VotesEventRoundStartEnd();
	MuteEventRoundStartEnd();
	BeaconEventRoundStartEnd();
	LeaderManagerEventRoundStartEnd();
}

public Action EventPlayerDeath(Handle event, const char[] name, bool dontBroadcast)
{
	int client = GetClientOfUserId(GetEventInt(event, "userid"));
	LeaderManagerEventPlayerDeath(client);
}

public int ZR_OnClientInfected(int client, int attacker, bool motherInfect, bool respawnOverride, bool respawn)
{
	if(client == g_iLeaderClient)
	{
		CPrintToChatAll("%t", "The leader has been infected");
		if(g_bRemoveOnDie)
		{
			RemoveLeader(client);
		}
	}
	else if(client == g_iHelperClient)
	{
		CPrintToChatAll("%t", "The leader has been infected");
		if(g_bRemoveOnDie)
		{
			RemoveLeader(client);
		}
	}	
}