#pragma once

#include "components/simple_scene.h"


namespace m1
{
    class Tema1 : public gfxc::SimpleScene
    {
    public:
        struct ViewportSpace
        {
            ViewportSpace() : x(0), y(0), width(1), height(1) {}
            ViewportSpace(int x, int y, int width, int height)
                : x(x), y(y), width(width), height(height) {
            }
            int x;
            int y;
            int width;
            int height;
        };

        struct LogicSpace
        {
            LogicSpace() : x(0), y(0), width(1), height(1) {}
            LogicSpace(float x, float y, float width, float height)
                : x(x), y(y), width(width), height(height) {
            }
            float x;
            float y;
            float width;
            float height;
        };

        struct Components
        {
            Components() : x(0), y(0), width(1), height(1) {}
            Components(float x, float y, float width, float height)
                : x(x), y(y), width(width), height(height) {
            }
            float x;
            float y;
            float width;
            float height;
            int type;
        };

        struct Chickens
        {
            Chickens() : x(0), y(0) {}
            Chickens(float x, float y)
                : x(x), y(y) {
            }
            float x;
            float y;
            int show;
        };

        struct Eggs
        {
            Eggs() : x(0), y(0) {}
            Eggs(float x, float y)
                : x(x), y(y) {
            }
            float x;
            float y;
        };

        struct Bullets
        {
            Bullets() : x(0), y(0) {}
            Bullets(float x, float y)
                : x(x), y(y) {
            }
            float x;
            float y;
        };

    public:
        Tema1();
        ~Tema1();

        void Init() override;

    private:
        void FrameStart() override;
        void Update(float deltaTimeSeconds) override;
        void FrameEnd() override;

        void DrawEditor(glm::mat3 visMatrix);
        void DrawSimpleBlock(glm::mat3 visMatrix, float squareSize);
        void DrawCanon(glm::mat3 visMatrix, float squareSize);
        void DrawEngine(glm::mat3 visMatrix, float squareSize);
        void DrawConstructionArea(glm::mat3 visMatrix);
        void DrawRocket(glm::mat3 visMatrix, float squareSize);
        void DrawNumberComponents(glm::mat3 visMatrix);

        void DrawGame(glm::mat3 visMatrix, float deltaTimeSeconds);
        void DrawLives(glm::mat3 visMatrix);
        void DrawChicken(glm::mat3 visMatrix);
        void DrawEgg(glm::mat3 visMatrix);
        void DrawBullet(glm::mat3 visMatrix);
        void InitChickens();

        glm::vec2 GetComponentPositions(int i, float squareSize);

        void OnInputUpdate(float deltaTime, int mods) override;
        void OnKeyPress(int key, int mods) override;
        void OnKeyRelease(int key, int mods) override;
        void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
        void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;

        // Sets the logic space and view space
        // logicSpace: { x, y, width, height }
        // viewSpace: { x, y, width, height }
        glm::mat3 VisualizationTransf2D(const LogicSpace& logicSpace, const ViewportSpace& viewSpace);
        glm::mat3 VisualizationTransf2DUnif(const LogicSpace& logicSpace, const ViewportSpace& viewSpace);

        void SetViewportArea(const ViewportSpace& viewSpace, glm::vec3 colorColor = glm::vec3(0), bool clear = true);

    protected:
        float length;
        ViewportSpace viewSpace;
        LogicSpace logicSpace;
        glm::mat3 modelMatrix, visMatrix;

        glm::ivec2 resolution;
        float squareSide, cx, cy;
        glm::vec3 corner;

        int selected; // ce block este selectat
        float offsetX, offsetY;
        float clickOffsetX, clickOffsetY;
        LogicSpace grid;

        int numberComponents;
        Components engine, block, canon, startBtn, rock;
        // in rock type == index-ul din vectorul de componente al coltului st jos
        std::vector<Components> rocket;
        int engineNumber; // nr de motoare pt calcul crestere viteza miscare
        int wave; // in a cata runda a jocului sunt
        int startWave; // pt a reinitializa pozitiile puilor pt o runda noua
        bool canStart; // daca pot folosi butonul de start
        
        std::vector<Chickens> chickens;
        int numberChickens;
        float eggSpawnInterval;
        float lastEgg;
        std::vector<Eggs> eggs;

        std::vector<Bullets> bullets;

        bool editor; // verif daca sunt in editor sau in joc
        float offsetRocketGameX, offsetRocketGameY;
        float timeGame, deadChickensTime;
        float waitRounds;
        bool gameOver;
        int lives;

        int score;
        int aliveChickens;
    };
}   // namespace m1
