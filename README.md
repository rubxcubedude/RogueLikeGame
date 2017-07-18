I'm trying to implement a RogueLike game in C++ following the python tutorial
from https://www.reddit.com/r/roguelikedev/

I'm Developing this using VS2010
Freeglut is available from http://freeglut.sourceforge.net/

Curent Game State:
Have a player that can move around a map unless blocked by walls
Can draw other entites/npc's on said map
The map is sudo-randomly generated
player can delete other npc's from map
player highlighted FOV

TODO: 
blocking objects(ie column's and/or monsters not letting you move to square)
state system
--fights
--movement