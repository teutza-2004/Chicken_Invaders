#include "lab_m1/Tema1/object2D.h"

#include <vector>

#include "core/engine.h"
#include "utils/gl_utils.h"

Mesh* object2D::CreateSquare(
    const std::string &name,
    glm::vec3 leftBottomCorner,
    float length,
    glm::vec3 color,
    bool fill)
{
    glm::vec3 corner = leftBottomCorner;

    std::vector<VertexFormat> vertices =
    {
        VertexFormat(corner, color),
        VertexFormat(corner + glm::vec3(length, 0, 0), color),
        VertexFormat(corner + glm::vec3(length, length, 0), color),
        VertexFormat(corner + glm::vec3(0, length, 0), color)
    };

    Mesh* square = new Mesh(name);
    std::vector<unsigned int> indices = { 0, 1, 2, 3 };

    if (!fill) {
        square->SetDrawMode(GL_LINE_LOOP);
    } else {
        // Draw 2 triangles. Add the remaining 2 indices
        indices.push_back(0);
        indices.push_back(2);
    }

    square->InitFromData(vertices, indices);
    return square;
}

Mesh* object2D::CreateHeart(
    const std::string& name,
    glm::vec3 leftBottomCorner,
    float length,
    glm::vec3 color,
    bool fill)
{
    glm::vec3 corner = leftBottomCorner + glm::vec3(length / 2, 0, 0);
    glm::vec3 circleCenter1 = corner + glm::vec3(-length / 4, length / 2, 0);
    glm::vec3 circleCenter2 = corner + glm::vec3(length / 4, length / 2, 0);

    std::vector<VertexFormat> vertices =
    {
        VertexFormat(corner, color),
        VertexFormat(corner + glm::vec3(length / 2, length / 2, 0), color),
        VertexFormat(corner + glm::vec3(- length / 2, length / 2, 0), color),
        VertexFormat(circleCenter1, color),
        VertexFormat(circleCenter2, color)
    };

    Mesh* heart = new Mesh(name);
    std::vector<unsigned int> indices = { 0, 1, 2 };

    float radius = length / 4;
    // cerc dreapta
    // conturul cercului
    for (int i = 0; i <= 100; i++) {
        float angle = glm::pi<float>() * i / 100;
        float x = circleCenter1.x + radius * cos(angle);
        float y = circleCenter1.y + radius * sin(angle);
        vertices.push_back(VertexFormat(glm::vec3(x, y, 0), color));
    }

    if (fill) {
        for (int i = 5; i < 105; i++) { // triunghiuri pentru umplere
            indices.push_back(3);
            indices.push_back(i);
            indices.push_back(i + 1);
        }
    }
    else { // contur
        for (int i = 5; i < 105; i++) {
            indices.push_back(i);
        }
        indices.push_back(5);
    }

    // cerc stanga
    // conturul cercului
    for (int i = 0; i <= 100; i++) {
        float angle = glm::pi<float>() * i / 100;
        float x = circleCenter2.x + radius * cos(angle);
        float y = circleCenter2.y + radius * sin(angle);
        vertices.push_back(VertexFormat(glm::vec3(x, y, 0), color));
    }

    if (fill) {
        for (int i = 105; i < 205; i++) { // triunghiuri pentru umplere
            indices.push_back(3);
            indices.push_back(i);
            indices.push_back(i + 1);
        }
    }
    else { // contur
        for (int i = 105; i < 205; i++) {
            indices.push_back(i);
        }
        indices.push_back(5);
    }

    if (!fill) {
        heart->SetDrawMode(GL_LINE_LOOP);
    }

    heart->InitFromData(vertices, indices);
    return heart;

}

Mesh* object2D::CreateTriangle(
    const std::string& name,
    glm::vec3 leftBottomCorner,
    float length,
    glm::vec3 color,
    bool fill)
{
    glm::vec3 corner = leftBottomCorner;

    std::vector<VertexFormat> vertices =
    {
        VertexFormat(corner, color),
        VertexFormat(corner + glm::vec3(length, 0, 0), color),
        VertexFormat(corner + glm::vec3(0, length, 0), color)
    };

    Mesh* triangle = new Mesh(name);
    std::vector<unsigned int> indices = { 0, 1, 2 };

    if (!fill) {
        triangle->SetDrawMode(GL_LINE_LOOP);
    }

    triangle->InitFromData(vertices, indices);
    return triangle;
}

Mesh* object2D::CreateStartButton(
    const std::string& name,
    glm::vec3 leftBottomCorner,
    float length,
    glm::vec3 color,
    bool fill)
{
    glm::vec3 corner = leftBottomCorner;

    std::vector<VertexFormat> vertices =
    {
        VertexFormat(corner, color),
        VertexFormat(corner + glm::vec3(length, 0, 0), color),
        VertexFormat(corner + glm::vec3(length, length, 0), color),
        VertexFormat(corner + glm::vec3(0, length, 0), color)
    };

    Mesh* square = new Mesh(name);
    std::vector<unsigned int> indices = { 0, 1, 3, 2 };

    if (!fill) {
        square->SetDrawMode(GL_LINE_LOOP);
    }
    else {
        // Draw 2 triangles. Add the remaining 2 indices
        indices.push_back(3);
        indices.push_back(0);
    }

    square->InitFromData(vertices, indices);
    return square;
}

Mesh* object2D::CreateCircle(
    const std::string& name,
    glm::vec3 center,
    float radius,
    glm::vec3 color,
    bool fill)
{
    std::vector<VertexFormat> vertices =
    {
        VertexFormat(center, color)
    };
    std::vector<unsigned int> indices;

    // conturul cercului
    for (int i = 0; i <= 100; i++) {
        float angle = 2 * glm::pi<float>() * i / 100;
        float x = center.x + radius * cos(angle);
        float y = center.y + radius * sin(angle);
        vertices.push_back(VertexFormat(glm::vec3(x, y, 0), color));
    }

    if (fill) {
        for (int i = 1; i <= 100; i++) { // triunghiuri pentru umplere
            indices.push_back(0);
            indices.push_back(i);
            indices.push_back(i + 1);
        }
    }
    else { // contur
        for (int i = 1; i <= 100; i++) {
            indices.push_back(i);
        }
        indices.push_back(1);
    }

    Mesh* circle = new Mesh(name);
    if (!fill) {
        circle->SetDrawMode(GL_LINE_LOOP);
    }

    circle->InitFromData(vertices, indices);
    return circle;
}
