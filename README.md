# Zr-Leader-Ultimate
 
### Improved version of zombiereloaded plugin with support for CS:GO and CS:S

* Test & Compile, SouceMod 1.10.0-6528
* Sorry for my English.

* Author Anubis, modified by Oz-Lin
* Version = 1.4.2

### Decription:Zr-Leader-Ultimate

* Allows for an admin to select or for regular players to vote for a human to be the leader for the current round. 
* The leader gets special perks, like the ability to put defend here / follow me sprites above their head, 
place defend markers, toggle a rainbow beacon, and maybe more in the future.
* Redesigned menu.
* Now if you type !voteleader without typing the name of the player, a player menu will open to vote.
* Translation file added, just edit.
* It is now possible to disable the definition in which admin typed !leader and became a leader automatically.

## New

* It is now possible to vote to remove the current leader.
* Possibility to remain leader until the map is changed.
* Possibility of placing several markers. 
* The leader can mute too many players for a set time
* The leader can now appoint a helper.
* The leader and helper can shine through walls.
* Added cvar to disable plugin. "sm_leader_disable"
* Calling the leader menu panel no longer blocks radar and money indicator.
* Markers are now spawned at crosshair, not at leader's position.
* [Leader] Clantag override for both leader and helper (Ref: [Entwatch clantag module](https://github.com/darkerz7/CSGO-Plugins/blob/master/EntWatch_DZ/addons/sourcemod/scripting/entwatch/module_clantag.inc))

### Server ConVars

* sm_leader_disable - Disable Plugin. 1 = On 0 = Off (Default: "1")
* sm_leader_allow_votes - Determines whether players can vote for leaders. (Default: "1")
* sm_leader_defend_vmt - The defend here .vmt file (Default: "materials/sg/sgdefend.vmt")
* sm_leader_defend_vtf - The defend here .vtf file (Default: "materials/sg/sgdefend.vtf")
* sm_leader_follow_vmt - The follow me .vmt file (Default: "materials/sg/sgfollow.vtf")
* sm_leader_follow_vtf - The follow me .vtf file (Default: "materials/sg/sgfollow.vtf")
* sm_leader_spawn_vmt - The zombie spawn .vmt file (Default: "materials/sg/sgspawn.vtf")
* sm_leader_spawn_vtf - The zombie spawn .vtf file (Default: "materials/sg/sgspawn.vtf")
* sm_leader_arrow_vmt - The generic arrow me .vmt file (Default: "materials/gfl/marker.vtf")
* sm_leader_arrow_vtf - The generic arrow .vtf file (Default: "materials/gfl/marker.vtf")
* sm_leader_no_doorhug_vmt - The follow me .vmt file (Default: "materials/sg/nodoorhug.vtf")
* sm_leader_no_doorhug_vtf - The follow me .vtf file (Default: "materials/sg/nodoorhug.vtf")
* sm_leader_admin_leader - Determines whether Admin can access menu leader, without voting. (Default: "1")
* sm_leader_timer_removemute - Determine how long the players were speechless after applying the Mute All (Avoid cheating leader). (Default: "15.0")
* sm_leader_glow_color - Determines R G B glow colors for Leader\nFormat should be \"R G B\" (with spaces). (Default: "72 96 144")


## New

* sm_leader_remove_leader_votes - Determines whether players can vote for remove leaders. (Default: "1")
* sm_leader_max_markers - Determines maximum number of markers. Max 20 (Default: "5")
* sm_leader_roundend_rleader - Determine whether to remove the leader at the end of the round. (Default: "1")

### Commands

* sm_leader - Access the leader menu OR Set a player to be leader
* sm_le - Access the leader menu OR Set a player to be leader
* sm_l - Access the leader menu OR Set a player to be leader
* sm_currentleader - Shows the current leader.
* sm_cl - Shows the current leader.
* sm_voteleader - Votes for the specified player to be leader. Required votes is current player count / 10.
* sm_vl - Votes for the specified player to be leader. Required votes is current player count / 10.
* sm_lmute - Leader mute command.

## New

* sm_voteremoveleader - Votes to remove the leader. The votes needed are the current player count / 10.
* sm_vrl - Votes to remove the leader. The votes needed are the current player count / 10.

## Shortcuts
* Double press +lookatweapon (default as F key) twice quickly to call the leader marker menu.

### Thanks.

* AntiTeal - Leader2

# Admin Commands
* sm_removeleader - Removes the current leader.
* sm_rl - Removes the current leader.

![alt text](https://raw.githubusercontent.com/Stewart-Anubis/Zr-Leader-Ultimate/main/img/img1.jpg)
![alt text](https://raw.githubusercontent.com/Stewart-Anubis/Zr-Leader-Ultimate/main/img/img2.jpg)
![alt text](https://raw.githubusercontent.com/Stewart-Anubis/Zr-Leader-Ultimate/main/img/img3.jpg)
![alt text](https://raw.githubusercontent.com/Stewart-Anubis/Zr-Leader-Ultimate/main/img/img4.jpg)
![alt text](https://raw.githubusercontent.com/Stewart-Anubis/Zr-Leader-Ultimate/main/img/img5.jpg)
![alt text](https://raw.githubusercontent.com/Stewart-Anubis/Zr-Leader-Ultimate/main/img/img6.jpg)
