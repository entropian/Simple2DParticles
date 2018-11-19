#pragma once
#define GLSL(src) "#version 150 core\n" #src

const char* basicVertSrc = GLSL(
    in vec2 aPosition;
    in vec2 aTexcoord;

    out vec2 vTexcoord;

    void main()
    {
        vTexcoord = aTexcoord;
        gl_Position = vec4(aPosition, 0.0, 1.0);
    }
);

const char* basicFragSrc = GLSL(
    in vec2 vTexcoord;

    uniform sampler2D textureMap;

    out vec4 outColor;
    
    void main()
    {
        outColor = vec4(texture(textureMap, vec2(vTexcoord.x, 1- vTexcoord.y)).rgb, 1.0);
    }
);
