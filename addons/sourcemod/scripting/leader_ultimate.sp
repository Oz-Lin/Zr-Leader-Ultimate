/*
 * =============================================================================
 * File:		  Leader_Ultimate
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

#pragma semicolon 1

#include <csgocolors_fix>
#include <sourcemod>
#include <sdktools>
#include <sdkhooks>
#include <zombiereloaded>
#include <leader>
#include <basecomm>
#include <cstrike>

#pragma newdecls required

#define PLUGIN_NAME           "Leader Ultimate OZIG Edition"
#define PLUGIN_AUTHOR         "Anubis, modified by Oz_Lin"
#define PLUGIN_DESCRIPTION    "Allows for a human to be a leader, and give them special functions with it."
#define PLUGIN_VERSION        "1.3"
#define PLUGIN_URL            "https://github.com/Oz-Lin"

#include "leader/global"
#include "leader/leader_ultimate"
#include "leader/cvars"
#include "leader/downloads"
#include "leader/commands"
#include "leader/votes"
#include "leader/menu"
#include "leader/event"
#include "leader/leader_manger"
#include "leader/glow"
#include "leader/sprite"
#include "leader/marker"
#include "leader/beacon"
#include "leader/mute"
#include "leader/leadertag"
#include "leader/api"

public Plugin myinfo =
{
	name = PLUGIN_NAME,
	author = PLUGIN_AUTHOR,
	description = PLUGIN_DESCRIPTION,
	version = PLUGIN_VERSION,
	url = PLUGIN_URL
};

public APLRes AskPluginLoad2(Handle myself, bool late, char[] error, int err_max)
{
	RegPluginLibrary("leader_ultimate");
	APILeaderInit();
	return APLRes_Success;
}

public void OnPluginStart()
{
	UpdateGameFolder();
	CvarsInit();
	CommandsInit();
	EventInit();
	DownloadsLoad();
}

public void OnMapStart()
{
	VotesOnMapEndStart();
	DownloadsLoad();
}

public void OnClientPutInServer(int client)
{
	MuteOnClientPutInServer(client);
}

public void OnClientDisconnect(int client)
{
	VoteOnClientDisconnect(client);
	LeaderManagerOnClientDisconnect(client);
	MuteOnClientDisconnect(client);
}

public void OnMapEnd()
{
	VotesOnMapEndStart();
	MuteOnMapEndStart();
	BeaconOnMapEndStart();
	LeaderManagerOnMapEndStart();
}
