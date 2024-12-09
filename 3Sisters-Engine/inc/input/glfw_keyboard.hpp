#pragma once

#ifndef GLFW_KEYBOARD_HPP
#define GLFW_KEYBOARD_HPP

/* Host several functions to allow for keyboard inputs
*/
namespace GLFW{
/* key callback of the keyboard which checks for the given key
* NOTE: Checks if key was pressed
*/
bool getKeyInput(int key);

/* key callback of the keyboard which checks for the given key
* NOTE: Checks if key was pressed, similar to getKeyInput
*/
bool getKeyInputDown(int key);

/* key callback of the keyboard which checks for the given key
* NOTE: Checks if key was released
*/
bool getKeyInputUp(int key);

}

#endif