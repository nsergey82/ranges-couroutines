#ifndef CRTN_HELPERS_H
#define CRTN_HELPERS_H

#include <iostream>
#include <boost/coroutine2/coroutine.hpp>

template<typename T=int>
using coro_t = boost::coroutines2::coroutine<T>;
template<typename T=int>
using pull_t = typename coro_t<T>::pull_type;
template<typename T=int>
using push_t = typename coro_t<T>::push_type;


template<typename Push, typename Pull, typename F, class ... Types>
auto chain(Pull& source, F callable, Types ... args) -> pull_t<Push>
{
    return pull_t<Push>([&](push_t<Push>& sink){
        callable(sink, source, args...);
    });
};

template<typename Pull, typename C>
auto operator|(Pull& source, C crtn) -> std::unique_ptr<pull_t<decltype(source.get())>>
{
    using T = decltype(source.get());
    return std::make_unique<pull_t<T>>([&](push_t<T>& sink){ crtn(sink, source); });
};

template<typename Pull, typename C>
auto operator|(std::unique_ptr<Pull> source, C crtn) -> std::unique_ptr<pull_t<decltype(source->get())>>
{
    using T = decltype(source->get());
    return std::make_unique<pull_t<T>>([source=move(source), crtn](push_t<T>& sink){ crtn(sink, *source); });

};


#endif
