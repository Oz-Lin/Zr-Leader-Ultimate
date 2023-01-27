/*
 * =============================================================================
 * File:		  laser.inc
 * Type:		  Base
 * Description:   Plugin's base file.
 *
 * Copyright (C)   Anubis+OZIG Edition. All rights reserved.
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
// Thanks: https://github.com/matthewpi/lasers

void LaserOnMapStart()
{
    //g_iLaserSprite = PrecacheModel(FindConVar ("sm_leader_laser_vmt"),true); //PrecacheModel("materials/sprites/laserbeam.vmt");
    g_iLaserSprite = PrecacheModel("materials/sprites/laserbeam.vmt"); // WTF, not on download table
    // Timers
    CreateTimer(0.1, Timer_RenderLeaderLasers, _, TIMER_REPEAT|TIMER_FLAG_NO_MAPCHANGE);
}

public void LaserOnClientPutInServer(int client)
{
    g_bLaserEnabled[client] = false;
    g_iLaserColour[client] = -1;
    g_iLeaderLaserColour[client] = 0;

    for (int i = 0; i < 3; i++) 
    {
        g_iLaserHistory[client][i] = 0.0;
    }
}

/**
 * Timer_RenderLasers
 * Renders all lasers.
 */
public Action Timer_RenderLeaderLasers(Handle timer) {
    float position[3];
    float standingPosition[3];
    int color = 0;

    // Loop through all clients.
    for (int client = 1; client <= MaxClients; client++) {
        // Check if the client is not ingame.
        if (!IsClientInGame(client)) {
            continue;
        }

        // Check if the client is not alive
        if (!IsPlayerAlive(client)) {
            continue;
        }

        // Check if the client's laser is disabled.
        if (!g_bLaserEnabled[client]) {
            continue;
        }

        // Get the client's standing position.
        GetClientAbsOrigin(client, standingPosition);
        TraceEye(client, position);

        // Check if the drawing distance of the laser is too far away.
        if (GetVectorDistance(position, standingPosition) > 2500.0) {
            // Reset the laser history to prevent lasers from being drawn
            // even if g_iLaserHistory is outside of the 2500.0 unit limit.
            for (int i = 0; i < 3; i++) {
                g_iLaserHistory[client][i] = 0.0;
            }
            return Plugin_Continue;
        }

        // Check if the laser distance is more than 6.0 units.
        if (GetVectorDistance(position, g_iLaserHistory[client]) > 6.0) {
            // Get the client's set laser colour.
            color = g_iLaserColour[client];

            // Check if the user is using the rainbow color.
            if (color == -1) {
                color = g_iLeaderLaserColour[client];
                g_iLeaderLaserColour[client] = color + 1;

                // Loop through 5 colours.
                if (g_iLeaderLaserColour[client] > 4) {
                    g_iLeaderLaserColour[client] = 0;
                }
            }

            // Render the laser.
            LeaderLaser(g_iLaserHistory[client], position, g_iLaserColours[color]);

            // Update the laser history array.
            for (int i = 0; i < 3; i++) {
                g_iLaserHistory[client][i] = position[i];
            }
            
        }
    }
    return Plugin_Handled;
}

/**
 * Command_Laser (+sm_laser)
 *
public Action Command_Laser(const int client, const int args) {
    // Check if the client is invalid.
    if (!IsValidClient(client)) {
        return Plugin_Handled;
    }

    // Check if the client is not eligible.
    if (!IsClientEligible(client)) {
        return Plugin_Handled;
    }

    // Open the laser menu.
    Laser_Menu(client);

    return Plugin_Handled;
}
*/

/**
 * Command_LeaderLaserOn (+sm_leader_laser)
 * Draws a laser.
 */
public Action Command_LeaderLaserOn(const int client, const int args) {
    // Check if the client is invalid.
    if (!IsValidClient(client)) {
        return Plugin_Handled;
    }

    // Check if the client is not eligible.
    if (!(g_iLeaderClient == client || g_iHelperClient == client)) {
        return Plugin_Handled;
    }

    // Check if the client is not alive.
    if (!IsPlayerAlive(client)) {
        return Plugin_Handled;
    }

    // Update the client's laser position history.
    TraceEye(client, g_iLaserHistory[client]);
    g_bLaserEnabled[client] = true;

    return Plugin_Handled;
}

/**
 * Command_LeaderLaserOff (-sm_leader_laser)
 * Stops drawing a laser.
 */
public Action Command_LeaderLaserOff(const int client, const int args) {
    // Check if the client is invalid.
    if (!IsValidClient(client)) {
        return Plugin_Handled;
    }

    // Check if the client is not eligible.
    if (!(g_iLeaderClient == client || g_iHelperClient == client)) {
        return Plugin_Handled;
    }

    // Check if the client is not alive.
    if (!IsPlayerAlive(client)) {
        return Plugin_Handled;
    }

    // Reset the client's laser history.
    for (int i = 0; i < 3; i++) {
        g_iLaserHistory[client][i] = 0.0;
    }

    // Disable the client's laser.
    g_bLaserEnabled[client] = false;

    return Plugin_Handled;
}

public void LeaderLaser(float start[3], float end[3], int color[4]) {
    // Render the laser.
    //TE_SetupBeamPoints(start, end, CVAR_VLASERBEAM_VMT.GetString(g_eCvarsList.g_sCVAR_VLASERBEAM_VMT, sizeof(g_eCvarsList.g_sCVAR_VLASERBEAM_VMT)), 0, 0, 0, g_eCvarsList.g_fCVAR_LEADER_LASER_REMOVE_DELAY, 2.0, 2.0, 1, 0.0, color, 0);
    TE_SetupBeamPoints(start, end, g_iLaserSprite, 0, 0, 0, g_eCvarsList.g_fCVAR_LEADER_LASER_REMOVE_DELAY, 2.0, 2.0, 1, 0.0, color, 0);

    // Loop through all players.
    int clients[MAXPLAYERS + 1];
    int clientCount = 0;
    for (int client = 1; client <= MaxClients; client++) {
        // Check if the client is invalid.
        if (!IsValidClient(client)) {
            continue;
        }

        // Check if the client has hidden lasers. NOT IN USE
        //if (g_bLaserHidden[client]) {
        //    continue;
        //}

        // Add the client to the list of clients to send the laser to.
        clients[clientCount] = client;
        clientCount++;
    }

    // Send the laser to the clients.
    TE_Send(clients, clientCount);
}

/**
 * TraceEye
 * Traces where a client is looking.
 */
public void TraceEye(int client, float position[3]) {
    // Get the client's eye position.
    float origins[3];
    GetClientEyePosition(client, origins);

    // Get the client's eye angles.
    float angles[3];
    GetClientEyeAngles(client, angles);

    // Trace where the client is looking to a surface.
    TR_TraceRayFilter(origins, angles, MASK_SHOT, RayType_Infinite, TraceEntityFilterPlayer);
    if (TR_DidHit(INVALID_HANDLE)) {
        TR_GetEndPosition(position, INVALID_HANDLE);
    }

    return;
}