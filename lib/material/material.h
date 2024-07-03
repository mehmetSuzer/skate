
#ifndef __MATERIAL_H__
#define __MATERIAL_H__

#include "glm.hpp"

typedef struct {
    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;
    float shininess;
} Material; 

namespace material {
                                  //                    AMBIENT               /                         DIFFUSE                     /                          SPECULAR                    /  SHININESS  //
                                  //            RED      GREEN       BLUE     /             RED          GREEN           BLUE       /               RED          GREEN           BLUE      /             //  
    const Material emerald          = {glm::vec3(0.0215f,   0.1745f,    0.0215f),   glm::vec3(0.07568f,     0.61424f,       0.07568f),      glm::vec3(0.633f,       0.727811f,      0.633f),        77.0f};
    const Material jade             = {glm::vec3(0.135f,    0.2225f,    0.1575f),   glm::vec3(0.54f,        0.89f,          0.63f),         glm::vec3(0.316228f,    0.316228f,      0.316228f),	    13.0f};
    const Material obsidian         = {glm::vec3(0.05375f,  0.05f,      0.06625f),  glm::vec3(0.18275f,     0.17f,          0.22525f),      glm::vec3(0.332741f,    0.328634f,      0.346435f),     38.0f};
    const Material pearl            = {glm::vec3(0.25f,     0.20725f,   0.20725f),  glm::vec3(1.0f,         0.829f,         0.829f),        glm::vec3(0.296648f,    0.296648f,      0.296648f),     11.0f};
    const Material ruby             = {glm::vec3(0.1745f,   0.01175f,   0.01175f),  glm::vec3(0.61424f,     0.04136f,       0.04136f),      glm::vec3(0.727811f,    0.626959f,      0.626959f),     77.0f};
    const Material turquoise        = {glm::vec3(0.1f,      0.18725f,   0.1745f),   glm::vec3(0.396f,       0.74151f,       0.69102f),      glm::vec3(0.297254f,    0.30829f,       0.306678f),     13.0f};
    const Material brass            = {glm::vec3(0.329412f, 0.223529f,  0.027451f), glm::vec3(0.780392f,    0.568627f,      0.113725f),     glm::vec3(0.992157f,    0.941176f,      0.807843f),     28.0f};
    const Material bronze           = {glm::vec3(0.2125f,   0.1275f,    0.054f),    glm::vec3(0.714f,       0.4284f,        0.18144f),      glm::vec3(0.393548f,    0.271906f,      0.166721f),     26.0f};
    const Material chrome           = {glm::vec3(0.25f,     0.25f,      0.25f),     glm::vec3(0.4f,         0.4f,           0.4f),          glm::vec3(0.774597f,    0.774597f,      0.774597f),     77.0f};
    const Material copper           = {glm::vec3(0.19125f,  0.0735f,    0.0225f),   glm::vec3(0.7038f,      0.27048f,       0.0828f),       glm::vec3(0.256777f,    0.137622f,      0.086014f),     13.0f};
    const Material gold             = {glm::vec3(0.24725f,  0.1995f,    0.0745f),   glm::vec3(0.75164f,     0.60648f,       0.22648f),      glm::vec3(0.628281f,    0.555802f,      0.366065f),     51.0f};
    const Material silver           = {glm::vec3(0.19225f,  0.19225f,   0.19225f),  glm::vec3(0.50754f,     0.50754f,       0.50754f),      glm::vec3(0.508273f,    0.508273f,      0.508273f),     51.0f};
    const Material blackPlastic     = {glm::vec3(0.0f,      0.0f,       0.0f),      glm::vec3(0.01f,        0.01f,          0.01f),         glm::vec3(0.50f,        0.50f,          0.50f),         32.0f};
    const Material cyanPlastic      = {glm::vec3(0.0f,      0.1f,       0.06f),     glm::vec3(0.0f,         0.50980392f,    0.50980392f),   glm::vec3(0.50196078f,  0.50196078f,    0.50196078f),   32.0f};
    const Material greenPlastic     = {glm::vec3(0.0f,      0.0f,       0.0f),      glm::vec3(0.1f,         0.35f,          0.1f),          glm::vec3(0.45f,        0.55f,          0.45f),         32.0f};
    const Material redPlastic       = {glm::vec3(0.0f,      0.0f,       0.0f),      glm::vec3(0.5f,         0.0f,           0.0f),          glm::vec3(0.7f,         0.6f,           0.6f),          32.0f};
    const Material whitePlastic     = {glm::vec3(0.0f,      0.0f,       0.0f),      glm::vec3(0.55f,        0.55f,          0.55f),         glm::vec3(0.70f,        0.70f,          0.70f),         32.0f};
    const Material yellowPlastic    = {glm::vec3(0.0f,      0.0f,       0.0f),      glm::vec3(0.5f,         0.5f,           0.0f),          glm::vec3(0.60f,        0.60f,          0.50f),         32.0f};
    const Material blackRubber      = {glm::vec3(0.02f,     0.02f,      0.02f),     glm::vec3(0.01f,        0.01f,          0.01f),         glm::vec3(0.4f,         0.4f,           0.4f),          10.0f};
    const Material cyanRubber       = {glm::vec3(0.0f,      0.05f,      0.05f),     glm::vec3(0.4f,         0.5f,           0.5f),          glm::vec3(0.04f,        0.7f,           0.7f),          10.0f};
    const Material greenRubber      = {glm::vec3(0.0f,      0.05f,      0.0f),      glm::vec3(0.4f,         0.5f,           0.4f),          glm::vec3(0.04f,        0.7f,           0.04f),         10.0f};
    const Material redRubber        = {glm::vec3(0.05f,     0.0f,       0.0f),      glm::vec3(0.5f,         0.4f,           0.4f),          glm::vec3(0.7f,         0.04f,          0.04f),         10.0f};
    const Material whiteRubber      = {glm::vec3(0.05f,     0.05f,      0.05f),     glm::vec3(0.5f,         0.5f,           0.5f),          glm::vec3(0.7f,         0.7f,           0.7f),          10.0f};
    const Material yellowRubber     = {glm::vec3(0.05f,     0.05f,      0.0f),      glm::vec3(0.5f,         0.5f,           0.4f),          glm::vec3(0.7f,         0.7f,           0.04f),         10.0f};
}

#endif // __MATERIAL_H__
