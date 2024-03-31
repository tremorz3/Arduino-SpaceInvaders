![SpaceInvadersImm](https://external-content.duckduckgo.com/iu/?u=http%3A%2F%2Fwww.classicgaming.cc%2Fclassics%2Fspace-invaders%2Fimages%2Fspace-invaders-logo.png&f=1&nofb=1&ipt=051a2e095806332144157d22da98c1d93aed63e018be97ba46a4b1fca2d6e029&ipo=images)
## SpaceInvaders
Simple Arduino project to play space invaders on an OLED display.
## Components
- 1 x OLED display SSD1306 128x64
- 1 x 10kΩ trimmer
- 1 x 10kΩ resistor
- 1 x active buzzer
- 1 x button
- 1 x breadboard
- 1 x Arduino Uno
## Description
I adapted the structure of this project from [this video](https://youtu.be/Tvitd4-NZ30), making several modifications and additions. In the original project, the alien could only move horizontally from left to right. 
However, in this version, the alien can move back and forth towards the ship. If the alien reaches the ship, the game ends, and the points reset to 0. 
Additionally, I incorporated an active buzzer to produce sound effects whenever a missile is fired or the alien is hit.
## Notes
You will need to install the U8G2 libraries. In the code.ino file, you must edit line 34. I used this [OLED display](https://amzn.eu/d/e6FCfjY), so line 34 corresponds to this specific display model. If you are using a different model, you need to 
replace it with the correct one by searching for it in the Arduino IDE menu bar (`File->Examples->U8G2->full_buffer->HelloWorld`). In the HelloWorld file, you will find several commented lines representing various models.
Once you find the line corresponding to your display, copy and paste it into the code.ino file.

I'll make some changes in the future, like adding a game over screen and a startup screen.
