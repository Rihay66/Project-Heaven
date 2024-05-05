#pragma once

#ifndef INTERPOLATION_UTIL_HPP
#define INTERPOLATION_UTIL_HPP

// define a state position that is used to allow for smooth render transitions
struct State{
    //* Note: both values are by default are set to zero
    float posX = 0.0f;
    float posY = 0.0f;
};

// define function that calculates the interpolated state between previous and current states
static void interpolateState(State &state, double &alpha, State &previous, State &current){
    // create a linear interpolation between previous and current states
    state.posX = current.posX * alpha + previous.posX * (1.0 - alpha);
    state.posY = current.posY * alpha + previous.posY * (1.0 - alpha);
}

#endif