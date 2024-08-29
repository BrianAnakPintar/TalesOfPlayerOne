#ifndef STATE_H
#define STATE_H

#include <string>

class State {
protected:
    std::string name;

public:
    virtual ~State() {}
    virtual void Init() = 0;
    virtual void HandleInput() = 0;
    virtual void Update(float dt) = 0;
    virtual void Draw(float dt) = 0;
    virtual void Pause() {}
    virtual void Resume() {}
};

#endif // !STATE_H

