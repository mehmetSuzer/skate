
#ifndef __CONFIG_H__
#define __CONFIG_H__

// In order to ensure that glad is imported before GLFW, include this header file.
// Do not manually include glad or GLFW
#include "glad.h"
#include <GLFW/glfw3.h>

// If you want to use the array implementation of Observer-Subject Design Pattern, keep this defined. 
// If you prefer the linked list implementation, comment out.
#define __OBSERVER_SUBJECT_ARRAY_IMPLEMENTATION__

// Starts the program in full screen
// #define __FULL_SCREEN__

// Enables shader releated debug info (compilation-linking)
#define __SHADER_DEBUG__

// Disables VSYNC and prints FPS
#define __FPS__

// Maximum number of light casters that can be in a scene.
// Other light casters are ignored.
// If you update this, update shaders and the uniform buffer object as well.
#define MAX_LIGHT_CASTER_NUMBER 8

#endif // __CONFIG_H__
