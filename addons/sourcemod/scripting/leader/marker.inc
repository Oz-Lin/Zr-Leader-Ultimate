/*
 * =============================================================================
 * File:		  marker.inc
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


void MarkerMenu(int client)
{
	if(!IsValidClient(client))
	{
		return;
	}

	Menu m_MarkerMenu = new Menu(MarkerMenu_Handler);
	SetGlobalTransTarget(client);
	if (g_Game == Game_CSGO)
	{
		//SendConVarValue(client, CVAR_MP_MAXMONEY, "0");
		//SendConVarValue(client, CVAR_SV_DISABLE_RADAR, "1");
	}

	char s_Title[LENGTH_MAX_TEXT];
	char s_RemoveMarker[LENGTH_MED_TEXT];
	char s_ArrowMarker[LENGTH_MED_TEXT];
	char s_DefendMarker[LENGTH_MED_TEXT];
	char s_SpawnMarker[LENGTH_MED_TEXT];
	char s_NoDoorhugMarker[LENGTH_MED_TEXT];
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

	Format(s_Title, sizeof(s_Title), "%t", "Leader Menu Title Marker", s_TSprite, s_TMarker, s_TBeacon, s_TGlow, s_TBMute, s_THelper);
	Format(s_DefendMarker, sizeof(s_DefendMarker), "%t", "Defend Marker");
	Format(s_RemoveMarker, sizeof(s_RemoveMarker), "%t", "Remove Marker");
	Format(s_ArrowMarker, sizeof(s_ArrowMarker), "%t", "Arrow Marker");
	Format(s_SpawnMarker, sizeof(s_SpawnMarker), "%t", "Spawn Marker");
	Format(s_NoDoorhugMarker, sizeof(s_NoDoorhugMarker), "%t", "No Doorhug Marker");

	m_MarkerMenu.SetTitle(s_Title);
	m_MarkerMenu.AddItem("m_arrowmarker", s_ArrowMarker);
	m_MarkerMenu.AddItem("m_defendmarker", s_DefendMarker);
	m_MarkerMenu.AddItem("m_spawnmarker", s_SpawnMarker);
	m_MarkerMenu.AddItem("m_nodoorhugmarker", s_NoDoorhugMarker);
	m_MarkerMenu.AddItem("m_removemarker", s_RemoveMarker);
	m_MarkerMenu.AddItem("", "", ITEMDRAW_NOTEXT);

	m_MarkerMenu.ExitBackButton = true;

	m_MarkerMenu.Display(client, MENU_TIME_FOREVER);
}

public int MarkerMenu_Handler(Handle m_MarkerMenu, MenuAction action, int client, int itemNum)
{
	if(action == MenuAction_End)
	{
		delete m_MarkerMenu;
	}
	if(IsValidClient(client) && (g_iLeaderClient == client || g_iHelperClient == client))
	{
		if(action == MenuAction_Select)
		{
			char info[32];
			GetMenuItem(m_MarkerMenu, itemNum, info, sizeof(info));

			if(StrEqual(info, "m_arrowmarker"))
			{
				if (g_iMarkerCount[client] >= g_eCvarsList.g_iCVAR_MAX_MARKER)
				{
					g_iRemoveMarker[client]++;
					if (g_iRemoveMarker[client] > g_eCvarsList.g_iCVAR_MAX_MARKER)
					{
						g_iRemoveMarker[client] = 1;
					}
					RemoveMarker(g_iRemoveMarker[client]);
					g_iMarkerEntities[g_iRemoveMarker[client]] = SpawnMarker(client, g_eCvarsList.g_sCVAR_VARROW_VMT);
					CPrintToChat(client, "%t", "Generic Arrow marker placed" ,g_iRemoveMarker[client]);
					MarkerMenu(client);

				}
				else
				{
					g_iMarkerCount[client]++;
					g_iMarkerEntities[g_iMarkerCount[client]] = SpawnMarker(client, g_eCvarsList.g_sCVAR_VARROW_VMT);
					CPrintToChat(client, "%t", "Generic Arrow marker placed" ,g_iMarkerCount[client]);
					MarkerMenu(client);
				}
			}

			if(StrEqual(info, "m_defendmarker"))
			{
				if (g_iMarkerCount[client] >= g_eCvarsList.g_iCVAR_MAX_MARKER)
				{
					g_iRemoveMarker[client]++;
					if (g_iRemoveMarker[client] > g_eCvarsList.g_iCVAR_MAX_MARKER)
					{
						g_iRemoveMarker[client] = 1;
					}
					RemoveMarker(g_iRemoveMarker[client]);
					g_iMarkerEntities[g_iRemoveMarker[client]] = SpawnMarker(client, g_eCvarsList.g_sCVAR_VDEFEND_VMT);
					CPrintToChat(client, "%t", "Defend Here marker placed" ,g_iRemoveMarker[client]);
					MarkerMenu(client);
					
				}
				else
				{
					g_iMarkerCount[client]++;
					g_iMarkerEntities[g_iMarkerCount[client]] = SpawnMarker(client, g_eCvarsList.g_sCVAR_VDEFEND_VMT);
					CPrintToChat(client, "%t", "Defend Here marker placed" ,g_iMarkerCount[client]);
					MarkerMenu(client);
				}
			}

			if(StrEqual(info, "m_spawnmarker"))
			{
				if (g_iMarkerCount[client] >= g_eCvarsList.g_iCVAR_MAX_MARKER)
				{
					g_iRemoveMarker[client]++;
					if (g_iRemoveMarker[client] > g_eCvarsList.g_iCVAR_MAX_MARKER)
					{
						g_iRemoveMarker[client] = 1;
					}
					RemoveMarker(g_iRemoveMarker[client]);
					g_iMarkerEntities[g_iRemoveMarker[client]] = SpawnMarker(client, g_eCvarsList.g_sCVAR_VSPAWN_VMT);
					CPrintToChat(client, "%t", "Zombie Spawn marker placed" ,g_iRemoveMarker[client]);
					MarkerMenu(client);
					
				}
				else
				{
					g_iMarkerCount[client]++;
					g_iMarkerEntities[g_iMarkerCount[client]] = SpawnMarker(client, g_eCvarsList.g_sCVAR_VSPAWN_VMT);
					CPrintToChat(client, "%t", "Zombie Spawn marker placed" ,g_iMarkerCount[client]);
					MarkerMenu(client);
				}
			}

			if(StrEqual(info, "m_nodoorhugmarker"))
			{
				if (g_iMarkerCount[client] >= g_eCvarsList.g_iCVAR_MAX_MARKER)
				{
					g_iRemoveMarker[client]++;
					if (g_iRemoveMarker[client] > g_eCvarsList.g_iCVAR_MAX_MARKER)
					{
						g_iRemoveMarker[client] = 1;
					}
					RemoveMarker(g_iRemoveMarker[client]);
					g_iMarkerEntities[g_iRemoveMarker[client]] = SpawnMarker(client, g_eCvarsList.g_sCVAR_VNODOORHUG_VMT);
					CPrintToChat(client, "%t", "No Doorhug marker placed" ,g_iRemoveMarker[client]);
					MarkerMenu(client);
					
				}
				else
				{
					g_iMarkerCount[client]++;
					g_iMarkerEntities[g_iMarkerCount[client]] = SpawnMarker(client, g_eCvarsList.g_sCVAR_VNODOORHUG_VMT);
					CPrintToChat(client, "%t", "No Doorhug marker placed" ,g_iMarkerCount[client]);
					MarkerMenu(client);
				}
			}

			if(StrEqual(info, "m_removemarker"))
			{
				RemoveAllMarker(client);
				CPrintToChat(client, "%t", "Marker removed");
				MarkerMenu(client);
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

public int SpawnMarker(int client, char[] sprite)
{
	if(!IsValidClient(client))
	{
		return -1;
	}

	// float Origin[3];
	// GetClientEyePosition(client, Origin);
	// Origin[2] += 25.0;

	if(!SetAimEndPoint(client))
	{
		return -1;
	}

	int Ent = CreateEntityByName("env_sprite");
	if(!Ent) return -1;

	DispatchKeyValue(Ent, "model", sprite);
	DispatchKeyValue(Ent, "classname", "env_sprite");
	DispatchKeyValue(Ent, "spawnflags", "1");
	DispatchKeyValue(Ent, "scale", "0.1");
	DispatchKeyValue(Ent, "rendermode", "1");
	DispatchKeyValue(Ent, "rendercolor", "255 255 255");
	DispatchSpawn(Ent);
	TeleportEntity(Ent, g_pos, NULL_VECTOR, NULL_VECTOR);

	return Ent;
}

public bool SetAimEndPoint(int client)
{
	float vAngles[3];
	float vOrigin[3];
	float vBuffer[3];
	float vStart[3];
	float Distance;

	GetClientEyePosition(client, vOrigin);
	GetClientEyeAngles(client, vAngles);

  //get endpoint for spawn marker
	Handle trace = TR_TraceRayFilterEx(vOrigin, vAngles, MASK_SHOT, RayType_Infinite, TraceEntityFilterPlayer);

	if(TR_DidHit(trace))
	{
  		TR_GetEndPosition(vStart, trace);
		GetVectorDistance(vOrigin, vStart, false);
		Distance = -35.0;
		GetAngleVectors(vAngles, vBuffer, NULL_VECTOR, NULL_VECTOR);
		g_pos[0] = vStart[0] + (vBuffer[0]*Distance);
		g_pos[1] = vStart[1] + (vBuffer[1]*Distance);
		g_pos[2] = vStart[2] + (vBuffer[2]*Distance) + 25.0;
	}
	else
	{
		CPrintToChat(client, "%t", "Could not spawn marker");
		CloseHandle(trace);
		return false;
	}

	CloseHandle(trace);
	return true;
}

public bool TraceEntityFilterPlayer(int entity, int contentsMask)
{
	return (entity > MaxClients || !entity);
}


public void RemoveMarker(int Marker)
{
	if (g_iMarkerEntities[Marker] != -1 && IsValidEdict(g_iMarkerEntities[Marker]))
	{
		char m_szClassname[64];
		GetEdictClassname(g_iMarkerEntities[Marker], m_szClassname, sizeof(m_szClassname));
		if(strcmp("env_sprite", m_szClassname)==0)
		AcceptEntityInput(g_iMarkerEntities[Marker], "Kill");
	}
	g_iMarkerEntities[Marker] = -1;
}

public void RemoveAllMarker(int client)
{
	if (g_iMarkerCount[client] >= 1)
	{
		for (int m = 1; m < g_iMarkerCount[client]+1; m++)
		{
			if (g_iMarkerEntities[m] != -1 && IsValidEdict(g_iMarkerEntities[m]))
			{
				char m_szClassname[64];
				GetEdictClassname(g_iMarkerEntities[m], m_szClassname, sizeof(m_szClassname));
				if(strcmp("env_sprite", m_szClassname)==0)
				AcceptEntityInput(g_iMarkerEntities[m], "Kill");
			}
			g_iMarkerEntities[m] = -1;
		}
	}
	g_iMarkerCount[client] = 0;
	g_iRemoveMarker[client] = 0;
}