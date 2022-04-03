# Zr-Leader2-Anubis-Edition
 
### Improved version of zombiereloaded plugin with support for CS:GO and CS:S

* This plugin is an updated version of AntiTeal plugin, under a new author.

* Test & Compile, SouceMod 1.10.0-6492
* Sorry for my English.

* Author Anubis.
* Version = 3.2

### Decription:Zr-Leader2-Anubis-Edition

* Allows for an admin to select or for regular players to vote for a human to be the leader for the current round. 
* The leader gets special perks, like the ability to put defend here / follow me sprites above their head, 
place defend markers, toggle a rainbow beacon, and maybe more in the future.
* Redesigned menu.
* Now if you type !voteleader without typing the name of the player, a player menu will open to vote.
* Translation file added, just edit.
* It is now possible to disable the definition in which admin typed !leader and became a leader automatically.

##New

* It is now possible to vote to remove the current leader.
* Possibility to remain leader until the map is changed.
* Possibility of placing several markers.
* The leader can mute too many players for a set time

### Server ConVars

* sm_leader_allow_votes - Determines whether players can vote for leaders. (Default: "1")
* sm_leader_defend_vmt - The defend here .vmt file (Default: "materials/sg/sgdefend.vmt")
* vsm_leader_defend_vtf - The defend here .vtf file (Default: "materials/sg/sgdefend.vtf")
* sm_leader_follow_vmt - The follow me .vmt file (Default: "materials/sg/sgfollow.vtf")
* sm_leader_follow_vtf - The follow me .vtf file (Default: "materials/sg/sgfollow.vtf")
* sm_leader_admin_leader - Determines whether Admin can access menu leader, without voting. (Default: "1")

##New

* sm_leader_remove_leader_votes - Determines whether players can vote for remove leaders. (Default: "1")
* sm_leader_max_markers - Determines maximum number of markers. Max 20 (Default: "5")
* sm_leader_roundend_rleader - Determine whether to remove the leader at the end of the round. (Default: "1")

### Commands

* sm_leader - Access the leader menu OR Set a player to be leader
* sm_le - Access the leader menu OR Set a player to be leader
* sm_currentleader - Shows the current leader.
* sm_cl - Shows the current leader.
* sm_voteleader - Votes for the specified player to be leader. Required votes is current player count / 10.
* sm_vl - Votes for the specified player to be leader. Required votes is current player count / 10.
* sm_lmute - Leader mute command.

##New

* sm_voteremoveleader - Votes to remove the leader. The votes needed are the current player count / 10.
* sm_vrl - Votes to remove the leader. The votes needed are the current player count / 10.

###Thanks.

* AntiTeal - Leader2

#Admin Commands
* sm_removeleader - Removes the current leader.
* sm_rl - Removes the current leader.

![alt text](https://i.ibb.co/tD28HrW/11.jpg)
![alt text](https://i.ibb.co/m9wmqRC/22.jpg)