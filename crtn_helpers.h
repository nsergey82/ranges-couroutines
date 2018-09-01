#ifndef CRTN_HELPERS_H
#define CRTN_HELPERS_H

#include <deque>
#include <vector>
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

// use outside owned queues object to persist streamed values
void _tee(push_t<int>& sink, pull_t<int>& source,
          unsigned index, std::vector<std::deque<int>>& queues)
{
    while(true) {
        if(queues[index].empty()) {
            auto val = source.get();
            source();
            queues[0].push_front(val);
            queues[1].push_front(val);
        }

        auto val = queues[index].back();
        queues[index].pop_back();
        sink(val);
        if(!source && queues[index].empty())
            break;
    }
};

// create two pull coroutines that utilize the queues to persist streaming data from single source
std::pair<pull_t<int>, pull_t<int>> tee(pull_t<int>& source, std::vector<std::deque<int>>& queues) {
    return std::make_pair(
            pull_t<int>([&](push_t<int>& sink){_tee(sink, source, 0, queues);}),
            pull_t<int>([&](push_t<int>& sink){_tee(sink, source, 1, queues);})
    );
};


#endif
