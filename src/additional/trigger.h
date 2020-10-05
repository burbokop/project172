#ifndef TRIGGER_H
#define TRIGGER_H


class Trigger {
private:
    bool enabled = false;
public:
    Trigger();
    void enable();
    void disanable();


    bool check();
};

#endif // TRIGGER_H
