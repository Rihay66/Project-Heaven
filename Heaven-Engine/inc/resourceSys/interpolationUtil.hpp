#pragma once

#ifndef INTERPOLATIONUTIL_HPP
#define INTERPOLATIONUTIL_HPP

//Define a state position that is used to allow for smooth render transitions
struct State{
    //* Note: both values are by default set to zero
    float posX = 0.0f;
    float posY = 0.0f;
};

//Define function that calculates the interpolated state between previous and current states
static State interpolateState(double &alpha, State &previous, State &current){
    //Create a linear interpolation between previous and current states
    State interpolateState;
    interpolateState.posX = current.posX * alpha + previous.posX * (1.0 - alpha);
    interpolateState.posY = current.posY * alpha + previous.posY * (1.0 - alpha);
    return interpolateState;
}

#endif