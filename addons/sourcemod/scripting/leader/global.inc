/*
 * =============================================================================
 * File:		  global.inc
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
#define LENGTH_MAX_LINE	1024
#define LENGTH_MED_LINE	512
#define LENGTH_MIN_LINE	256
#define LENGTH_MAX_TEXT	128
#define LENGTH_MED_TEXT	64
#define LENGTH_MIN_TEXT	32

#define MARKER_ENTITIES	20

enum struct CvarsList
{
	bool g_bCVAR_DISABLE;
	char g_sCVAR_VDEFEND_VTF[PLATFORM_MAX_PATH];
	char g_sCVAR_VDEFEND_VMT[PLATFORM_MAX_PATH];
	char g_sCVAR_VFOLLOW_VTF[PLATFORM_MAX_PATH];
	char g_sCVAR_VFOLLOW_VMT[PLATFORM_MAX_PATH];
	char g_sCVAR_VSPAWN_VTF[PLATFORM_MAX_PATH];
	char g_sCVAR_VSPAWN_VMT[PLATFORM_MAX_PATH];
	char g_sCVAR_VARROW_VTF[PLATFORM_MAX_PATH];
	char g_sCVAR_VARROW_VMT[PLATFORM_MAX_PATH];
	char g_sCVAR_VNODOORHUG_VTF[PLATFORM_MAX_PATH];
	char g_sCVAR_VNODOORHUG_VMT[PLATFORM_MAX_PATH];
	bool g_bCVAR_ALLOW_VOTING;
	bool g_bCVAR_ALLOW_RL_VOTING;
	bool g_bCVAR_ALLOW_ADMIN_LEADER;
	int g_iCVAR_MAX_MARKER;
	bool g_bCVAR_ROUND_END_RELEADER;
	float g_fCVAR_TIMER_REMOVE_MUTE;
	char g_sCVAR_GLOW_COLOR[LENGTH_MED_TEXT];
	//char g_sCVAR_VALUE_MP_MAXMONEY[LENGTH_MIN_TEXT];
	//char g_sCVAR_VALUE_SV_DISABLE_RADAR[LENGTH_MIN_TEXT];
}

CvarsList g_eCvarsList;

int g_iLeaderClient;
int g_iHelperClient;

char g_sClientNames[MAXPLAYERS+1][MAX_NAME_LENGTH];
//char g_sLeaderTag[LENGTH_MED_TEXT];

/**
 * Global button count.
 */
 int g_iButtoncount[MAXPLAYERS+1] = 0;
//**

/**
 * Global Votes.
 */
int g_iVoteCount[MAXPLAYERS+1];
int g_iVoteRemoveCount[MAXPLAYERS+1];
int g_iVotedFor[MAXPLAYERS+1];
int g_iVotedRemovedFor[MAXPLAYERS+1];
//**

/**
 * Global Sprites.
 */
int g_iSpriteEntities[MAXPLAYERS+1];
int g_iCurrentSprite[MAXPLAYERS+1] = { -1, ... };
//**

/**
 * Global Marker.
 */
int g_iMarkerEntities[MARKER_ENTITIES+1];
int g_iMarkerCount[MAXPLAYERS+1] = { 0, ... };
int g_iRemoveMarker[MAXPLAYERS+1] = { 0, ... };
float g_pos[3];

//**

/**
 * Global Glow.
 */
int g_iColorsGlow[3];
int g_iPlayerModelsIndex[MAXPLAYERS + 1] = { -1, ... };
int g_iPlayerModels[MAXPLAYERS + 1] = {INVALID_ENT_REFERENCE, ... };
//**

/**
 * Global Beacon.
 */
int g_iBeamSprite = -1;
int g_iHaloSprite = -1;
int g_iSerial_Gen = 0;
int g_iBeaconSerial[MAXPLAYERS+1] = { 0, ... };
int g_iGreyColor[4] = {128, 128, 128, 255};
//**

/**
 * Global Mute.
 */
bool g_bMuteStatus = false;
bool g_bMuteClient[MAXPLAYERS+1] = {false, ...};
//**