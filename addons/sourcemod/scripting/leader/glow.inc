/*
 * =============================================================================
 * File:		  glow.inc
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

#define EF_BONEMERGE                (1 << 0)
#define EF_NOSHADOW                 (1 << 4)
#define EF_NORECEIVESHADOW          (1 << 6)

public void PerformGlow(int client)
{
	if (g_iPlayerModelsIndex[client] == -1)
	{
		CVAR_SV_FORCE_TRANSMIT_PLAYERS.SetString("1", true, false);
		LogAction(client, client, "\"%L\" set a Glow on himself", client);
		CreateGlow(client);
	}
	else
	{
		CVAR_SV_FORCE_TRANSMIT_PLAYERS.SetString("0", true, false);
		LogAction(client, client, "\"%L\" removed a Glow on himself", client);
		RemoveSkin(client);
	}
}

public void CreateGlow(int client) 
{	
	char model[PLATFORM_MAX_PATH];
	int skin = -1;
	GetClientModel(client, model, sizeof(model));
	skin = CreatePlayerModelProp(client, model);
	if(skin > MaxClients)
	{
		if(SDKHookEx(skin, SDKHook_SetTransmit, OnSetTransmit_All))
		{
			SetupGlow(skin);
		}
	}
}

public Action OnSetTransmit_All(int entity, int client)
{
	if(g_iPlayerModelsIndex[client] != entity)
	{
		return Plugin_Continue;
	}
	return Plugin_Stop;
}

public void SetupGlow(int entity)
{
	static int offset = -1;
	if ((offset = GetEntSendPropOffs(entity, "m_clrGlow")) == -1)
	{
		LogError("Unable to find property offset: \"m_clrGlow\"!");
		return;
	}


	SetEntProp(entity, Prop_Send, "m_bShouldGlow", true);
	SetEntProp(entity, Prop_Send, "m_nGlowStyle", 0);
	SetEntPropFloat(entity, Prop_Send, "m_flGlowMaxDist", 10000.0);

	for(int i = 0; i < 3; i++)
	{
		SetEntData(entity, offset + i, g_iColorsGlow[i], _, true);
	}
}

public int CreatePlayerModelProp(int client, char[] sModel)
{
	RemoveSkin(client);
	int skin = CreateEntityByName("prop_dynamic_glow");
	DispatchKeyValue(skin, "model", sModel);
	DispatchKeyValue(skin, "solid", "0");
	DispatchKeyValue(skin, "fademindist", "1");
	DispatchKeyValue(skin, "fademaxdist", "1");
	DispatchKeyValue(skin, "fadescale", "2.0");
	SetEntProp(skin, Prop_Send, "m_CollisionGroup", 0);
	DispatchSpawn(skin);
	SetEntityRenderMode(skin, RENDER_GLOW);
	SetEntityRenderColor(skin, 0, 0, 0, 0);
	SetEntProp(skin, Prop_Send, "m_fEffects", EF_BONEMERGE);
	SetVariantString("!activator");
	AcceptEntityInput(skin, "SetParent", client, skin);
	SetVariantString("primary");
	AcceptEntityInput(skin, "SetParentAttachment", skin, skin, 0);
	SetVariantString("OnUser1 !self:Kill::0.1:-1");
	AcceptEntityInput(skin, "AddOutput");
	g_iPlayerModels[client] = EntIndexToEntRef(skin);
	g_iPlayerModelsIndex[client] = skin;
	return skin;
}

public void RemoveSkin(int client) {
    int index = EntRefToEntIndex(g_iPlayerModels[client]);
    if(index > MaxClients && IsValidEntity(index)) {
        SetEntProp(index, Prop_Send, "m_bShouldGlow", false);
        AcceptEntityInput(index, "FireUser1");
    }
    g_iPlayerModels[client] = INVALID_ENT_REFERENCE;
    g_iPlayerModelsIndex[client] = -1;
}