/**
 * @file ColorPair.h
 * @brief File containing the definition of the ColorPair class.
 */

#ifndef WATER_MANAGEMENT_COLORPAIR_H
#define WATER_MANAGEMENT_COLORPAIR_H

#include "unordered_set"
#include "Color.h"
#include <curses.h>
#include <functional>

// Forward declare the Color class
class Color;

/**
 * @class ColorPair
 * @brief Class representing a pair of colors.
 *
 * This class is used to manage pairs of colors in the application. It provides methods to apply, get, activate, and deactivate color pairs.
 */
class ColorPair
{
private:
    short _id;          ///< ID of the color pair
    Color *_foreground; ///< Pointer to the foreground color
    Color *_background; ///< Pointer to the background color

    static short last_pair_;                ///< Static variable to keep track of the last color pair used
    static std::vector<ColorPair *> pairs_; ///< Static vector to store all the color pair objects

    /**
     * @brief Private constructor for the ColorPair class.
     *
     * This constructor is private because we want to control the creation of ColorPair objects through the get and apply methods.
     *
     * @param foreground Pointer to the foreground color
     * @param background Pointer to the background color
     */
    ColorPair(Color *foreground, Color *background);

public:
    /**
     * @brief Static method to apply a color pair.
     *
     * This method creates a new color pair with the given RGB values for the foreground and background colors, stores it, and applies it to the given window.
     *
     * @param win Pointer to the window to apply the color pair to
     * @param fr Red component of the foreground color
     * @param fg Green component of the foreground color
     * @param fb Blue component of the foreground color
     * @param br Red component of the background color
     * @param bg Green component of the background color
     * @param bb Blue component of the background color
     * @return ID of the applied color pair
     */
    static short apply(WINDOW *win, short fr, short fg, short fb, short br, short bg, short bb);

    /**
     * @brief Static method to get a color pair.
     *
     * This method checks if a color pair with the given RGB values for the foreground and background colors already exists. If it does, it returns the ID of the existing color pair. If not, it creates a new color pair, stores it, and returns its ID.
     *
     * @param fr Red component of the foreground color
     * @param fg Green component of the foreground color
     * @param fb Blue component of the foreground color
     * @param br Red component of the background color
     * @param bg Green component of the background color
     * @param bb Blue component of the background color
     * @return ID of the color pair with the given RGB values
     */
    static short get(short fr, short fg, short fb, short br, short bg, short bb);

    /**
     * @brief Static method to activate a color pair.
     *
     * This method activates the color pair with the given ID on the given window.
     *
     * @param win Pointer to the window to activate the color pair on
     * @param id ID of the color pair to activate
     * @return ID of the activated color pair
     */
    static short activate(WINDOW *win, short id);

    /**
     * @brief Static method to deactivate a color pair.
     *
     * This method deactivates the color pair with the given ID on the given window.
     *
     * @param win Pointer to the window to deactivate the color pair on
     * @param id ID of the color pair to deactivate
     * @return ID of the deactivated color pair
     */
    static short deactivate(WINDOW *win, short id);
};

#endif // WATER_MANAGEMENT_COLORPAIR_H