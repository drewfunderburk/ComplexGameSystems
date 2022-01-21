# Modular Combat Platform

### Description
The Modular Combat Platform is an all-in-one solution for creating 
modular combat oriented objects in Unreal Engine that need to literally 
be the sum of their parts. Developers are equipped to specify the stats of their 
creation with modular pieces, whether it be a spaceship or a castle. 
It is highly extensible for custom implementations.

The Modular Combat Platform is written in Unreal Engine 4 and depends 
upon it to function. No other libraries are needed

The system consists of two Actor Components to handle all of the heavy lifting: 
Hulls and Hardpoints.
- *A Hull is a platform upon which hardpoints are placed. 
   It handles the collection and implementation of it's hardpoint's stats*
- *A Hardpoint is a modular piece referenced by a Hull to alter its stats.*

Each hull serves as a parent to keep track of its hardpoints as well as a 
central location from which to retrieve stats like:
- *Speed*
- *Maneuverability*
- *Weight*
- *Health*

These two Actor Components are used as a springboard for developers in the 
creation of their own hulls and hardpoints, handling integration and framework 
so developers can focus on stats and gameplay.

### Installation
- Download the latest release [here](https://github.com/drewfunderburk/ComplexGameSystems/releases)
- Unzip MCP_Source.zip and copy its contents into your source directory.
- Change `COMPLEXGAMESYSTEMS_API` in each header file to `YOURPROJECTNAME_API`.
- Open your project's solution and add the new files.
- Rebuild your project, and you should now see the MCP classes in your editor.

### How to use
- Create a DataAsset that derives from UMCPStats.
  This asset will allow you to specify the stats that an entire system will use.
- Create an Actor and add an MCPHull Actor Component to it.
  This will serve as your "Hub" for stats and hardpoints.
- In the details panel for the MCPHardpoint component, assign the DataAsset you created
  to the stats asset variable. This will update the MCPHull's base stats to reflect
  this system's stats.
- Set the MCPHull's base stats to the point you would like them to be before any
  hardpoints are added. (Note: As an MCPHull cannot get its hardpoints in editor,
  the stats variable will be the same as the base stats until the project enters play).
- Add an MCPHardpoint Actor Component to the Actor and assign the same DataAsset to its
  stats asset variable. Its stats will update to reflect this system's stats.
- Set the MCPHardpoint's stats so that they reflect how you would like this hardpoint
  to modify the MCPHull at runtime.
- Upon running the project, an in-level MCPHull will gather all MCPHardpoints on itself
  and any child actors and modify its stats accordingly. These stats can then be accessed
  outside the system by your own gameplay systems.

> Important Notes:
> 
> The functionality of this system is limited in editor, and while base stats can be
> edited and hardpoints changed the actual stats should be checked while the game is
> playing.
> 
> All MCPHulls and MCPHardpoints that need to function together in a system must use
> the same DataAsset, as this is how they judge if they are compatible and can expect
> to have the same stats.
