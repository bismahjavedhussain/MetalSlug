#pragma once

class Direction
{
public:
    virtual ~Direction() = default;
    virtual int getXSign() = 0;
    virtual Direction* flip() = 0;
    virtual Direction* clone() = 0;
};

class LeftDirection : public Direction
{
public:
    int getXSign() override;
    Direction* flip()     override;
    Direction* clone()    override;
};

class RightDirection : public Direction
{
public:
    int getXSign() override;
    Direction* flip() override;
    Direction* clone() override;
};
