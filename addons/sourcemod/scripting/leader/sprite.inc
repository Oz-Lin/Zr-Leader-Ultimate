/*
 * =============================================================================
 * File:		  sprite.inc
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

void SpriteMenu(int client)
{
	if(!IsValidClient(client))
	{
		return;
	}

	Menu m_SpriteMenu = new Menu(SpriteMenu_Handler);
	SetGlobalTransTarget(client);
	if (g_Game == Game_CSGO)
	{
		SendConVarValue(client, CVAR_MP_MAXMONEY, "0");
		SendConVarValue(client, CVAR_SV_DISABLE_RADAR, "1");
	}

	char s_Title[LENGTH_MIN_LINE];
	char s_None[LENGTH_MED_TEXT];
	char s_Defend[LENGTH_MED_TEXT];
	char s_Follow[LENGTH_MED_TEXT];
	char s_TSprite[LENGTH_MED_TEXT];
	char s_TMarker[LENGTH_MED_TEXT];
	char s_TBeacon[LENGTH_MED_TEXT];
	char s_TGlow[LENGTH_MED_TEXT];
	char s_TBMute[LENGTH_MED_TEXT];
	char s_THelper[LENGTH_MED_TEXT];

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

	if (IsValidClient(g_iHelperClient)) Format(s_THelper, sizeof(s_THelper), "%N", g_iHelperClient);
	else Format(s_THelper, sizeof(s_THelper), "%t", "None");

	Format(s_Title, sizeof(s_Title), "%t", "Leader Menu Title Sprite", s_TSprite, s_TMarker, s_TBeacon, s_TGlow, s_TBMute, s_THelper);
	Format(s_None, sizeof(s_None), "%t", "No Sprite");
	Format(s_Defend, sizeof(s_Defend), "%t", "Defend Here");
	Format(s_Follow, sizeof(s_Follow), "%t", "Follow Me");

	m_SpriteMenu.SetTitle(s_Title);
	m_SpriteMenu.AddItem("m_none", s_None);
	m_SpriteMenu.AddItem("m_defend", s_Defend);
	m_SpriteMenu.AddItem("m_follow", s_Follow);
	m_SpriteMenu.AddItem("", "", ITEMDRAW_NOTEXT);
	m_SpriteMenu.AddItem("", "", ITEMDRAW_NOTEXT);
	m_SpriteMenu.AddItem("", "", ITEMDRAW_NOTEXT);

	m_SpriteMenu.ExitBackButton = true;

	m_SpriteMenu.Display(client, MENU_TIME_FOREVER);
}

public int SpriteMenu_Handler(Handle m_SpriteMenu, MenuAction action, int client, int itemNum)
{
	if(action == MenuAction_End)
	{
		delete m_SpriteMenu;
	}
	if(IsValidClient(client) && (g_iLeaderClient == client || g_iHelperClient == client))
	{
		if(action == MenuAction_Select)
		{
			char info[32];
			GetMenuItem(m_SpriteMenu, itemNum, info, sizeof(info));

			// SpriteMenu
			if(StrEqual(info, "m_none"))
			{
				RemoveSprite(client);
				CPrintToChat(client, "%t", "Sprite removed");
				g_iCurrentSprite[client] = -1;
				SpriteMenu(client);
			}
			if(StrEqual(info, "m_defend"))
			{
				RemoveSprite(client);
				g_iSpriteEntities[client] = AttachSprite(client, g_eCvarsList.g_sCVAR_VDEFEND_VMT);
				CPrintToChat(client, "%t", "Sprite changed to Defend Here");
				g_iCurrentSprite[client] = 0;
				SpriteMenu(client);
			}
			if(StrEqual(info, "m_follow"))
			{
				RemoveSprite(client);
				g_iSpriteEntities[client] = AttachSprite(client, g_eCvarsList.g_sCVAR_VFOLLOW_VMT);
				CPrintToChat(client, "%t", "Sprite changed to Follow Me");
				g_iCurrentSprite[client] = 1;
				SpriteMenu(client);
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
				SendConVarValue(client, CVAR_MP_MAXMONEY, g_eCvarsList.g_sCVAR_VALUE_MP_MAXMONEY);
				SendConVarValue(client, CVAR_SV_DISABLE_RADAR, g_eCvarsList.g_sCVAR_VALUE_SV_DISABLE_RADAR);
			}
		}
		else action = MenuAction_Cancel;
		
	}
	if (action == MenuAction_Cancel && itemNum != MenuCancel_ExitBack)
	{
		if (IsValidClient(client) && g_Game == Game_CSGO)
		{
			SendConVarValue(client, CVAR_MP_MAXMONEY, g_eCvarsList.g_sCVAR_VALUE_MP_MAXMONEY);
			SendConVarValue(client, CVAR_SV_DISABLE_RADAR, g_eCvarsList.g_sCVAR_VALUE_SV_DISABLE_RADAR);
		}
	}
	return 0;
}

public int AttachSprite(int client, char[] sprite)
{
	if(!IsValidClient(client))
	{
		return -1;
	}

	char iTarget[16], sTargetname[64];
	GetEntPropString(client, Prop_Data, "m_iName", sTargetname, sizeof(sTargetname));

	Format(iTarget, sizeof(iTarget), "Client%d", client);
	DispatchKeyValue(client, "targetname", iTarget);

	float Origin[3];
	GetClientEyePosition(client, Origin);
	Origin[2] += 45.0;

	int Ent = CreateEntityByName("env_sprite");
	if(!Ent) return -1;

	DispatchKeyValue(Ent, "model", sprite);
	DispatchKeyValue(Ent, "classname", "env_sprite");
	DispatchKeyValue(Ent, "spawnflags", "1");
	DispatchKeyValue(Ent, "scale", "0.1");
	DispatchKeyValue(Ent, "rendermode", "1");
	DispatchKeyValue(Ent, "rendercolor", "255 255 255");
	DispatchSpawn(Ent);
	TeleportEntity(Ent, Origin, NULL_VECTOR, NULL_VECTOR);
	SetVariantString(iTarget);
	AcceptEntityInput(Ent, "SetParent", Ent, Ent, 0);

	DispatchKeyValue(client, "targetname", sTargetname);

	return Ent;
}

public void RemoveSprite(int client)
{
	if (g_iSpriteEntities[client] != -1 && IsValidEdict(g_iSpriteEntities[client]))
	{
		char m_szClassname[64];
		GetEdictClassname(g_iSpriteEntities[client], m_szClassname, sizeof(m_szClassname));
		if(strcmp("env_sprite", m_szClassname)==0)
		AcceptEntityInput(g_iSpriteEntities[client], "Kill");
	}
	g_iSpriteEntities[client] = -1;
	g_iCurrentSprite[client] = -1;
}