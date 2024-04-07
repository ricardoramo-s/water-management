/**
 * @file Color.h
 * @brief File containing the definition of the Color class.
 */

#ifndef WATER_MANAGEMENT_COLOR_H
#define WATER_MANAGEMENT_COLOR_H

#include "vector"
#include "ColorPair.h"
#include "ncurses.h"

/**
 * @class Color
 * @brief Class representing a color.
 *
 * This class is used to manage colors in the application. It provides a method to get a color object given its RGB values.
 */
class Color {
private:
    short _r, g_, b_, id_; ///< RGB values and id of the color
    static short last_color_; ///< Static variable to keep track of the last color used
    static std::vector<Color*> colors_; ///< Static vector to store all the color objects

    /**
     * @brief Private constructor for the Color class.
     *
     * This constructor is private because we want to control the creation of Color objects through the get method.
     *
     * @param r Red component of the color
     * @param g Green component of the color
     * @param b Blue component of the color
     */
    Color(short r, short g, short b);
public:
    friend class ColorPair; ///< ColorPair class has access to private members of Color

    /**
     * @brief Static method to get a Color object.
     *
     * This method checks if a color with the given RGB values already exists. If it does, it returns the existing color. If not, it creates a new color, stores it, and returns it.
     *
     * @param red Red component of the color
     * @param green Green component of the color
     * @param blue Blue component of the color
     * @return Pointer to the Color object with the given RGB values
     */
    static Color* get(short red, short green, short blue);
};


#endif //WATER_MANAGEMENT_COLOR_H