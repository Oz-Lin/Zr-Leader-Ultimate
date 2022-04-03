/*
 * =============================================================================
 * File:		  downloads.inc
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

void DownloadsLoad()
{
	AddFileToDownloadsTable(g_eCvarsList.g_sCVAR_VDEFEND_VTF);
	AddFileToDownloadsTable(g_eCvarsList.g_sCVAR_VDEFEND_VMT);
	AddFileToDownloadsTable(g_eCvarsList.g_sCVAR_VFOLLOW_VTF);
	AddFileToDownloadsTable(g_eCvarsList.g_sCVAR_VFOLLOW_VMT);

	PrecacheGeneric(g_eCvarsList.g_sCVAR_VDEFEND_VTF, true);
	PrecacheGeneric(g_eCvarsList.g_sCVAR_VDEFEND_VMT, true);
	PrecacheGeneric(g_eCvarsList.g_sCVAR_VFOLLOW_VTF, true);
	PrecacheGeneric(g_eCvarsList.g_sCVAR_VFOLLOW_VMT, true);

	Handle gameConfig = LoadGameConfigFile("funcommands.games");
	if (gameConfig == null)
	{
		SetFailState("Unable to load game config funcommands.games");
		return;
	}

	char buffer[PLATFORM_MAX_PATH];
	if (GameConfGetKeyValue(gameConfig, "SpriteBeam", buffer, sizeof(buffer)) && buffer[0])
	{
		g_iBeamSprite = PrecacheModel(buffer);
	}
	if (GameConfGetKeyValue(gameConfig, "SpriteHalo", buffer, sizeof(buffer)) && buffer[0])
	{
		g_iHaloSprite = PrecacheModel(buffer);
	}
}