#ifndef TRIGGER_H
#define TRIGGER_H


class Trigger {
private:
    bool enabled = false;
public:
    Trigger();
    void enable();
    bool check();
};

#endif // TRIGGER_H
