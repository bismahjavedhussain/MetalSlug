#pragma once

class BossLevel;
class BossPhase
{
public:
    virtual ~BossPhase() = default;
    virtual void enter(BossLevel* lvl) = 0;

    virtual BossPhase* tick(BossLevel* lvl) = 0;
    virtual int phaseId() const = 0;
};

class BossPhase1Ground : public BossPhase
{
public:
    void enter(BossLevel* lvl) override;
    BossPhase* tick (BossLevel* lvl) override;
    int phaseId() const override { return 1; }
};

class BossPhase2Aerial : public BossPhase
{
public:
    void enter(BossLevel* lvl) override;
    BossPhase* tick (BossLevel* lvl) override;
    int phaseId() const override { return 2; }
};

class BossPhase3Aquatic : public BossPhase
{
public:
    void enter(BossLevel* lvl) override;
    BossPhase* tick (BossLevel* lvl) override;
    int phaseId() const override { return 3; }
};

class BossPhase4Fused : public BossPhase
{
public:
    void enter(BossLevel* lvl) override;
    BossPhase* tick (BossLevel* lvl) override;
    int phaseId() const override { return 4; }
};

class BossPhaseDone : public BossPhase
{
public:
    void enter(BossLevel* lvl) override;
    BossPhase* tick (BossLevel* lvl) override { (void)lvl; return nullptr; }
    int phaseId() const override { return 5; }
};
