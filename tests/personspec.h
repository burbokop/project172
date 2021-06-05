#ifndef PERSONSPEC_H
#define PERSONSPEC_H

#include <src/testing.h>

#include <src/capabilities/warestorage.h>

class PersonSpec {
    class TestWareStorage : public WareStorage {
        size_t m_initialCapacity = 0;
        std::map<std::string, size_t> m_initialWares;
    public:
        TestWareStorage(size_t capacity = 0, const std::map<std::string, size_t> &initialWares = {});
        size_t setCapacity(size_t capacity);
        e172::ptr<AbstractWareContainer> __wareContainer() const;

        // Entity interface
    public:
        virtual void proceed(e172::Context *, e172::AbstractEventHandler *) override {};
        virtual void render(e172::AbstractRenderer *) override {};

        // WareStorage interface
    protected:
        virtual e172::ptr<AbstractWareContainer> createWareContainer() const override;
    };


    static void buyWareTest(); e172_test(PersonSpec, buyWareTest)
    static void sellWareTest(); e172_test(PersonSpec, sellWareTest)
};

#endif // PERSONSPEC_H
