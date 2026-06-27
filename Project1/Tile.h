#pragma once

class Entity;

class Tile{
protected:               
    int gridX;
    int gridY;

  public:
    Tile() : gridX(0), gridY(0) {}
    virtual ~Tile() = default;

    virtual bool isSolid() = 0;
    virtual bool isDestructible() = 0;
    virtual bool isWater() = 0;
    virtual void onEntityEnter(Entity* ) {}
    virtual void onExplosion(float ) {}

    int  getGridX() const { return gridX; }
    int  getGridY() const { return gridY; }
    void setGrid(int x, int y) {
    gridX = x;
    gridY = y;
    }
};
