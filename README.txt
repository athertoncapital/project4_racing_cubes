/**
* William H Chuang April 18 2016
* Current progress and implemented features
*/

a. This game will never stop until you hit the "esc".
b. Key up: Move forward.
c. Key down: Move backward.
d. Key Left: turn left.
e. Key Right: turn right.
f. Key W: flying (increasing altitude).
g. Key S: diving (decreasing altitude).

h. If you get too closed to the AI tanks, the tanks will move fast (translate/or simply get some new good places) to hide.
	Also, meanwhile, the AI tank will generate huge fog to soruond you, to block your view, so that you won't know the direction it translates to. 
	(If you don't like the fog, you could set them off by hit the X key.)
i. You have 180 seconds to win your glory records in this great game. After 180seconds, the results will show, and you have 5 seconds to enjoy the view in your glory/ghost mode.

j. You could use two Ogre heads and one red cross to figure out the directions. The Ogre heads have repulsive forece, so be careful.
k. You could increase the vertical velocity of the both projectiles by hitting "V", and decrease it by "C".
l. You could increase the horizontal velocity of the both projectiles by hitting "H", and decrease it by "G".
m. You could capture the rendering viewports by clicking the key "O" to switch on the screenshot camera!

o. The screen shots of the rendering viewport could be turn off, after switching on, by hitting the key "P".
   However, please mind that in this mode, the projectiles won't be able to destroy the AI tanks.
   Nevertheless, this enable function won't affect the AI's detectors, so they still could know where are you, and once yo are getting close they will try their best to hide.
p. The default setting is one snapshot per 10 seconds, but you could change it in the Think function (the modulus) to whatever you want.  