# project4_racing_cubes

History:

April 23, 2016.

Made the Mobius strip, derived and tested the Normal vectors, and attached all the racing cubes on the racing track. (William)

April 27, 2016.

Added moving input handlers.

Added some samples on the racing track.

Added a rear view mirror and connect to output image functions.

Will start to work on adding AI.
(William)

Added a background of space (space.jpg)
For now, code is in the beginning of the Tank Constructor but will be moved to its own function

Added a sun object placed at an arbitrary point in space
(Enrique)

May 1st, 2016.

Added controls for AI Tank 2 and 3.
T,F,G,H and W,A,S,D are used respectively
NOTE: W & S were used for fly and dive of designer tank. Those have been replaced to Z and X

May 18th,2016

TODO


  Make menu
    Check old code to see viewport information
    Check Will's reset, pause and continue code

Functions added:

added StaticObject.h and .cpp which mimics MovingObject but contains "obstacles"
Tank.cpp
-----
createOBB()
createBackground()

added OBB field to Node
deleted mAABB field from Node
deleted Moving Object field since it wasn't used anywhere.
deleted destroyed field

created movObjs map to store Moving Objects
created movObjs map to store Moving Objects

created getMovObj func which gets a movingbject depending on its name //Useful for when moving cubes from World
created getStatObj  func which gets a staticbject depending on its name


change Attach Camera function since class wide variables of AItank as well as mainNode are not used anymore


Added createAICubes
NOTE: Left old method of making AICubes and called it createAICubesOld
When ready, remove function and line count will decrease dramatically

Added menu camera to attach camera

MovingObject.cpp
-----
change constructor to add entity/object name
added obb field
added getOBB
added setOBB

getSceneNode()

setGraphicPosition //Change obb orientation and position

ProjectileManager.cpp
-----
Deleted the checking of eAABB since ProjectileManager is not needed.
Can we delete this class completely?

World.cpp
-----
Deleted the checking of eAABB

added moveCubes function that has the movements along the mobius strip

------

InputHandler

added paramaters to constructor to take in Menu Interface

MainListener

added parameters to constructor to take in Menu Interface

OgrePong

created function for menu camera
made virtual clock start at pause since Menu Screen starts



---------------------------------------------------------------------------
Issues:

Stops at 171 seconds and stays there 10 seconds.
Tried to switch mode to prediction but still was lagging

MTANKNODE IS NOT WORKING CORRECTLY
  Just made mTankNode equal to "U" tank created in createUserTank function
--------------------------------------------------------------------------------

TODO:
We need more arts to decorate the scene!

Make a sun, a sunny/gloomy sky, gound, or some planets and stars (like in the outer space).

Make some levels, and add a score and/or health counting/bar on the overlay.
Add the AI.
