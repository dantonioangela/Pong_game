# Pong game
<p align="center">
 <img alt="Languages" src="https://img.shields.io/badge/Languages-C | Assembly-orange"/>
 <img alt="Status" src="https://img.shields.io/badge/development-completed-green"/>
</p>
Extra points projects for the course of "Architetture dei Sistemi di Elaborazione" (Computer Architectures) at Politecnico di Torino.

The project consists in the implementation on an embedded platform of the popular game "pong game" in c language. This version runs on the NXP LandTiger Board equipped with the LPC1768 microcontroller.  

## Brief description

The user can guide a ball via a paddle trying not to drop it.

More specifically:
- To start a game press KEY1
- To pause KEY2 
- To start a game after losing INT0.  

The user controls the paddle horizontally only using the potentiometer, every time the ball hits the paddle the score will increase by 5. Once the initial record of 100 is reached the score will increase by 10 points. 
If the ball passes the paddle the game is lost.

Take a look at the ```doc``` folder for a complete description of the specifications. 

## How to use
The project was developed on Keil uVision 5 running on a Windows 10 virtual machine. 

To use it, simply clone the repository on your machine 

``` git clone https://github.com/PronElle/Blind-Labyrinth```
and open it with Keil uVision (double click on ```sample.uvprojx``` file).
