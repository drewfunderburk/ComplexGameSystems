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

### Installation / Use
Add download instructions here

