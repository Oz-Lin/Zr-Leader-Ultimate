#if defined _leader_included_
  #endinput
#endif
#define _leader_included_

/**
 * Returns current leader
 *
 * @return int    Client index of the leader (-1 = null)
 */
native int Leader_CurrentLeader();
/**
 * Sets the leader
 *
 * @param client    Client index to be set as leader
 */
native void Leader_SetLeader(int client);


// Added this for compatibility with other plugins that involves helper (2nd leader)
/**
 * Returns current helper (2nd leader)
 *
 * @return int    Client index of the helper leader (-1 = null)
 */
native int Leader_CurrentLeader_Helper();
/**
 * Sets the helper (2nd leader)
 *
 * @param client    Client index to be set as helper leader
 */
native void Leader_SetLeader_Helper(int client);
