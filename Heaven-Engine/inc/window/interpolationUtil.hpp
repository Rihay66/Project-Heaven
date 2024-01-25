#pragma once

#ifndef INTERPOLATIONUTIL_HPP
#define INTERPOLATIONUTIL_HPP

//Define a state position that is used to allow for smooth render transitions
static struct State{
    //* Note: both values are by default set to zero
    float posX;
    float posY;
} instance = {};

//Define function that calculates the interpolated state between previous and current states
static State interpolateState(double alpha, State &previous, State &current){
    //Create a linear interpolation between previous and current states
    State interpolateState;
    interpolateState.posX = previous.posX * (1.0 - alpha) + current.posX * alpha;
    interpolateState.posY = previous.posY * (1.0 - alpha) + current.posY * alpha;
    return interpolateState;
}

#endif