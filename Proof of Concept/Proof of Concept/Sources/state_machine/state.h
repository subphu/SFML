#pragma once

class State {
    
public:
    virtual ~State() = default;
    virtual long run(long lag) = 0;
};
