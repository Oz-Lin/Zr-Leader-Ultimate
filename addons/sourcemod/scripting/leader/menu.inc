/*
 * =============================================================================
 * File:		  menu.inc
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

void MenuOnCommandsCreate()
{
	RegConsoleCmd("sm_leader", Command_Leader, "Opens Leader main menu.");
	RegConsoleCmd("sm_le", Command_Leader, "Opens Leader main menu.");
	RegConsoleCmd("sm_l", Command_Leader, "Opens Leader main menu.");
}

void HookShortcutOnCommandsCreate()
{
	AddCommandListener(QuickCommand, "+lookatweapon");
}

public Action Command_Leader(int client, int args)
{
	if(!IsValidClient(client)) return Plugin_Handled;

	if(!g_eCvarsList.g_bCVAR_DISABLE)
	{
		CReplyToCommand(client, "%t", "Leader is disabled");
		return Plugin_Handled;
	}

	if(GetClientTeam(client) == 2)
	{
		CReplyToCommand(client, "%t", "You are not a human");
		return Plugin_Handled;
	}
	else if(IsValidGenericAdmin(client) && g_eCvarsList.g_bCVAR_ALLOW_ADMIN_LEADER)
	{
		if(args == 1)
		{
			char arg1[65];
			GetCmdArg(1, arg1, sizeof(arg1));
			int target = FindTarget(client, arg1, false, false);
			if (target == -1)
			{
				return Plugin_Handled;
			}

			if(target == g_iLeaderClient)
			{
				LeaderMenu(target);
			}
			else
			{
				if(IsValidClient(target))
				{
					SetLeader(target);
					CPrintToChatAll("%t", "The new leader", target);
					CPrintToChat(target, "%t", "You are now the leader");
					LeaderMenu(target);
				}
				else
				{
					CReplyToCommand(client, "%t", "The target has to be alive");
				}
			}
		}
		else if(args == 0)
		{
			if(client == g_iLeaderClient)
			{
				LeaderMenu(client);
				return Plugin_Handled;
			}
			if(IsValidClient(client))
			{
				SetLeader(client);
				CPrintToChatAll("%t", "The new leader", client);
				CPrintToChat(client, "%t", "You are now the leader");
				LeaderMenu(client);
			}
			else
			{
				CReplyToCommand(client, "%t", "The target has to be alive");
			}
		}
		else if(client == g_iLeaderClient)
		{
			LeaderMenu(client);
			return Plugin_Handled;
		}
		else
		{
			CReplyToCommand(client, "%t", "Usage sm_leader");
		}
	}
	else if(client == g_iLeaderClient || client == g_iHelperClient)
	{
		LeaderMenu(client);
	}
	else
	{
		PrintToChat(client, "%t", "No Access");
	}
	return Plugin_Handled;
}

public Action QuickCommand(int client, const char[] command, int argc)
{
	if(client == g_iLeaderClient || client == g_iHelperClient)
	{
		//if(g_bShortcut[client])
		//{
		g_iButtoncount[client]++;
		CreateTimer(1.2, ResetButtonPressed, client);
		//}

		if (g_iButtoncount[client] >= 2)
		{
			if(client == g_iLeaderClient || client == g_iHelperClient)
			{
				MarkerMenu(client);
			}
		}
	}
	return Plugin_Continue;
}

public Action ResetButtonPressed(Handle timer, any client)
{
	g_iButtoncount[client] = 0;
}

void LeaderMenu(int client)
{
	if(!IsValidClient(client))
	{
		return;
	}

	Menu m_LeaderMenu = new Menu(LeaderMenu_Handler);
	SetGlobalTransTarget(client);
	if (g_Game == Game_CSGO)
	{
		//SendConVarValue(client, CVAR_MP_MAXMONEY, "0");
		//SendConVarValue(client, CVAR_SV_DISABLE_RADAR, "1");
	}

	char s_Title[LENGTH_MIN_LINE];
	char s_Sprite[LENGTH_MED_TEXT];
	char s_Marker[LENGTH_MED_TEXT];
	char s_Beacon[LENGTH_MED_TEXT];
	char s_Glow[LENGTH_MED_TEXT];
	char s_Muteall[LENGTH_MED_TEXT];
	char s_SelectHelper[LENGTH_MED_TEXT];
	char s_SRemoveHelper[LENGTH_MED_TEXT];
	char s_TSprite[LENGTH_MED_TEXT];
	char s_TMarker[LENGTH_MED_TEXT];
	char s_TBeacon[LENGTH_MED_TEXT];
	char s_TGlow[LENGTH_MED_TEXT];
	char s_TBMute[LENGTH_MED_TEXT];
	char s_THelper[LENGTH_MED_TEXT];
	char s_Resign[LENGTH_MED_TEXT];
	char s_LeaderLaser[LENGTH_MED_TEXT];

	switch (g_iCurrentSprite[client])
	{
		case 0:
		Format(s_TSprite, sizeof(s_TSprite), "%t", "Defend");
		case 1:
		Format(s_TSprite, sizeof(s_TSprite), "%t", "Follow");
		default:
		Format(s_TSprite, sizeof(s_TSprite), "%t", "None");
	}

	if(g_iMarkerCount[client] != 0) Format(s_TMarker, sizeof(s_TMarker), "%i", g_iMarkerCount[client]);
	else Format(s_TMarker, sizeof(s_TMarker), "%t", "No");
	
	if(g_iBeaconSerial[client] != 0) Format(s_TBeacon, sizeof(s_TBeacon), "%t", "Yes");
	else Format(s_TBeacon, sizeof(s_TBeacon), "%t", "No");

	if(g_iPlayerModelsIndex[client] != -1) Format(s_TGlow, sizeof(s_TGlow), "%t", "Yes");
	else Format(s_TGlow, sizeof(s_TGlow), "%t", "No");

	if (g_bMuteStatus) Format(s_TBMute, sizeof(s_TBMute), "%t", "Yes");
	else Format(s_TBMute, sizeof(s_TBMute), "%t", "No");
	
	if (IsValidClient(g_iHelperClient))
	{
		Format(s_THelper, sizeof(s_THelper), "%N", g_iHelperClient);
		Format(s_SRemoveHelper, sizeof(s_SRemoveHelper), "%t", "Remove Helper");
	}
	else Format(s_THelper, sizeof(s_THelper), "%t", "None");

	Format(s_Title, sizeof(s_Title), "%t", "Leader Menu Title", s_TSprite, s_TMarker, s_TBeacon, s_TGlow, s_TBMute, s_THelper);
	Format(s_Sprite, sizeof(s_Sprite), "%t", "Sprite Menu");
	Format(s_Marker, sizeof(s_Marker), "%t", "Marker Menu");
	Format(s_Beacon, sizeof(s_Beacon), "%t", "Toggle Beacon");
	Format(s_Glow, sizeof(s_Glow), "%t", "Toggle Glow");
	Format(s_Muteall, sizeof(s_Muteall), "%t", "Toggle Mute");
	Format(s_SelectHelper, sizeof(s_SelectHelper), "%t", "Select Helper");
	Format(s_Resign, sizeof(s_Resign), "%t", "Resign from Leader");
	Format(s_LeaderLaser, sizeof(s_LeaderLaser), "%t", "Draw Leader Laser");

	m_LeaderMenu.SetTitle(s_Title);
	m_LeaderMenu.AddItem("m_sprite", s_Sprite);
	m_LeaderMenu.AddItem("m_marker", s_Marker);
	m_LeaderMenu.AddItem("m_beacon", s_Beacon);
	m_LeaderMenu.AddItem("m_glow", s_Glow);
	m_LeaderMenu.AddItem("m_muteall", s_Muteall);
	if (g_iLeaderClient == client && !IsValidClient(g_iHelperClient)) m_LeaderMenu.AddItem("m_selecthelper", s_SelectHelper);
	if (IsValidClient(g_iHelperClient)) m_LeaderMenu.AddItem("m_removehelper", s_SRemoveHelper);
	m_LeaderMenu.AddItem("m_resign", s_Resign);
	m_LeaderMenu.AddItem("m_leaderlaser", s_LeaderLaser);

	m_LeaderMenu.ExitButton = true;

	m_LeaderMenu.Display(client, MENU_TIME_FOREVER);
}

public int LeaderMenu_Handler(Handle m_LeaderMenu, MenuAction action, int client, int itemNum)
{
	if(action == MenuAction_End)
	{
		delete m_LeaderMenu;
	}

	if(IsValidClient(client) && (g_iLeaderClient == client || g_iHelperClient == client))
	{
		if(action == MenuAction_Select)
		{
			char info[32];
			GetMenuItem(m_LeaderMenu, itemNum, info, sizeof(info));

			// Menu Leader
			if(StrEqual(info, "m_sprite"))
			{
				SpriteMenu(client);
			}
			if(StrEqual(info, "m_marker"))
			{
				MarkerMenu(client);
			}
			if(StrEqual(info, "m_beacon"))
			{
				PerformBeacon(client);
				LeaderMenu(client);
			}
			if(StrEqual(info, "m_glow"))
			{
				PerformGlow(client);
				LeaderMenu(client);
			}
			if(StrEqual(info, "m_muteall"))
			{
				ToggleMute(client);
				LeaderMenu(client);
			}
			if(StrEqual(info, "m_selecthelper"))
			{
				Menu_SelectHelperLeader(client);
			}
			if(StrEqual(info, "m_removehelper"))
			{
				RemoveLeader(g_iHelperClient);
				LeaderMenu(client);
			}
			if(StrEqual(info, "m_resign"))
			{
				RemoveLeader(client);
				CPrintToChatAll("%t", "Resigned from being leader", client);
				action = MenuAction_Cancel;
			}
			if(StrEqual(info, "m_leaderlaser"))
			{
				CPrintToChat(client, "%t", "How to bind key for leader laser");
				LeaderMenu(client);
			}
		}
		if (itemNum == MenuCancel_ExitBack)
		{
			LeaderMenu(client);
		}
	}
	else if(IsValidClient(client) && (g_iLeaderClient != client || g_iHelperClient != client))
	{
		
		if (itemNum == MenuCancel_ExitBack || action == MenuAction_Select || action == MenuAction_Cancel)
		{
			if (IsValidClient(client) && g_Game == Game_CSGO)
			{
				//SendConVarValue(client, CVAR_MP_MAXMONEY, g_eCvarsList.g_sCVAR_VALUE_MP_MAXMONEY);
				//SendConVarValue(client, CVAR_SV_DISABLE_RADAR, g_eCvarsList.g_sCVAR_VALUE_SV_DISABLE_RADAR);
			}			
		}
		else action = MenuAction_Cancel;
		
	}
	if (action == MenuAction_Cancel && itemNum != MenuCancel_ExitBack)
	{
		if (IsValidClient(client) && g_Game == Game_CSGO)
		{
			//SendConVarValue(client, CVAR_MP_MAXMONEY, g_eCvarsList.g_sCVAR_VALUE_MP_MAXMONEY);
			//SendConVarValue(client, CVAR_SV_DISABLE_RADAR, g_eCvarsList.g_sCVAR_VALUE_SV_DISABLE_RADAR);
		}
	}
	return 0;
}

void Menu_SelectHelperLeader(int client)
{
	if(!IsValidClient(client))
	{
		return;
	}

	Menu LeaderHelper = new Menu(MenuHandler_LeaderHelper);
	SetGlobalTransTarget(client);
	if (g_Game == Game_CSGO)
	{
		//SendConVarValue(client, CVAR_MP_MAXMONEY, "0");
		//SendConVarValue(client, CVAR_SV_DISABLE_RADAR, "1");
	}

	char m_title[LENGTH_MAX_TEXT];
	char strClientID[LENGTH_MIN_TEXT];
	char strClientName[LENGTH_MED_TEXT];

	int[] alphabetClients = new int[MaxClients+1];

	Format(m_title, sizeof(m_title), "%t\n ", "Helper Select Player");

	LeaderHelper.SetTitle(m_title);
	LeaderHelper.ExitButton = true;

	for (int aClient = 1; aClient <= MaxClients; aClient++)
	{
		if (IsValidClient(aClient) && GetClientTeam(aClient) == 3 && aClient != client)
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
			FormatEx(strClientName, sizeof(strClientName), "%N", alphabetClients[i]);
			LeaderHelper.AddItem(strClientID, strClientName);
		}
	}

	if (LeaderHelper.ItemCount == 0) 
	{
		delete(LeaderHelper);
	}
	else
	{
		LeaderHelper.ExitBackButton = (LeaderHelper.ItemCount > 7);
		DisplayMenu(LeaderHelper, client, MENU_TIME_FOREVER);
	}
}

public int MenuHandler_LeaderHelper(Menu LeaderHelper, MenuAction action, int client, int itemNum)
{
	if (action == MenuAction_End)
	{
		delete LeaderHelper;
	}
	if(IsValidClient(client) && g_iLeaderClient == client)
	{
		if (action == MenuAction_Select)
		{
			char info[32], name[32];
			int userid, target;
	
			GetMenuItem(LeaderHelper, itemNum, info, sizeof(info), _, name, sizeof(name));
			userid = StringToInt(info);

			if ((target = GetClientOfUserId(userid)) == 0)
			{
				PrintToChat(client, "[SM] %s", "Player no longer available");
			}
			else
			{
				SetLeaderHelper(target);
			}
			if (itemNum == MenuCancel_ExitBack)
			{
				LeaderMenu(client);
			}
		}
	}
	else if(IsValidClient(client) && g_iLeaderClient != client)
	{
		
		if (itemNum == MenuCancel_ExitBack || action == MenuAction_Select || action == MenuAction_Cancel)
		{
			if (IsValidClient(client) && g_Game == Game_CSGO)
			{
				//SendConVarValue(client, CVAR_MP_MAXMONEY, g_eCvarsList.g_sCVAR_VALUE_MP_MAXMONEY);
				//SendConVarValue(client, CVAR_SV_DISABLE_RADAR, g_eCvarsList.g_sCVAR_VALUE_SV_DISABLE_RADAR);
			}			
		}
		else action = MenuAction_Cancel;
		
	}
	if (action == MenuAction_Cancel && itemNum != MenuCancel_ExitBack)
	{
		if (IsValidClient(client) && g_Game == Game_CSGO)
		{
			//SendConVarValue(client, CVAR_MP_MAXMONEY, g_eCvarsList.g_sCVAR_VALUE_MP_MAXMONEY);
			//SendConVarValue(client, CVAR_SV_DISABLE_RADAR, g_eCvarsList.g_sCVAR_VALUE_SV_DISABLE_RADAR);
		}
	}
	return 0;
}