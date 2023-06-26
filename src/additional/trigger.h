#pragma once

namespace proj172::core {

class Trigger {
private:
    bool enabled = false;
public:
    Trigger() = default;
    void enable();
    void disanable();


    bool check();
};

} // namespace proj172::core
