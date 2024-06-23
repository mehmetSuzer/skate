
#ifndef __CONFIG_H__
#define __CONFIG_H__

// In order to speed up the program and to reduce the size of the executable, you may disable error handlers by commenting out.
// Disable them, only if you are sure that the code is error-free.
#define COMPILE_ERROR_HANDLERS

// If you want to use the array implementation of Observer-Subject Design Pattern, keep this defined. 
// If you prefer the linked list implementation, comment out.
#define OBSERVER_SUBJECT_ARRAY_IMPLEMENTATION

// You may start the program in full screen.
// #define FULL_SCREEN

// It should be defined if you use MacOS.
// #define APPLE

#define BASIC_VERTEX    0
#define NORMAL_VERTEX   1
#define TEXTURE_VERTEX  2
#define COLOR_VERTEX    3
#define OBJECT_VERTEX_TYPE     TEXTURE_VERTEX

#endif // __CONFIG_H__
