# Arduino Temperature Fan Speed Controller

This small project was designed as an upgrade my 3D printer with a speed controller so I can make it even quieter. Unfortunately, I shorted the PCB design I was working with and got too busy to continue with the project. I believe the original code was designed for an Arduino Nano but I concluded later an ATMega2560 with the extra hardware timers would be more appropriate for this application.

Setup for Clion + PlatformIO pluggin:

1) Download repository
2) Unpack to your location of choice
3) Open project in Clion
4) right click "platformio.ini" in project browser
5) select "re-init"
6) repeat step 5 if you encounter an error (usually caused by Cmakelist.txt since it does not exist yet)
7) select your build enviroment from the configurations in the upper right hand drop down menu
8) build/upload/revise to your hearts content!
