/*
 * =============================================================================
 * File:		  leader_ultimate.inc
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

/**
 * Supported games.
 */
enum Game
{
	Game_Unknown = -1,
	Game_CSS,
	Game_CSGO
}

/**
 * Current game.
 */
Game g_Game = Game_Unknown;
#pragma unused g_Game

/**
 * Updates g_game. Will log a warning if a unsupported game is detected.
 */
void UpdateGameFolder()
{
	char gameFolder[PLATFORM_MAX_PATH];
	GetGameFolderName(gameFolder, sizeof(gameFolder));
	
	if (StrEqual(gameFolder, "cstrike", false))
	{
		g_Game = Game_CSS;
		PrintToServer("Game detected: cstrike");
		return;
	}
	else if (StrEqual(gameFolder, "csgo", false))
	{
		g_Game = Game_CSGO;
		PrintToServer("Game detected: csgo");
		return;
	}
	
	LogError("Warning: Zombie:Reloaded doesn't support this game: %s", gameFolder);
	g_Game = Game_Unknown;
}

public void ColorStringToArray(const char[] sColorString, int aColor[3])
{
	char asColors[4][4];
	ExplodeString(sColorString, " ", asColors, sizeof(asColors), sizeof(asColors[]));

	aColor[0] = StringToInt(asColors[0]);
	aColor[1] = StringToInt(asColors[1]);
	aColor[2] = StringToInt(asColors[2]);
}

public bool IsValidGenericAdmin(int client) 
{ 
	return CheckCommandAccess(client, "generic_admin", ADMFLAG_GENERIC, false);
}

stock bool IsValidClient(int client, bool bzrAllowBots = false, bool bzrAllowDead = true)
{
	if (!(1 <= client <= MaxClients) || !IsClientInGame(client) || (IsFakeClient(client) && !bzrAllowBots) || IsClientSourceTV(client) || IsClientReplay(client) || (!bzrAllowDead && !IsPlayerAlive(client)))
		return false;
	return true;
}

stock int SortByPlayerName(int player1, int player2, const int[] array, Handle hndl)
{
	return strcmp(g_sClientNames[player1], g_sClientNames[player2], false);
}

stock int GetCtCount()
{
	int clients = 0;
	for (int i = 1; i <= MAXPLAYERS; i++)
	{
		if (IsValidClient(i) && GetClientTeam(i) == 3)
		{
			clients++;
		}
	}
	return clients;
}