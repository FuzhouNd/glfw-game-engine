#pragma once

#include <vector>

#include "glew.h"
#include "glfw3.h"
#include "glm.hpp"

#include "texture.h"
#include "program.h"
#include "entity.h"
#include "shape.h"

namespace GGE
{
    class Mesh : public Entity
    {
    public:
        // Constructor
        // TODO: Figure out what the best way to pass draw type is
        Mesh(std::vector<GLfloat> points, std::vector<GLfloat> textureCoords, Texture *texture,
                Program *program, GLenum drawType = GL_STATIC_DRAW, GLenum drawShape = GL_TRIANGLES);

        // Constructor for use with Model
        // TODO: Remove other constructors
        Mesh(std::vector<GLfloat> points);

        // Constructor to load from file
        Mesh(const char * filename, const char * directory, Program *program);

        // Destructor
        ~Mesh();

        // Draw mesh
        void draw();

        // Getter for model matrix
        glm::mat4 getModelMatrix();

        // Override movement functions
        glm::vec3 move(glm::vec3 translation);

        glm::vec3 setPosition(glm::vec3 newPosition);

    private:
        // Common initialization code
        void init();

        // Shapes that make up mesh
        std::vector<Shape *> shapes;

        // Points in triangle
        // TODO: See if there is something better to use for these
        std::vector<GLfloat> points;

        // Model matrix for mesh
        glm::mat4 modelMatrix;

        // Texture for mesh
        Texture *texture;

        // Program to render mesh
        Program *program;

        // Texture coords for mesh
        std::vector<GLfloat> textureCoords;

        // vao object for mesh
        GLuint vao;

        // Draw type (static, dynamic, etc.)
        GLenum drawType;
        // Shape to draw (triangle, triangle strips, etc.)
        GLenum drawShape;
    };
}