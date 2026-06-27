#pragma once

class TextureManager;
class Infantry;
class ParatrooperKind
{
public:
    virtual ~ParatrooperKind() = default;
    virtual int scoreBase() = 0;
    virtual Infantry* spawnLanded(TextureManager& tm, float x, float y, int batchId) = 0;
    virtual ParatrooperKind* clone() = 0;
};

class RebelParatrooperKind : public ParatrooperKind
{
public:
    int scoreBase() override;
    Infantry* spawnLanded(TextureManager& tm, float x, float y, int batchId) override;
    ParatrooperKind* clone() override;
};

class ShieldedParatrooperKind : public ParatrooperKind
{
public:
    int scoreBase() override;
    Infantry* spawnLanded(TextureManager& tm, float x, float y, int batchId) override;
    ParatrooperKind* clone() override;
};

class BazookaParatrooperKind : public ParatrooperKind
{
public:
    int scoreBase() override;
    Infantry* spawnLanded(TextureManager& tm, float x, float y, int batchId) override;
    ParatrooperKind* clone() override;
};

class GrenadierParatrooperKind : public ParatrooperKind
{
public:
    int scoreBase() override;
    Infantry* spawnLanded(TextureManager& tm, float x, float y, int batchId) override;
    ParatrooperKind* clone() override;
};
