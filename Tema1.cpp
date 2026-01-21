#include "lab_m1/Tema1/Tema1.h"

#include <vector>
#include <iostream>
#include <algorithm>

#include "lab_m1/Tema1/transform2D.h"
#include "lab_m1/Tema1/object2D.h"

using namespace std;
using namespace m1;


/*
 *  To find out more about `FrameStart`, `Update`, `FrameEnd`
 *  and the order in which they are called, see `world.cpp`.
 */


Tema1::Tema1()
{
}


Tema1::~Tema1()
{
}


void Tema1::Init()
{
    // resolution = window->GetResolution();
    auto camera = GetSceneCamera();
    //camera->SetOrthographic(0, (float)resolution.x, 0, (float)resolution.y, 0.01f, 400);
    camera->SetPosition(glm::vec3(0, 0, 50));
    camera->SetRotation(glm::vec3(0, 0, 0));
    camera->Update();
    GetCameraInput()->SetActive(false);

    corner = glm::vec3(0, 0, 0);
    squareSide = 100;
    length = 0.99f;

    resolution = window->GetResolution();
    logicSpace.x = 0;       // logic x
    logicSpace.y = 0;       // logic y
    logicSpace.width = resolution.x;   // logic width
    logicSpace.height = resolution.y;  // logic height

    cx = corner.x + squareSide / 2;
    cy = corner.y + squareSide / 2;

    Mesh* empty_neon_pink_square = object2D::CreateSquare("empty_neon_pink_square", corner, squareSide, glm::vec3(1, 0, 0.5));
    AddMeshToList(empty_neon_pink_square);

    Mesh* light_pink_square = object2D::CreateSquare("light_pink_square", corner, squareSide, glm::vec3(0.8, 0.7, 0.7), true);
    AddMeshToList(light_pink_square);

    Mesh* dark_gray_pink_square = object2D::CreateSquare("dark_gray_pink_square", corner, squareSide, glm::vec3(0.55, 0.15, 0.3), true);
    AddMeshToList(dark_gray_pink_square);

    Mesh* dark_gray_square = object2D::CreateSquare("dark_gray_square", corner, squareSide, glm::vec3(0.4, 0.3, 0.3), true);
    AddMeshToList(dark_gray_square);

    Mesh* light_gray_square = object2D::CreateSquare("light_gray_square", corner, squareSide, glm::vec3(0.7, 0.6, 0.6), true);
    AddMeshToList(light_gray_square);

    Mesh* light_gray_circle = object2D::CreateCircle("light_gray_circle", corner, squareSide / 2, glm::vec3(0.7, 0.6, 0.6), true);
    AddMeshToList(light_gray_circle);

    Mesh* neon_pink_square = object2D::CreateSquare("neon_pink_square", corner, squareSide, glm::vec3(1, 0, 0.4), true);
    AddMeshToList(neon_pink_square);

    Mesh* medium_pink_square = object2D::CreateSquare("medium_pink_square", corner, squareSide, glm::vec3(1, 0.35, 0.55), true);
    AddMeshToList(medium_pink_square);

    Mesh* start_button = object2D::CreateStartButton("start_button", corner, squareSide, glm::vec3(1, 0, 0.4), true);
    AddMeshToList(start_button);

    Mesh* cant_start_button = object2D::CreateStartButton("cant_start_button", corner, squareSide, glm::vec3(0.8, 0.7, 0.7), true);
    AddMeshToList(cant_start_button);


    Mesh* light_yellow_square = object2D::CreateSquare("light_yellow_square", corner, squareSide, glm::vec3(1.0, 0.95, 0.55), true);
    AddMeshToList(light_yellow_square);

    Mesh* yellow_circle = object2D::CreateCircle("yellow_circle", corner, squareSide / 2, glm::vec3(1.0, 0.9, 0.2), true);
    AddMeshToList(yellow_circle);

    Mesh* dark_yellow_triangle = object2D::CreateTriangle("dark_yellow_triangle", corner, squareSide, glm::vec3(0.95, 0.8, 0.1), true);
    AddMeshToList(dark_yellow_triangle);

    Mesh* orange_triangle = object2D::CreateTriangle("orange_triangle", corner, squareSide / 2, glm::vec3(1.0, 0.4, 0.0), true);
    AddMeshToList(orange_triangle);

    Mesh* black_circle = object2D::CreateCircle("black_circle", corner, squareSide / 2, glm::vec3(0.0, 0.0, 0.0), true);
    AddMeshToList(black_circle);

    Mesh* red_triangle = object2D::CreateTriangle("red_triangle", corner, squareSide / 2, glm::vec3(1.0, 0.1, 0.1), true);
    AddMeshToList(red_triangle);

    Mesh* orange_square = object2D::CreateSquare("orange_square", corner, squareSide, glm::vec3(1.0, 0.4, 0.0), true);
    AddMeshToList(orange_square);

    Mesh* egg_circle = object2D::CreateCircle("egg_circle", corner, squareSide / 4, glm::vec3(0.94, 0.85, 0.64), true);
    AddMeshToList(egg_circle);

    Mesh* nenon_pink_heart = object2D::CreateHeart("nenon_pink_heart", corner, squareSide / 2, glm::vec3(1, 0, 0.4), true);
    AddMeshToList(nenon_pink_heart);

    Mesh* neon_pink_circle = object2D::CreateCircle("neon_pink_circle", corner, squareSide / 5, glm::vec3(1, 0, 0.4), true);
    AddMeshToList(neon_pink_circle);

    numberComponents = 10;
    offsetX = offsetY = 0;
    clickOffsetX = clickOffsetY = 0;
    selected = -1; // nu e nicun bloc selectat
    rocket = vector<Components>(0);
    grid.x = grid.y = grid.height = grid.width = 0;

    editor = true;
    offsetRocketGameX = logicSpace.width / 2;
    offsetRocketGameY = 0;
    rock.x = logicSpace.width;
    rock.y = logicSpace.height;
    rock.height = rock.width = 0;
    engineNumber = 0;

    wave = 1;
    startWave = 1;
    numberChickens = 9;
    chickens = vector<Chickens>(numberChickens);
    InitChickens();

    timeGame = deadChickensTime = 0;
    gameOver = false;
    lives = 3;
    score = 0;

    bullets = vector<Bullets>(0);

    eggs = vector<Eggs>(0);
    eggSpawnInterval = 1.5f;
    lastEgg = 0.8f;
    canStart = false;
}

// 2D visualization matrix
glm::mat3 Tema1::VisualizationTransf2D(const LogicSpace& logicSpace, const ViewportSpace& viewSpace)
{
    float sx, sy, tx, ty;
    sx = viewSpace.width / logicSpace.width;
    sy = viewSpace.height / logicSpace.height;
    tx = viewSpace.x - sx * logicSpace.x;
    ty = viewSpace.y - sy * logicSpace.y;

    return glm::transpose(glm::mat3(
        sx, 0.0f, tx,
        0.0f, sy, ty,
        0.0f, 0.0f, 1.0f));
}

// Uniform 2D visualization matrix (same scale factor on x and y axes)
glm::mat3 Tema1::VisualizationTransf2DUnif(const LogicSpace& logicSpace, const ViewportSpace& viewSpace)
{
    float sx, sy, tx, ty, smin;
    sx = viewSpace.width / logicSpace.width;
    sy = viewSpace.height / logicSpace.height;
    if (sx < sy)
        smin = sx;
    else
        smin = sy;
    tx = viewSpace.x - smin * logicSpace.x + (viewSpace.width - smin * logicSpace.width) / 2;
    ty = viewSpace.y - smin * logicSpace.y + (viewSpace.height - smin * logicSpace.height) / 2;

    return glm::transpose(glm::mat3(
        smin, 0.0f, tx,
        0.0f, smin, ty,
        0.0f, 0.0f, 1.0f));
}

void Tema1::SetViewportArea(const ViewportSpace& viewSpace, glm::vec3 colorColor, bool clear)
{
    glViewport(viewSpace.x, viewSpace.y, viewSpace.width, viewSpace.height);

    glEnable(GL_SCISSOR_TEST);
    glScissor(viewSpace.x, viewSpace.y, viewSpace.width, viewSpace.height);

    // Clears the color buffer (using the previously set color) and depth buffer
    glClearColor(colorColor.r, colorColor.g, colorColor.b, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glDisable(GL_SCISSOR_TEST);

    GetSceneCamera()->SetOrthographic((float)viewSpace.x, (float)(viewSpace.x + viewSpace.width), (float)viewSpace.y, (float)(viewSpace.y + viewSpace.height), 0.1f, 400);
    GetSceneCamera()->Update();
}

void Tema1::FrameStart()
{
    // Clears the color buffer (using the previously set color) and depth buffer
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}


void Tema1::Update(float deltaTimeSeconds)
{
    resolution = window->GetResolution();

    // EDITORUL
    // Sets the screen area where to draw - the full window
    viewSpace = ViewportSpace(0, 0, resolution.x, resolution.y);
    SetViewportArea(viewSpace, glm::vec3(0), true);

    // Compute the 2D visualization matrix
    visMatrix = glm::mat3(1);
    visMatrix *= VisualizationTransf2D(logicSpace, viewSpace);

    if (editor == true) {
        DrawEditor(visMatrix);
    }
    else if (gameOver == false && lives != 0) {
        DrawGame(visMatrix, deltaTimeSeconds);
    }
    else {
        cout << "GAME OVER! FINAL SCORE: " << score << '\n';
    }
}

void Tema1::DrawConstructionArea(glm::mat3 visMatrix) {
    // gridul
    float rows = 10;
    float cols = 20;

    float spacing = 0.35f; // cat % din marimea celulei sa las spatiu intre celule
   
    float cellW = logicSpace.width / (cols + (cols + 1) * spacing);
    float cellH = logicSpace.height / (rows + (rows + 1) * spacing);

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            glm::mat3 gridMatrix = visMatrix;
            gridMatrix *= transform2D::Translate(cellW * spacing + j * cellW * (1 + spacing), cellH * spacing + i * cellH * (1 + spacing));
            gridMatrix *= transform2D::Scale(cellW / squareSide, cellH / squareSide);

            RenderMesh2D(meshes["light_pink_square"], shaders["VertexColor"], gridMatrix);
        }
    }
}

void Tema1::DrawNumberComponents(glm::mat3 visMatrix) {
    int totalSpaces = 11;
    float areaHeight = logicSpace.height / 6;

    float spacing = 0.5f;

    float squareSize = logicSpace.width / (totalSpaces + (totalSpaces + 1) * spacing) * 0.7f;

    float padding = (areaHeight - squareSize) / 2.0f;

    for (int i = 0; i < numberComponents; i++) {
        glm::mat3 gridMatrix = visMatrix;
        gridMatrix *= transform2D::Translate(squareSize * spacing / 0.7f + i * squareSize * (1 + spacing) / 0.7f, padding);
        gridMatrix *= transform2D::Scale(squareSize / squareSide, squareSize / squareSide);

        RenderMesh2D(meshes["neon_pink_square"], shaders["VertexColor"], gridMatrix);
    }

    float startSize = squareSize / 0.7f;
    float startPadding = (areaHeight - startSize) / 2.0f;

    glm::mat3 gridMatrix = visMatrix;
    gridMatrix *= transform2D::Translate(squareSize * spacing / 0.7f + 10 * squareSize * (1 + spacing) / 0.7f, startPadding);
    gridMatrix *= transform2D::Scale(startSize / squareSide, startSize / squareSide);

    if (canStart == true) {
        RenderMesh2D(meshes["start_button"], shaders["VertexColor"], gridMatrix);
    }
    else {
        RenderMesh2D(meshes["cant_start_button"], shaders["VertexColor"], gridMatrix);
    }
}

void Tema1::DrawSimpleBlock(glm::mat3 visMatrix, float squareSize) {
    modelMatrix *= transform2D::Translate(cx, cy);
    modelMatrix *= transform2D::Scale(squareSize / squareSide / 3.7f, (squareSize - 1) / squareSide / 3.7f);
    modelMatrix *= transform2D::Translate(-cx, -cy);

    RenderMesh2D(meshes["dark_gray_pink_square"], shaders["VertexColor"], modelMatrix);
    
}

void Tema1::DrawCanon(glm::mat3 visMatrix, float squareSize) {
    {
        modelMatrix = visMatrix;
        modelMatrix *= transform2D::Translate(cx, cy);
        modelMatrix *= transform2D::Scale(squareSize / squareSide / 3.7f, (squareSize - 1) / squareSide / 5.5f);
        modelMatrix *= transform2D::Translate(-cx, -cy);
        modelMatrix *= transform2D::Translate(0, -squareSide * 1.3f);

        RenderMesh2D(meshes["light_gray_square"], shaders["VertexColor"], modelMatrix);
    }

    {
        modelMatrix = visMatrix;
        modelMatrix *= transform2D::Translate(cx, cy);
        modelMatrix *= transform2D::Scale(squareSize / squareSide / 3.7f, (squareSize - 1) / squareSide / 3.7f);
        modelMatrix *= transform2D::Translate(0, -squareSide * 0.5);

        RenderMesh2D(meshes["light_gray_circle"], shaders["VertexColor"], modelMatrix);
    }

    {
        modelMatrix = visMatrix;
        modelMatrix *= transform2D::Translate(cx, cy);
        modelMatrix *= transform2D::Scale(squareSize / squareSide / 4.5f, (squareSize - 1) / squareSide / 4.5f);
        modelMatrix *= transform2D::Translate(-cx, -cy);

        RenderMesh2D(meshes["dark_gray_square"], shaders["VertexColor"], modelMatrix);
    }
    
    {
        modelMatrix = visMatrix;
        modelMatrix *= transform2D::Translate(cx, cy);
        modelMatrix *= transform2D::Scale(squareSize / squareSide / 4.5f, (squareSize - 1) / squareSide / 4.5f);
        modelMatrix *= transform2D::Translate(-cx, -cy);
        modelMatrix *= transform2D::Translate(0, squareSide);

        RenderMesh2D(meshes["dark_gray_square"], shaders["VertexColor"], modelMatrix);
    } 
}

void Tema1::DrawEngine(glm::mat3 visMatrix, float squareSize) {
    {
        modelMatrix = visMatrix;
        modelMatrix *= transform2D::Translate(cx, cy);
        modelMatrix *= transform2D::Scale(squareSize / squareSide / 3.7f, (squareSize - 1) / squareSide / 3.7f);
        modelMatrix *= transform2D::Translate(-cx, -cy);
        modelMatrix *= transform2D::Translate(0, squareSide / 4.0f);

        RenderMesh2D(meshes["medium_pink_square"], shaders["VertexColor"], modelMatrix);
    }

    {
        modelMatrix = visMatrix;
        modelMatrix *= transform2D::Translate(cx, cy);
        modelMatrix *= transform2D::Scale(squareSize / squareSide / 4.5f, (squareSize - 1) / squareSide / 5.0f);
        modelMatrix *= transform2D::Translate(-cx, -cy);
        modelMatrix *= transform2D::Translate(0, - squareSide / 5);

        RenderMesh2D(meshes["neon_pink_square"], shaders["VertexColor"], modelMatrix);
    }

    {
        modelMatrix = visMatrix;
        modelMatrix *= transform2D::Translate(cx, cy);
        modelMatrix *= transform2D::Scale(0.3f, 0.1f);
        modelMatrix *= transform2D::Scale(squareSize / squareSide / 5.0f, (squareSize - 1) / squareSide);
        modelMatrix *= transform2D::Translate(-squareSide * 1.55f, -squareSide * 2.1f);
        modelMatrix *= transform2D::Rotate(RADIANS(60));

        RenderMesh2D(meshes["neon_pink_square"], shaders["VertexColor"], modelMatrix);
    }

    {
        modelMatrix = visMatrix;
        modelMatrix *= transform2D::Translate(cx, cy);
        modelMatrix *= transform2D::Scale(0.3f, 0.3f);
        modelMatrix *= transform2D::Scale(squareSize / squareSide / 5.0f, (squareSize - 1) / squareSide);
        modelMatrix *= transform2D::Translate(-squareSide * 4 / 3, -squareSide);
        modelMatrix *= transform2D::Rotate(RADIANS(50));

        RenderMesh2D(meshes["neon_pink_square"], shaders["VertexColor"], modelMatrix);
    }

    {
        modelMatrix = visMatrix;
        modelMatrix *= transform2D::Translate(cx, cy);
        modelMatrix *= transform2D::Scale(0.2f, 0.2f);
        modelMatrix *= transform2D::Scale(squareSize / squareSide / 4.0f, (squareSize - 1) / squareSide);
        modelMatrix *= transform2D::Translate(-squareSide * 0.3, -squareSide * 1.3);
        modelMatrix *= transform2D::Rotate(RADIANS(70));

        RenderMesh2D(meshes["neon_pink_square"], shaders["VertexColor"], modelMatrix);
    }

    {
        modelMatrix = visMatrix;
        modelMatrix *= transform2D::Translate(cx, cy);
        modelMatrix *= transform2D::Scale(0.2f, 0.4f);
        modelMatrix *= transform2D::Scale(squareSize / squareSide / 4.5f, (squareSize - 1) / squareSide / 1.5f);
        modelMatrix *= transform2D::Translate(squareSide, -squareSide * 0.8f);
        modelMatrix *= transform2D::Rotate(RADIANS(110));

        RenderMesh2D(meshes["neon_pink_square"], shaders["VertexColor"], modelMatrix);
    }

    {
        modelMatrix = visMatrix;
        modelMatrix *= transform2D::Translate(cx, cy);
        modelMatrix *= transform2D::Scale(0.2f, 0.2f);
        modelMatrix *= transform2D::Scale(squareSize / squareSide / 4.0f, (squareSize - 1) / squareSide);
        modelMatrix *= transform2D::Translate(squareSide * 1.6f, -squareSide * 1.3f);
        modelMatrix *= transform2D::Rotate(RADIANS(70));

        RenderMesh2D(meshes["neon_pink_square"], shaders["VertexColor"], modelMatrix);
    }

    {
        modelMatrix = visMatrix;
        modelMatrix *= transform2D::Translate(cx, cy);
        modelMatrix *= transform2D::Scale(0.3f, 0.2f);
        modelMatrix *= transform2D::Scale(squareSize / squareSide / 7.5f, (squareSize - 1) / squareSide);
        modelMatrix *= transform2D::Translate(squareSide * 2.7f, -squareSide * 1.5f);
        modelMatrix *= transform2D::Rotate(RADIANS(35));

        RenderMesh2D(meshes["neon_pink_square"], shaders["VertexColor"], modelMatrix);
    }
}

void Tema1::DrawRocket(glm::mat3 visMatrix, float squareSize)
{
    // racheta
    float rxMax = 0;
    float ryMax = 0;

    for (int i = 0; i < rocket.size(); i++) {
        modelMatrix = visMatrix;
        modelMatrix *= transform2D::Translate(1, squareSize * rocket[i].type + 1);
        modelMatrix *= transform2D::Translate(squareSize / 2 - cx, squareSize / 2 - cy);
        modelMatrix *= transform2D::Translate(rocket[i].x, rocket[i].y);

        if (rocket[i].type == 0) { // simple block
            DrawSimpleBlock(modelMatrix, squareSize);
        }
        else if (rocket[i].type == 1) { // tun
            DrawCanon(modelMatrix, squareSize);
        }
        else if (rocket[i].type == 2) { // motor
            DrawEngine(modelMatrix, squareSize);
        }

        float rx = rocket[i].x + (squareSize / 2 - cx);
        float ry = rocket[i].y + squareSize * rocket[i].type + (squareSize / 2 - cy);
        if (rock.x > rx) {
            rock.x = rx;
            rock.type = i;
        }
        if (rock.y > ry) {
            rock.y = ry;
            rock.type = i;
        }
        rxMax = max(rxMax, rx + rocket[i].width);
        ryMax = max(ryMax, ry + rocket[i].height);
    }
    rock.width = rxMax - rock.x;
    rock.height = ryMax - rock.y;
}

void Tema1::DrawEditor(glm::mat3 visMatrix)
{
    // daca am o compeonenta selectata
    {
        float squareSize = (logicSpace.height * 5 / 6) / 3;

        modelMatrix = visMatrix;
        modelMatrix *= transform2D::Translate(1, squareSize * selected + 1);
        modelMatrix *= transform2D::Translate(squareSize / 2 - cx, squareSize / 2 - cy);
        modelMatrix *= transform2D::Translate(offsetX, offsetY);

        if (selected == 0) { // simple block       
            DrawSimpleBlock(modelMatrix, squareSize);
        }
        else if (selected == 1) { // tun
            DrawCanon(modelMatrix, squareSize);
        }
        else if (selected == 2) { // motor
            DrawEngine(modelMatrix, squareSize);
        }
    }


    // desenez nava deja existenta
    {
        float squareSize = (logicSpace.height * 5 / 6) / 3;

        modelMatrix = visMatrix;

        DrawRocket(modelMatrix, squareSize);

        if (rocket.size() != 0) {
            canStart = true;
        }
    }
    

    // patratele de delimitare zone
    // cadrament intreg frame
    modelMatrix = visMatrix;
    modelMatrix *= transform2D::Translate(1, 1);
    modelMatrix *= transform2D::Scale((logicSpace.width - 1) / squareSide, (logicSpace.height - 1) / squareSide);

    RenderMesh2D(meshes["empty_neon_pink_square"], shaders["VertexColor"], modelMatrix);

    // Z1. zona nr componente + buton start
    {
        float squareSizeZ2 = (logicSpace.height * 5 / 6) / 3;

        modelMatrix = visMatrix;
        modelMatrix *= transform2D::Translate(1, logicSpace.height * 5 / 6);
        modelMatrix *= transform2D::Scale((logicSpace.width - 1) / squareSide, (logicSpace.height - 1) / 6 / squareSide);

        RenderMesh2D(meshes["empty_neon_pink_square"], shaders["VertexColor"], modelMatrix);

        modelMatrix = visMatrix;
        modelMatrix *= transform2D::Translate(1, logicSpace.height * 5 / 6);
        modelMatrix *= transform2D::Scale((logicSpace.width - 1) / logicSpace.width, (logicSpace.height - 1) / logicSpace.height);

        DrawNumberComponents(modelMatrix);

        startBtn.x = logicSpace.x + 1166;
        startBtn.y = logicSpace.y + 625;
        startBtn.type = 3;
        startBtn.height = squareSide * 0.8f;
        startBtn.width = squareSide * 0.8f;
    }

    // Z2. zona componente
    {
        float squareSize = (logicSpace.height * 5 / 6) / 3; // 3 patrate cu dimensiuni egale, in spatiul care ramane fara Z1

        for (int i = 0; i < 3; i++) {
            modelMatrix = visMatrix;
            modelMatrix *= transform2D::Translate(1, squareSize * i + 1);
            modelMatrix *= transform2D::Scale(squareSize / squareSide, (squareSize - 1) / squareSide); // -1 ca sa incapa frumos pe inaltime

            RenderMesh2D(meshes["empty_neon_pink_square"], shaders["VertexColor"], modelMatrix);

            modelMatrix = visMatrix;
            modelMatrix *= transform2D::Translate(1, squareSize * i + 1);
            modelMatrix *= transform2D::Translate(squareSize / 2 - cx, squareSize / 2 - cy);
            if (i == 0) { // simple block
                DrawSimpleBlock(modelMatrix, squareSize);

                block.height = squareSize / 3.7f;
                block.width = squareSize / 3.7f;
                block.x = logicSpace.x + 73;
                block.y = logicSpace.y + 78;
            }
            else if (i == 1) { // tun
                DrawCanon(modelMatrix, squareSize);

                canon.height = squareSize / 4.7f + squareSize / 4.5f * 2;
                canon.width = squareSize / 3.7f;
                canon.x = logicSpace.x + 73;
                canon.y = logicSpace.y + 237;
            }
            else if (i == 2) { // motor
                DrawEngine(modelMatrix, squareSize);

                engine.height = squareSize / 3.7f + squareSize / 4.5f;
                engine.width = squareSize / 3.7f;
                engine.x = logicSpace.x + 73;
                engine.y = logicSpace.y + 444;
            }
        }
    }

    // Z3. zona constructie
    {
        float squareSizeZ2 = (logicSpace.height * 5 / 6) / 3;
        grid.y = logicSpace.width / 45;
        grid.width = logicSpace.width - squareSizeZ2 - 2 * grid.y;
        grid.height = logicSpace.height * 5 / 6 - 2 * grid.y;
        grid.x = squareSizeZ2 + grid.y;
  
        modelMatrix = visMatrix;
        modelMatrix *= transform2D::Translate(grid.x, grid.y);
        modelMatrix *= transform2D::Scale(grid.width / squareSide, grid.height / squareSide);

        RenderMesh2D(meshes["empty_neon_pink_square"], shaders["VertexColor"], modelMatrix);

        // desenare grid cu patrate
        modelMatrix = visMatrix;
        modelMatrix *= transform2D::Translate(grid.x, grid.y);
        modelMatrix *= transform2D::Scale(grid.width / logicSpace.width, grid.height / logicSpace.height);

        DrawConstructionArea(modelMatrix);
    }
}


void Tema1::InitChickens() {
    aliveChickens = numberChickens - 1;

    for (int i = 0; i < 5; i++) {
        chickens[i].x = logicSpace.width / 6 * (i + 1);
        chickens[i].y = logicSpace.height * 7 / 8;
        chickens[i].show = 1;
    }

    float groupW = logicSpace.width / 4;
    float startR2 = logicSpace.width / 2 - groupW / 2;
    for (int i = 0; i < 3; i++) {
        chickens[5 + i].x = startR2 + i * groupW / 2;
        chickens[5 + i].y = logicSpace.height * 6 / 8;
        chickens[5 + i].show = 1;
    }
}

void Tema1::DrawChicken(glm::mat3 visMatrix) {
    // aripa stanga
    {
        modelMatrix = visMatrix;
        modelMatrix *= transform2D::Translate(-cx * 3 - 20, cy / 2 + 20);
        modelMatrix *= transform2D::Scale(1.3f, 1.3f);
        modelMatrix *= transform2D::Rotate(RADIANS(-20));

        RenderMesh2D(meshes["dark_yellow_triangle"], shaders["VertexColor"], modelMatrix);
    }

    // aripa dreapta
    {
        modelMatrix = visMatrix;
        modelMatrix *= transform2D::Translate(cx * 3 + 10, cy / 2 + 30);
        modelMatrix *= transform2D::Scale(1.3f, 1.3f);
        modelMatrix *= transform2D::Rotate(RADIANS(120));

        RenderMesh2D(meshes["dark_yellow_triangle"], shaders["VertexColor"], modelMatrix);
    }

    // picior stanga
    {
        modelMatrix = visMatrix;
        modelMatrix *= transform2D::Translate(-cx / 2 - 10, -cy - 0.2f * squareSide);
        modelMatrix *= transform2D::Scale(0.2f, 0.3f);

        RenderMesh2D(meshes["orange_square"], shaders["VertexColor"], modelMatrix);

        modelMatrix = visMatrix;
        modelMatrix *= transform2D::Translate(-cx / 4 - 3, -cy - 0.4f * squareSide);
        modelMatrix *= transform2D::Scale(0.6f, 0.6f);
        modelMatrix *= transform2D::Rotate(RADIANS(45));

        RenderMesh2D(meshes["orange_triangle"], shaders["VertexColor"], modelMatrix);
    }

    // picior dreapta
    {
        modelMatrix = visMatrix;
        modelMatrix *= transform2D::Translate(cx / 2 - 10, -cy - 0.2f * squareSide);
        modelMatrix *= transform2D::Scale(0.2f, 0.3f);

        RenderMesh2D(meshes["orange_square"], shaders["VertexColor"], modelMatrix);

        modelMatrix = visMatrix;
        modelMatrix *= transform2D::Translate(cx / 4 * 3 + 1, -cy - 0.4f * squareSide + 3);
        modelMatrix *= transform2D::Scale(0.6f, 0.6f);
        modelMatrix *= transform2D::Rotate(RADIANS(55));

        RenderMesh2D(meshes["orange_triangle"], shaders["VertexColor"], modelMatrix);
    }

    // corp
    {
        modelMatrix = visMatrix;
        modelMatrix *= transform2D::Translate(-cx, -cy);

        RenderMesh2D(meshes["light_yellow_square"], shaders["VertexColor"], modelMatrix);
    }

    // creasta
    {
        modelMatrix = visMatrix;
        modelMatrix *= transform2D::Translate(0, cy + squareSide * 0.8f - 2);
        modelMatrix *= transform2D::Scale(0.3f, 0.7f);
        modelMatrix *= transform2D::Rotate(RADIANS(90));

        RenderMesh2D(meshes["red_triangle"], shaders["VertexColor"], modelMatrix);

        modelMatrix = visMatrix;
        modelMatrix *= transform2D::Translate(17, cy + squareSide * 0.8f - 7);
        modelMatrix *= transform2D::Scale(0.5f, 0.9f);
        modelMatrix *= transform2D::Rotate(RADIANS(80));

        RenderMesh2D(meshes["red_triangle"], shaders["VertexColor"], modelMatrix);
    }
    
    // ochi stanga
    {
        modelMatrix = visMatrix;
        modelMatrix *= transform2D::Translate(0, cy + squareSide / 2 * 0.8f);
        modelMatrix *= transform2D::Scale(0.8f, 0.8f);

        modelMatrix *= transform2D::Translate(-squareSide / 2 * 0.8f / 2, squareSide / 2 * 0.8f / 3);
        modelMatrix *= transform2D::Scale(0.15f, 0.15f);

        RenderMesh2D(meshes["black_circle"], shaders["VertexColor"], modelMatrix);
    }

    // ochi dreapta
    {
        modelMatrix = visMatrix;
        modelMatrix *= transform2D::Translate(0, cy + squareSide / 2 * 0.8f);
        modelMatrix *= transform2D::Scale(0.8f, 0.8f);

        modelMatrix *= transform2D::Translate(squareSide / 2 * 0.8f / 2, squareSide / 2 * 0.8f / 3);
        modelMatrix *= transform2D::Scale(0.15f, 0.15f);

        RenderMesh2D(meshes["black_circle"], shaders["VertexColor"], modelMatrix);
    }

    // cioc
    {
        modelMatrix = visMatrix;
        modelMatrix *= transform2D::Translate(2, cy + squareSide / 2 * 0.8f);
        modelMatrix *= transform2D::Scale(0.6f, 0.4f);
        modelMatrix *= transform2D::Rotate(RADIANS(250));

        RenderMesh2D(meshes["orange_triangle"], shaders["VertexColor"], modelMatrix);
    }

    // cap
    {
        modelMatrix = visMatrix;
        modelMatrix *= transform2D::Translate(0, cy + squareSide / 2 * 0.8f);
        modelMatrix *= transform2D::Scale(0.8f, 0.8f);

        RenderMesh2D(meshes["yellow_circle"], shaders["VertexColor"], modelMatrix);
    }
}

void Tema1::DrawEgg(glm::mat3 visMatrix) {
    modelMatrix = visMatrix;
    modelMatrix *= transform2D::Translate(0, cy + squareSide / 2 * 0.8f);
    modelMatrix *= transform2D::Scale(1.0f, 1.3f);

    RenderMesh2D(meshes["egg_circle"], shaders["VertexColor"], modelMatrix);
}

void Tema1::DrawBullet(glm::mat3 visMatrix) {
    modelMatrix = visMatrix;
    modelMatrix *= transform2D::Translate(0, cy + squareSide / 2 * 0.8f);

    RenderMesh2D(meshes["neon_pink_circle"], shaders["VertexColor"], modelMatrix);
}

void Tema1::DrawLives(glm::mat3 visMatrix) {
    int totalSpaces = 3;
    float areaHeight = logicSpace.height / 12;

    float spacing = 0.3f;

    float lifeSize = logicSpace.width / 7 / (totalSpaces + (totalSpaces + 1) * spacing);

    float padding = (areaHeight - lifeSize) / 2.0f;

    for (int i = 0; i < lives; i++) {
        glm::mat3 gridMatrix = visMatrix;
        gridMatrix *= transform2D::Translate(lifeSize * spacing + i * lifeSize * (1 + spacing), padding);

        RenderMesh2D(meshes["nenon_pink_heart"], shaders["VertexColor"], gridMatrix);
    }
}

void Tema1::DrawGame(glm::mat3 visMatrix, float deltaTimeSeconds) {
    float squareSize = (logicSpace.height * 5 / 6) / 3;

    modelMatrix = visMatrix;
    modelMatrix *= transform2D::Translate(1, 1);
    modelMatrix *= transform2D::Scale((logicSpace.width - 1) / squareSide, (logicSpace.height - 2) / squareSide);

    RenderMesh2D(meshes["empty_neon_pink_square"], shaders["VertexColor"], modelMatrix);

    // vietile
    {
        modelMatrix = visMatrix;
        modelMatrix *= transform2D::Translate(logicSpace.width * 6 / 7, logicSpace.height * 11 / 12);
        modelMatrix *= transform2D::Scale(logicSpace.width / 7 / squareSide, logicSpace.height / 12 / squareSide);

        RenderMesh2D(meshes["empty_neon_pink_square"], shaders["VertexColor"], modelMatrix);

        modelMatrix = visMatrix;
        modelMatrix *= transform2D::Translate(logicSpace.width * 6 / 7, logicSpace.height * 11 / 12);

        DrawLives(modelMatrix);
    }

    // racheta
    {
        modelMatrix = visMatrix;
        modelMatrix *= transform2D::Scale(0.75f, 0.75f);
        modelMatrix *= transform2D::Translate(-rock.x, -rock.y);
        modelMatrix *= transform2D::Translate(offsetRocketGameX, offsetRocketGameY);

        DrawRocket(modelMatrix, squareSize);
    }

    // proiectile
    {
        for (int i = 0; i < bullets.size(); i++) {
            modelMatrix = visMatrix;
            modelMatrix *= transform2D::Scale(0.75f, 0.75f);
            modelMatrix *= transform2D::Translate(bullets[i].x, bullets[i].y);

            DrawBullet(modelMatrix);

            bullets[i].y += 300 * deltaTimeSeconds; // viteza proiectilelor

            if (bullets[i].y == logicSpace.height) {
                bullets.erase(bullets.begin() + i);
                i--;
            }
        }

        // verific coliziune cu puii
        float chickenRadius = squareSide * 0.7f;
        for (int b = 0; b < bullets.size(); b++) {
            for (int c = 0; c < numberChickens; c++) {
                if (chickens[c].show == 1 &&
                    chickens[c].x + chickenRadius> bullets[b].x * 0.75 && chickens[c].x - chickenRadius < bullets[b].x * 0.75 &&
                    chickens[c].y + chickenRadius> bullets[b].y * 0.75 && chickens[c].y - chickenRadius < bullets[b].y * 0.75) {
                    chickens[c].show = 0;
                    aliveChickens--;
                    bullets.erase(bullets.begin() + b);
                    b--;

                    score += 10;
                    cout << "SCORE: " << score << '\n';
                    break;
                }
            }
        }
    }

    // puii
    {
        timeGame += deltaTimeSeconds;

        for (int i = 0; i < numberChickens; i++) {
            if (chickens[i].show == 1) {
                float amplitude = wave * 10.0f;
                float frequency = wave * 2.0f;
                float phase = wave * 0.5f;

                float sinOffset = amplitude * sin(frequency * timeGame + phase);

                modelMatrix = visMatrix;
                modelMatrix *= transform2D::Translate(chickens[i].x + sinOffset, chickens[i].y);
                modelMatrix *= transform2D::Scale(0.3f, 0.3f);

                DrawChicken(modelMatrix);

                chickens[i].y -= 20 * wave * deltaTimeSeconds; // viteza de cadere a puilor
                startWave = 0;

                if (chickens[i].y <= 0) {
                    gameOver = true;
                }
                deadChickensTime = timeGame;
            }
        }

        if (aliveChickens == 0 && timeGame - deadChickensTime >= 5.0f) {
            wave++;
            InitChickens();
        }

    }

    // oua 
    {
        lastEgg += deltaTimeSeconds;

        // adaug ou nou
        if (lastEgg >= eggSpawnInterval) {
            if (aliveChickens > 0) {
                int index;
                do {
                    index = rand() % numberChickens;
                } while (chickens[index].show == 0);

                Eggs e;
                e.x = chickens[index].x;
                e.y = chickens[index].y;
                eggs.push_back(e);

                lastEgg = 0;
            }
        }

        for (int i = 0; i < eggs.size(); i++) {
            modelMatrix = visMatrix;
            modelMatrix *= transform2D::Translate(eggs[i].x, eggs[i].y);
            modelMatrix *= transform2D::Scale(0.3f, 0.3f);

            DrawEgg(modelMatrix);

            eggs[i].y -= 50 * (wave + 1) * deltaTimeSeconds; // viteza de cadere a oualor

            if (eggs[i].y <= 0) {
                eggs.erase(eggs.begin() + i);
                i--;
            }
        }

        // verific coliziune cu nava
        for (int e = 0; e < eggs.size(); e++) {
            glm::vec2 rocketCorner = GetComponentPositions(rock.type, squareSize);
            if ((rocketCorner.x + rock.width) * 0.75f > eggs[e].x && (rocketCorner.x - block.width / 2) * 0.75f < eggs[e].x &&
                (rocketCorner.y + rock.height) * 0.75f > eggs[e].y && (rocketCorner.y - block.height / 2) * 0.75f < eggs[e].y) {
                lives--;
                eggs.erase(eggs.begin() + e);
                e--;
                score -= 10;
                cout << "SCORE: " << score << '\n';
            }
        }
    }
}

glm::vec2 Tema1::GetComponentPositions(int i, float squareSize)
{
    glm::vec2 pos = glm::vec2(rocket[i].x, rocket[i].y);

    pos.x += squareSize / 2;
    pos.y += squareSize * rocket[i].type + (squareSize / 2 - cy);

    pos.x -= rock.x;
    pos.y -= rock.y;

    pos.x += offsetRocketGameX;
    pos.y += offsetRocketGameY;

    return pos;
}


void Tema1::FrameEnd()
{
}


/*
 *  These are callback functions. To find more about callbacks and
 *  how they behave, see `input_controller.h`.
 */


void Tema1::OnInputUpdate(float deltaTime, int mods)
{
    float speed = 200.0f + 75.0f * engineNumber;

    if (editor == false) {
        if (window->KeyHold(GLFW_KEY_LEFT)) {
            offsetRocketGameX -= speed * deltaTime;
        }
        if (window->KeyHold(GLFW_KEY_RIGHT)) {
            offsetRocketGameX += speed * deltaTime;
        }
        if (window->KeyHold(GLFW_KEY_DOWN)) {
            offsetRocketGameY -= speed * deltaTime;
        }
        if (window->KeyHold(GLFW_KEY_UP)) {
            offsetRocketGameY += speed * deltaTime;
        }
    }
}


void Tema1::OnKeyPress(int key, int mods)
{
    // Add key press event
    if (key == GLFW_KEY_SPACE) {
        for (int i = 0; i < rocket.size(); i++) {
            if (rocket[i].type == 1) {
                float squareSize = (logicSpace.height * 5 / 6) / 3;
                Bullets b;
                glm::vec2 pos = GetComponentPositions(i, squareSize);

                b.x = pos.x;
                b.y = pos.y;

                bullets.push_back(b);
            }
        }
    }
    
}


void Tema1::OnKeyRelease(int key, int mods)
{
    // Add key release event
}


void Tema1::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
    // Add mouse move event
    glm::mat3 invVisMatrix = glm::inverse(visMatrix);
    glm::vec3 mouseLogic = invVisMatrix * glm::vec3(mouseX, resolution.y - mouseY, 1);

    if (selected == 0) { // simple block 
        offsetX = mouseLogic.x - clickOffsetX - block.x;
        offsetY = mouseLogic.y - clickOffsetY - block.y;
    } else if (selected == 1) { // tun 
        offsetX = mouseLogic.x - clickOffsetX - canon.x;
        offsetY = mouseLogic.y - clickOffsetY - canon.y;
    } else if (selected == 2) { // motor 
        offsetX = mouseLogic.x - clickOffsetX - engine.x;
        offsetY = mouseLogic.y - clickOffsetY - engine.y;
    }
}


void Tema1::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button press event
    glm::mat3 invVisMatrix = glm::inverse(visMatrix);
    glm::vec3 mouseLogic = invVisMatrix * glm::vec3(mouseX, resolution.y - mouseY, 1);

    if (button == GLFW_MOUSE_BUTTON_2) {
        // simple block
        if (mouseLogic.x >= block.x && mouseLogic.x <= block.x + block.width &&
            mouseLogic.y >= block.y && mouseLogic.y <= block.y + block.height)
        {
            cout << "Ai dat click pe Simple Block!\n";

            clickOffsetX = mouseLogic.x - block.x;
            clickOffsetY = mouseLogic.y - block.y;
            selected = 0;
        } else 
        // tun
        if (mouseLogic.x >= canon.x && mouseLogic.x <= canon.x + canon.width &&
            mouseLogic.y >= canon.y && mouseLogic.y <= canon.y + canon.height)
        {
            cout << "Ai dat click pe Tun!\n";

            clickOffsetX = mouseLogic.x - canon.x;
            clickOffsetY = mouseLogic.y - canon.y;
            selected = 1;
        } else 
        // motor
        if (mouseLogic.x >= engine.x && mouseLogic.x <= engine.x + engine.width &&
            mouseLogic.y >= engine.y && mouseLogic.y <= engine.y + engine.height)
        {
            cout << "Ai dat click pe Motor!\n";

            clickOffsetX = mouseLogic.x - engine.x;
            clickOffsetY = mouseLogic.y - engine.y;
            selected = 2;
        }
        else
        // buton start
        if (mouseLogic.x >= startBtn.x && mouseLogic.x <= startBtn.x + startBtn.width &&
            mouseLogic.y >= startBtn.y && mouseLogic.y <= startBtn.y + startBtn.height)
        {
            cout << "Ai dat click pe Start!\n";

            clickOffsetX = mouseLogic.x - startBtn.x;
            clickOffsetY = mouseLogic.y - startBtn.y;
            selected = 3;
        }
    }
    if (button == GLFW_MOUSE_BUTTON_3) {
        for (int i = 0; i < rocket.size(); i++) {
            if (rocket[i].type == 0) { // simple block 
                offsetX = mouseLogic.x - clickOffsetX - block.x;
                offsetY = mouseLogic.y - clickOffsetY - block.y;
            }
            else if (rocket[i].type == 1) { // tun 
                offsetX = mouseLogic.x - clickOffsetX - canon.x;
                offsetY = mouseLogic.y - clickOffsetY - canon.y;
            }
            else if (rocket[i].type == 2) { // motor 
                offsetX = mouseLogic.x - clickOffsetX - engine.x;
                offsetY = mouseLogic.y - clickOffsetY - engine.y;
            }

            if (offsetX >= rocket[i].x && offsetX <= rocket[i].x + rocket[i].width &&
                offsetY >= rocket[i].y && offsetY <= rocket[i].y + rocket[i].height) {
                rocket.erase(rocket.begin() + i);

                numberComponents++;
                numberComponents = min(numberComponents, 10);
                break;
            }
        }
    }
}


void Tema1::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button release event
    glm::mat3 invVisMatrix = glm::inverse(visMatrix);
    glm::vec3 mouseLogic = invVisMatrix * glm::vec3(mouseX, resolution.y - mouseY, 1);

    if (button == GLFW_MOUSE_BUTTON_2 && selected != -1 && editor == true) {
        if (selected == 3) { // am apasat butonul start
            if (numberComponents == 10) {
                return;
            }
            editor = 0;
        }

        Components c;
        c.x = offsetX;
        c.y = offsetY;
        c.type = selected;
        if (selected == 0) { // simple block
            c.height = block.height;
            c.width = block.width;
        }
        else if (selected == 1) { // tun
            c.height = canon.height;
            c.width = canon.width;
        }
        else if (selected == 2) { // motor
            c.height = engine.height;
            c.width = engine.width;
        }

        float objectX = mouseLogic.x - clickOffsetX;
        float objectY = mouseLogic.y - clickOffsetY;

        if (objectX >= grid.x && objectX + c.width <= grid.x + grid.width &&
            objectY >= grid.y && objectY + c.height <= grid.y + grid.height) {
            
            float localX = objectX - grid.x;
            float localY = objectY - grid.y;

            // gasesc celula din grid cea mai apropiata
            float rows = 10;
            float cols = 20;
            float spacing = 0.35f; // cat % din marimea celulei sa las spatiu intre celule
            float cellW = grid.width / (cols + (cols + 1) * spacing);
            float cellH = grid.height / (rows + (rows + 1) * spacing);

            int col = int(localX / (cellW * (1 + spacing)));
            int row = int(localY / (cellH * (1 + spacing)));
            // verif sa nu iasa din grid
            col = max(0, min((int)cols - 1, col));
            row = max(0, min((int)rows - 1, row));

            // coordonatele centrului celulei
            float cellCenterX = grid.x + cellW * spacing / 2 + col * cellW * (1 + spacing);
            float cellCenterY = grid.y + cellH * spacing / 2 + row * cellH * (1 + spacing);

            
            if (selected == 0) { // simple block
                c.x = cellCenterX - block.x;
                c.y = cellCenterY - block.y;
            }
            else if (selected == 1) { // tun
                c.x = cellCenterX - canon.x;
                c.y = cellCenterY - canon.y;
            }
            else if (selected == 2) { // motor
                c.x = cellCenterX - engine.x;
                c.y = cellCenterY - engine.y;

                engineNumber++;
            }

            rocket.push_back(c);

            numberComponents--;
        }

        selected = -1;
        offsetX = offsetY = clickOffsetX = clickOffsetY = 0;
    }
}


void Tema1::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}
