#pragma once


#define K_EXPAND(BLOCK) std::vector<int> { 0, ((void)(BLOCK), 0) ... };


#define K_AUTO_MEMBER(TYPE, NAME, GETTER, SETTER, DEFAULT) \
public: \
    TYPE GETTER() const { return this->m_ ## NAME; } \
    void SETTER(TYPE value) { \
        this->m_ ## NAME = value; \
    } \
private: \
    TYPE m_ ## NAME = DEFAULT;

#define K_CONST_MEMBER(TYPE, NAME, DEFAULT) \
public: \
    TYPE NAME() const { return this->m_ ## NAME; } \
private: \
    TYPE m_ ## NAME = DEFAULT;


#define K_READONLY_MEMBER(TYPE, NAME, GETTER, SETTER, DEFAULT) \
public: \
    TYPE GETTER() const { return this->m_ ## NAME; } \
private: \
    TYPE m_ ## NAME = DEFAULT; \
    void SETTER(TYPE value) { \
        this->m_ ## NAME = value; \
    }

#define K_PROTECTED_MEMBER(TYPE, NAME, GETTER, SETTER, DEFAULT) \
public: \
    TYPE GETTER() const { return this->m_ ## NAME; } \
protected: \
    void SETTER(TYPE value) { \
        this->m_ ## NAME = value; \
    } \
private: \
    TYPE m_ ## NAME = DEFAULT;



#define K_GENERATE_METHOD_CHECKER(METHOD_NAME) \
template <typename T> \
class k_has_ ## METHOD_NAME ## _method { \
private: \
    typedef char YesType[1]; \
    typedef char NoType[2]; \
    template <typename C> static YesType& test( decltype(&C:: METHOD_NAME) ) ; \
    template <typename C> static NoType& test(...); \
public: \
    enum { value = sizeof(test<T>(0)) == sizeof(YesType) }; \
};

K_GENERATE_METHOD_CHECKER(push_back)
K_GENERATE_METHOD_CHECKER(append)
K_GENERATE_METHOD_CHECKER(clear)

template <typename ContainerType, typename ItemType>
void kAppendToContainer(ContainerType *container, ItemType item) {
    if constexpr(k_has_push_back_method<ContainerType>::value) { \
        container->push_back(item);
    } else if constexpr(k_has_append_method<ContainerType>::value) {
        container->append(item);
    }
}




#define K_SINGLETON(TYPE) \
public: \
    static TYPE *instance() { \
        static TYPE *m_instance; \
        if (m_instance == nullptr) { \
            m_instance = new TYPE(); \
        } \
        return m_instance; \
    } \
private:


#define K_PRIVATE_SINGLETON(TYPE) \
private: \
    static TYPE *instance() { \
        static TYPE *m_instance; \
        if (m_instance == nullptr) { \
            m_instance = new TYPE(); \
        } \
        return m_instance; \
    }


#define K_ERROR_STRING() \
    K_PROTECTED_PROPERTY(QString, errorString, errorString, setErrorString, errorStringChanged, "")

#define K_DISPLAY_ERROR(CONDITION, TEXT) \
    if(CONDITION) { \
        setErrorString(TEXT); \
        return; \
    } else { \
        setErrorString(""); \
    }


#ifdef KLIBCORE_USE_EXTENDED_META_SYSTEM
    #define __K_EXTENDED_TYPE_REGISTRATION(TYPE) \
    private: \
        static inline const QString TYPE ## MetaTypeName = KClassRegistry::registerType<TYPE>();

    #define K_QML_TYPE(TYPE) \
    __K_EXTENDED_TYPE_REGISTRATION(TYPE) \
        static inline const int TYPE ## QMLRegistration = qmlRegisterType<TYPE>(KLibInfo::libname, KLibInfo::major, KLibInfo::minor, # TYPE);
    #define K_META_TYPE_EXTENDED(TYPE) \
    __K_EXTENDED_TYPE_REGISTRATION(TYPE) \
        static inline const int TYPE ## MetaRegistration = qRegisterMetaType<TYPE>();
#else
    #define K_QML_TYPE(TYPE) \
    private: \
        static inline const int TYPE ## QMLRegistration = qmlRegisterType<TYPE>(KLibInfo::libname, KLibInfo::major, KLibInfo::minor, # TYPE);
#endif

#define K_META_TYPE(TYPE) \
private: \
    static inline const int TYPE ## MetaRegistration = qRegisterMetaType<TYPE>();

#define K_META_TYPE_ALIAS(TYPE, ALIAS) \
private: \
    static inline const int ALIAS ## MetaRegistration = qRegisterMetaType<TYPE>();

#define K_QML_SINGLETON(TYPE) \
private: \
    static QObject *qmlInstance(QQmlEngine *engine, QJSEngine *scriptEngine) { \
        (void)engine; \
        (void)scriptEngine; \
        return instance(); \
    } \
    static inline const int TYPE ## QMLRegistration = qmlRegisterSingletonType<TYPE>(KLibInfo::libname, KLibInfo::major, KLibInfo::minor, # TYPE, &TYPE::qmlInstance);

#define K_QML_SINGLETON_ALIAS(TYPE, ALIAS) \
private: \
    static QObject *qmlInstance(QQmlEngine *engine, QJSEngine *scriptEngine) { \
        (void)engine; \
        (void)scriptEngine; \
        return instance(); \
    } \
    static inline const int TYPE ## QMLRegistration = qmlRegisterSingletonType<TYPE>(KLibInfo::libname, KLibInfo::major, KLibInfo::minor, #ALIAS, &TYPE::qmlInstance);




#define K_SETTER(SETTER_NAME, VAR_NAME) \
    void SETTER_NAME(const decltype(VAR_NAME) &value) { VAR_NAME = value; }

#define K_GETTER(SETTER_NAME, VAR_NAME) \
    auto SETTER_NAME() const { return VAR_NAME; }

#define K_STATIC_SETTER(SETTER_NAME, VAR_NAME) \
    static void SETTER_NAME(const decltype(VAR_NAME) &value) { VAR_NAME = value; }

#define K_STATIC_GETTER(SETTER_NAME, VAR_NAME) \
    static auto SETTER_NAME() { return VAR_NAME; }


#define K_MEMBER_FUNCTION_INSTALLER(F_NAME, ...) \
    template<typename ...Args, typename T, typename C> \
    void F_NAME(__VA_ARGS__ C *obj, T(C::*f)(Args...)) { \
        return F_NAME([obj, f](auto d) { return (obj->*f)(d); }); \
    }

#define K_STATIC_MEMBER_FUNCTION_INSTALLER(F_NAME, ...) \
    template<typename ...Args, typename T, typename C> \
    static void F_NAME(__VA_ARGS__ C *obj, T(C::*f)(Args...)) { \
        return F_NAME([obj, f](auto d) { return (obj->*f)(d); }); \
    }


