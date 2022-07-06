/*
 * =============================================================================
 * File:		  cvars.inc
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

ConVar CVAR_DISABLE = null;
ConVar CVAR_VDEFEND_VTF = null;
ConVar CVAR_VDEFEND_VMT = null;
ConVar CVAR_VFOLLOW_VTF = null;
ConVar CVAR_VFOLLOW_VMT = null;
ConVar CVAR_VSPAWN_VTF = null;
ConVar CVAR_VSPAWN_VMT = null;
ConVar CVAR_VARROW_VTF = null;
ConVar CVAR_VARROW_VMT = null;
ConVar CVAR_VNODOORHUG_VTF = null;
ConVar CVAR_VNODOORHUG_VMT = null;
ConVar CVAR_ALLOW_VOTING = null;
ConVar CVAR_ALLOW_RL_VOTING = null;
ConVar CVAR_ALLOW_ADMIN_LEADER = null;
ConVar CVAR_MAX_MARKER = null;
ConVar CVAR_ROUND_END_RELEADER = null;
ConVar CVAR_TIMER_REMOVE_MUTE = null;
ConVar CVAR_GLOW_COLOR = null;
ConVar CVAR_SV_FORCE_TRANSMIT_PLAYERS = null;
ConVar CVAR_REMOVE_LEADER_ON_DEATH = null;
//ConVar CVAR_MP_MAXMONEY = null;  // not in use
//ConVar CVAR_SV_DISABLE_RADAR = null; // not in use

void CvarsInit()
{
	LoadTranslations("leader2.phrases");
	LoadTranslations("common.phrases");
	LoadTranslations("core.phrases");

	CvarsCreate();

	if (g_Game == Game_CSGO) CvarsFind();
}

void CvarsCreate()
{
	CVAR_DISABLE = CreateConVar("sm_leader_disable", "1", "Disable Plugin. 1 = On 0 = Off");
	CVAR_VDEFEND_VTF = CreateConVar("sm_leader_defend_vtf", "materials/sg/sgdefend.vtf", "The defend here .vtf file");
	CVAR_VDEFEND_VMT = CreateConVar("sm_leader_defend_vmt", "materials/sg/sgdefend.vmt", "The defend here .vmt file");
	CVAR_VFOLLOW_VTF = CreateConVar("sm_leader_follow_vtf", "materials/sg/sgfollow.vtf", "The follow me .vtf file");
	CVAR_VFOLLOW_VMT = CreateConVar("sm_leader_follow_vmt", "materials/sg/sgfollow.vmt", "The follow me .vmt file");
	CVAR_VSPAWN_VMT = CreateConVar("sm_leader_spawn_vmt", "materials/sg/sgspawn.vmt", "The zombie spawn .vmt file");
	CVAR_VSPAWN_VTF = CreateConVar("sm_leader_spawn_vtf", "materials/sg/sgspawn.vtf", "The zombie spawn .vtf file");
	CVAR_VARROW_VMT = CreateConVar("sm_generic_arrow_vmt", "materials/gfl/marker.vmt", "The generic arrow .vmt file");
	CVAR_VARROW_VTF = CreateConVar("sm_generic_arrow_vtf", "materials/gfl/marker.vtf", "The generic arrow .vtf file");
	CVAR_VNODOORHUG_VMT = CreateConVar("sm_no_doorhug_vmt", "materials/sg/nodoorhug.vmt", "The no doorhug .vmt file");
	CVAR_VNODOORHUG_VTF = CreateConVar("sm_no_doorhug_vtf", "materials/sg/nodoorhug.vtf", "The no doorhug .vtf file");
	CVAR_ALLOW_VOTING = CreateConVar("sm_leader_allow_votes", "1", "Determines whether players can vote for leaders.");
	CVAR_ALLOW_RL_VOTING = CreateConVar("sm_leader_remove_leader_votes", "1", "Determines whether players can vote for remove leaders.");
	CVAR_ALLOW_ADMIN_LEADER = CreateConVar("sm_leader_admin_leader", "1", "Determines whether Admin can access menu leader, without voting.");
	CVAR_MAX_MARKER = CreateConVar("sm_leader_max_markers", "5", "Determines maximum number of markers. Max 20");
	CVAR_ROUND_END_RELEADER = CreateConVar("sm_leader_roundend_rleader", "1", "Determine whether to remove the leader at the end of the round.");
	CVAR_TIMER_REMOVE_MUTE = CreateConVar("sm_leader_timer_removemute", "15.0", "Determine how long the players were speechless after applying the Mute All (Avoid cheating leader).");
	CVAR_GLOW_COLOR = CreateConVar("sm_leader_glow_color", "72 96 144", "Determines R G B glow colors for Leader\nFormat should be \"R G B\" (with spaces).");
	CVAR_REMOVE_LEADER_ON_DEATH = CreateConVar("sm_leader_remove_on_die", "1", "Determine whether to remove the leader if leader get infected or died.");

	CVAR_DISABLE.AddChangeHook(ConVarChange);
	CVAR_VDEFEND_VTF.AddChangeHook(ConVarChange);
	CVAR_VDEFEND_VMT.AddChangeHook(ConVarChange);
	CVAR_VFOLLOW_VTF.AddChangeHook(ConVarChange);
	CVAR_VFOLLOW_VMT.AddChangeHook(ConVarChange);
	CVAR_VSPAWN_VTF.AddChangeHook(ConVarChange);
	CVAR_VSPAWN_VMT.AddChangeHook(ConVarChange);
	CVAR_VARROW_VTF.AddChangeHook(ConVarChange);
	CVAR_VARROW_VMT.AddChangeHook(ConVarChange);
	CVAR_VNODOORHUG_VTF.AddChangeHook(ConVarChange);
	CVAR_VNODOORHUG_VMT.AddChangeHook(ConVarChange);
	CVAR_ALLOW_VOTING.AddChangeHook(ConVarChange);
	CVAR_ALLOW_RL_VOTING.AddChangeHook(ConVarChange);
	CVAR_ALLOW_ADMIN_LEADER.AddChangeHook(ConVarChange);
	CVAR_MAX_MARKER.AddChangeHook(ConVarChange);
	CVAR_ROUND_END_RELEADER.AddChangeHook(ConVarChange);
	CVAR_TIMER_REMOVE_MUTE.AddChangeHook(ConVarChange);
	CVAR_GLOW_COLOR.AddChangeHook(ConVarChange);
	CVAR_REMOVE_LEADER_ON_DEATH.AddChangeHook(ConVarChange);

	AutoExecConfig(true, "leader_ultimate");

	GetConVars();
}

public void ConVarChange(ConVar CVar, const char[] oldVal, const char[] newVal)
{
	GetConVars();
}

public void GetConVars()
{
	g_eCvarsList.g_bCVAR_DISABLE = CVAR_DISABLE.BoolValue;
	CVAR_VDEFEND_VTF.GetString(g_eCvarsList.g_sCVAR_VDEFEND_VTF, sizeof(g_eCvarsList.g_sCVAR_VDEFEND_VTF));
	CVAR_VDEFEND_VMT.GetString(g_eCvarsList.g_sCVAR_VDEFEND_VMT, sizeof(g_eCvarsList.g_sCVAR_VDEFEND_VMT));
	CVAR_VFOLLOW_VTF.GetString(g_eCvarsList.g_sCVAR_VFOLLOW_VTF, sizeof(g_eCvarsList.g_sCVAR_VFOLLOW_VTF));
	CVAR_VFOLLOW_VMT.GetString(g_eCvarsList.g_sCVAR_VFOLLOW_VMT, sizeof(g_eCvarsList.g_sCVAR_VFOLLOW_VMT));
	CVAR_VSPAWN_VTF.GetString(g_eCvarsList.g_sCVAR_VSPAWN_VTF, sizeof(g_eCvarsList.g_sCVAR_VSPAWN_VTF));
	CVAR_VSPAWN_VMT.GetString(g_eCvarsList.g_sCVAR_VSPAWN_VMT, sizeof(g_eCvarsList.g_sCVAR_VSPAWN_VMT));
	CVAR_VARROW_VTF.GetString(g_eCvarsList.g_sCVAR_VARROW_VTF, sizeof(g_eCvarsList.g_sCVAR_VARROW_VTF));
	CVAR_VARROW_VMT.GetString(g_eCvarsList.g_sCVAR_VARROW_VMT, sizeof(g_eCvarsList.g_sCVAR_VARROW_VMT));
	CVAR_VNODOORHUG_VTF.GetString(g_eCvarsList.g_sCVAR_VNODOORHUG_VTF, sizeof(g_eCvarsList.g_sCVAR_VNODOORHUG_VTF));
	CVAR_VNODOORHUG_VMT.GetString(g_eCvarsList.g_sCVAR_VNODOORHUG_VMT, sizeof(g_eCvarsList.g_sCVAR_VNODOORHUG_VMT));
	g_eCvarsList.g_bCVAR_ALLOW_VOTING = CVAR_ALLOW_VOTING.BoolValue;
	g_eCvarsList.g_bCVAR_ALLOW_RL_VOTING = CVAR_ALLOW_RL_VOTING.BoolValue;
	g_eCvarsList.g_bCVAR_ALLOW_ADMIN_LEADER = CVAR_ALLOW_ADMIN_LEADER.BoolValue;
	g_eCvarsList.g_iCVAR_MAX_MARKER = CVAR_MAX_MARKER.IntValue;
	g_eCvarsList.g_bCVAR_ROUND_END_RELEADER = CVAR_ROUND_END_RELEADER.BoolValue;
	g_eCvarsList.g_fCVAR_TIMER_REMOVE_MUTE = CVAR_TIMER_REMOVE_MUTE.FloatValue;
	g_eCvarsList.g_bCVAR_REMOVE_LEADER_ON_DEATH = CVAR_REMOVE_LEADER_ON_DEATH.BoolValue;
	CVAR_GLOW_COLOR.GetString(g_eCvarsList.g_sCVAR_GLOW_COLOR, sizeof(g_eCvarsList.g_sCVAR_GLOW_COLOR));
	ColorStringToArray(g_eCvarsList.g_sCVAR_GLOW_COLOR, g_iColorsGlow);
}

void CvarsFind()
{
	CVAR_SV_FORCE_TRANSMIT_PLAYERS = FindConVar("sv_force_transmit_players");
	//CVAR_MP_MAXMONEY = FindConVar("mp_maxmoney");
	//GetConVarString(CVAR_MP_MAXMONEY, g_eCvarsList.g_sCVAR_VALUE_MP_MAXMONEY, sizeof(g_eCvarsList.g_sCVAR_VALUE_MP_MAXMONEY));
	//CVAR_SV_DISABLE_RADAR = FindConVar("sv_disable_radar");
	//GetConVarString(CVAR_SV_DISABLE_RADAR, g_eCvarsList.g_sCVAR_VALUE_SV_DISABLE_RADAR, sizeof(g_eCvarsList.g_sCVAR_VALUE_SV_DISABLE_RADAR));
}