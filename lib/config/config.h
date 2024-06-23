
#ifndef __CONFIG_H__
#define __CONFIG_H__

// In order to speed up the program and to reduce the size of the executable, you may disable error handlers by commenting out.
// Disable them, only if you are sure that the code is error-free.
#define __COMPILE_ERROR_HANDLERS__

// If you want to use the array implementation of Observer-Subject Design Pattern, keep this defined. 
// If you prefer the linked list implementation, comment out.
#define __OBSERVER_SUBJECT_ARRAY_IMPLEMENTATION__

// You may start the program in full screen.
// #define __FULL_SCREEN__

// It should be defined if you use MacOS.
// #define __APPLE__

#define __NORMAL_VERTEX__   0
#define __TEXTURE_VERTEX__  1
#define __COLOR_VERTEX__    2
#define __MATERIAL_VERTEX__ 3
#define __PYRAMID_VERTEX_TYPE__     __TEXTURE_VERTEX__

#endif // __CONFIG_H__
