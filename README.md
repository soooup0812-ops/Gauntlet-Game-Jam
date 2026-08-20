# Gauntlet-Game-Jam
Raylib included to render windows and graphics

The game is called Ambatutoss, based off a traditional malaysian game called Batu Seremban. It connects to malaysia day by being a malaysian traditional game (duh).

The game mechanics are basically tossing a stone in the air and picking up all stones on the ground before catching the falling stone. That's it. I planned to make it a roguelite by adding modifiers and a round system but 
due to time constraints I couldn't add too much modifiers.

To build it and run it, do cmake -B build then cmake --build build , then run it by doing ./build/Ambatutoss
Libraries you need installed are uhh none? The cmakelists should fetch raylib on its own. 
I chose raylib because it was mentioned a lot during the workshop period, and a more experienced senior suggested it due to its simplicity and higher-level functions. I only used the library for rendering and drawing the windows / graphics.

I tried to apply most of what I learned in week one to every file, including m_classMembers, const variables where no changes are needed, pragma once in every hpp, vector containers. But due to the game design itself being more simplistic in terms of data types (I mostly abused boolean), class designs, dontainers, patterns, algorithms and such were not really necessary. NO TESTS WERE DONE because I had no time due to being unfamiliar with C++ even after the weeklong workshop.

I cut a lot of modifiers and buffs/skills, which I feel would've been really cool to do. As for what I'd do differently, a lot. I think my structural design is overall really cluttered due to littering update functions with a ton of stuff, stone handling was not done well, so I'd probably do a structural overhaul. Aside from that, I also wanted to add SFX and music, alongside cooler sprites and a better physics system, but oh well.

Overall I had a lot of fun this GameJam, though there were quite a lot of setbacks this time around cuz I'm doing a GameJam as a programmer for the first time (SOLO WITHOUT AN ENGINE?? WHAT??) but I really appreciate the experience and the friends I've made throughout this event. <3