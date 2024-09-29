#ifndef GAME_SHAPES_H
#define GAME_SHAPES_H

#include <VertexBuffer.h>

static const TexturedUnlit Square[] =
{
    { { -50.0f, -50.0f, 0.0f }, { 1.0f, 0.0f, 0.0f } , { 0.0f, 0.0f } },//bottom left
    { { 50.0f, -50.0f, 0.0f }, { 0.0f, 1.0f, 0.0f } , { 1.0f, 0.0f } },//bottom right
    { { 50.0f, 50.0f, 0.0f }, { 0.0f, 0.0f, 1.0f } , { 1.0f, 1.0f } },//top right
    { { -50.0f, -50.0f, 0.0f }, { 1.0f, 0.0f, 0.0f } , { 0.0f, 0.0f } },//bottom left
    { { -50.0f, 50.0f, 0.0f }, { 1.0f, 1.0f, 0.0f } , { 0.0f, 1.0f } },//top left
    { { 50.0f, 50.0f, 0.0f }, { 0.0f, 0.0f, 1.0f } , { 1.0f, 1.0f } },//top right
};

#endif // GAME_SHAPES_H
