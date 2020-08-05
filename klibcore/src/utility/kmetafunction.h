#ifndef KMETAFUNCTION_H
#define KMETAFUNCTION_H

#include "ktype.h"

#include <string>
#include <functional>
#include <type_traits>

#ifdef QT_CORE_LIB
    #include <QVariantList>
#endif

/**
 * @brief The KMetaFunction class provides store meta methods.
 * @details
 *
 * You can store function with each signature (class signature is not changing) by calling <b>assignFunction</b> and invoke method by <b>invoke</b> function.
 *
 * @note KMetaFunction is available whithout Qt
 * @note You can consider thet this class is analog of QVariant but for functions
 */

template <typename VariantList
#ifdef QT_CORE_LIB
          = QVariantList
#endif
          >
class KMetaFunction {

    template <typename F>
    struct function_traits;

    template <typename R, class... Args>
    struct function_traits<R(*)(Args...)> : public function_traits<R(Args...)> {};

    template <typename R, class... Args>
    struct function_traits<R(Args...)> {};

    template <typename C, class R, class... Args>
    struct function_traits<R(C::*)(Args...) const> : public function_traits<R(C&, Args...)> {
        using args = std::tuple<Args...>;
    };

    template <typename F, typename Args, std::size_t ... I>
    static auto invoke_impl(std::string &functionName, F&& f, const VariantList& args, std::index_sequence<I ...>) {
        constexpr int index_sequence_size = sizeof...(I);
        const std::string size_string = std::to_string(index_sequence_size);
        if(index_sequence_size <= args.size()) {
            return f(args.at(I).template value<std::remove_const_t<std::remove_reference_t<std::tuple_element_t<I, Args>>>>() ...);
        } else {
            throw std::string("to less arguments of function: needs ") + size_string + std::string(" passed: ") + std::to_string(args.size()) + " function: " + functionName;
        }
    }

    std::function<void(VariantList)> function;
public:

    /**
     * @brief invokeMethod function is used for static metacall
     * @param name - name of function witch is used for throwing errors
     * @param f - function pointer of lambda
     * @param args - arguments of call
     *
     * This is direct call. All compiler errors ignored.
     */
    template <typename Func>
    static auto invokeMethod(std::string name, Func&& f, const VariantList& args) {
        using F = typename std::remove_reference<Func>::type;
        using Args = typename function_traits<decltype(&F::operator())>::args;
        using Indices = std::make_index_sequence<std::tuple_size<Args>::value>;
        return invoke_impl<Func, Args>(name, std::forward<Func>(f), args, Indices{});
    }

    /**
     * @brief invokeMethod overload without function name
     */
    template <typename Func>
    static auto invokeMethod(Func&& f, const VariantList& args) {
        return invokeMethod("<anonymus meta function>", f, args);
    }


    /**
     * @brief methodAddress function extracts address of method passed as call paremeter
     */
    template<typename T, typename... U>
    static size_t methodAddress(std::function<T(U...)> f) {
        typedef T(fnType)(U...);
        fnType ** fnPointer = f.template target<fnType*>();
        return (size_t) *fnPointer;
    }

    /**
     * @brief bind function is used for converting member functions to independent functions.
     * @details
     *
     * Example:
     * ```
     * const auto independentFunction = KMetaFunction::bind(this, &MyClass::someMemberFunction);
     * //independentFunction can be called without pointer to object
     * independentFunction(10);
     * ```
     *
     */
    template<typename T, typename C, typename ...A>
    static auto bind(C *object, T (C::*function)(A...)) {
        return [function, object](A ...a) { (object->*function)(a...); };
    }


    KMetaFunction() {}

#ifndef K_DISABLE_ABSTRACT_CONSTRUCTORS
    /**
     * @brief Abstract Constructor that assigns function
     *
     * @details
     *
     * By Abstract Constructor you can do it:
     *      1. KMetaFunction func1 = &poiterToFunction;
     *      2. KMetaFunction func2 = [](){};
     *      3. KMetaFunction func3 = KMetaFunction(this, &MyClass::pointerToMemberFunction);
     */
    template<typename ...Args>
    KMetaFunction(Args... args) { assignFunction(args...); }
#endif

    /**
     * @brief invoke function call contained function
     */
    template<typename ...Args>
    auto invoke(Args ...args){ return function(VariantList { args... }); }

    /**
     * @brief metaCall function is same as <b>invoke</b> but you can pass arguments as VariantList
     * @param args
     */
    auto metaCall(const VariantList &args){ return function(args); }


    /**
     * @brief standart functor
     */
    template<typename ...Args>
    auto operator()(Args... args){ return invoke(args...); }

    /**
     * @brief assignFunction for assigning member function
     */
    template <typename T, typename C, typename ...A>
    void assignFunction(C *object, T(C::*function)(A...));
    /**
     * @brief assignFunction for assigning independent function pointer
     */
    template <typename T, typename ...A>
    void assignFunction(T(*function)(A...));
    /**
     * @brief assignFunction for assigning lambda and std::function
     */
    template <typename Function>
    void assignFunction(Function function);
};

template<typename VariantList>
template<typename Function>
void KMetaFunction<VariantList>::assignFunction(Function function) {
    std::string name = KType<Function>();
    this->function = [name, function](VariantList args) {
        KMetaFunction::invokeMethod(name, function, args);
    };
}

template<typename VariantList>
template<typename T, typename ...A>
void KMetaFunction<VariantList>::assignFunction(T (*function)(A...)) {
    std::string name = KType<T(*)(A...)>();
    this->function = [name, function](VariantList args) {
        KMetaFunction::invokeMethod(name, function, args);
    };
}

template<typename VariantList>
template<typename T, typename C, typename ...A>
void KMetaFunction<VariantList>::assignFunction(C *object, T (C::*function)(A...)) {
    std::string name = KType<T(C::*)(A...)>();
    this->function = [name, function, object](VariantList args) {
        KMetaFunction::invokeMethod(name, [function, object](A ...a){
            (object->*function)(a...);
        }, args);
    };
}

#endif // KMETAFUNCTION_H
