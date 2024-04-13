#include "Buffer.h"
#include "curses.h"
#include "colors/ColorPair.h"
#include "pallets/gruvbox.h"

Buffer::Buffer() : Component(getmaxy(stdscr), getmaxx(stdscr), 0, 0), next_buffer_(nullptr), previous_buffer_(nullptr) {}

Buffer::Buffer(int height, int width, int y, int x) : Component(height, width, y, x), next_buffer_(nullptr), previous_buffer_(nullptr) {}

void Buffer::select_component(Component *component)
{
    previously_selected_component_ = currently_selected_component_;
    currently_selected_component_ = component;
}

void Buffer::swap_selected_component()
{
    std::swap(currently_selected_component_, previously_selected_component_);
}

void Buffer::select_previous_component()
{
    currently_selected_component_ = previously_selected_component_;
}

Buffer *Buffer::get_next_buffer()
{
    Buffer *b = next_buffer_;
    next_buffer_ = nullptr;

    return b;
}

void Buffer::previous_buffer(Buffer *buffer)
{
    previous_buffer_ = buffer;
}

void Buffer::quit()
{
    quit_ = true;
}

bool Buffer::to_quit() const
{
    return quit_;
}