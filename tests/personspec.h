#pragma once

#include <src/testing.h>
#include <src/capabilities/warestorage.h>

namespace proj172::core::tests {

class PersonSpec {
    class TestWareStorage : public WareStorage {
        size_t m_initialCapacity = 0;
        std::map<std::string, size_t> m_initialWares;
    public:
        TestWareStorage(e172::FactoryMeta &&meta,
                        size_t capacity = 0,
                        const std::map<std::string, std::size_t> &initialWares = {})
            : WareStorage(std::move(meta))
            , m_initialCapacity(capacity)
            , m_initialWares(initialWares)
        {}

        size_t setCapacity(size_t capacity);
        e172::ptr<AbstractWareContainer> __wareContainer() const;

        // Entity interface
    public:
        virtual void proceed(e172::Context *, e172::EventHandler *) override{};
        virtual void render(e172::AbstractRenderer *) override {};

        // WareStorage interface
    protected:
        virtual e172::ptr<AbstractWareContainer> createWareContainer() const override;
    };

    static void buyWareTest() e172_test(PersonSpec, buyWareTest);
    static void sellWareTest() e172_test(PersonSpec, sellWareTest);
};

} // namespace proj172::core::tests
