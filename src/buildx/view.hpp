#ifndef BUILDX_VIEW_HPP
#define BUILDX_VIEW_HPP

#include <ranges>
#include <vector>

namespace bx {

template <typename R>
concept viewable =
    std::ranges::input_range<R> &&
    std::is_lvalue_reference_v<std::ranges::range_reference_t<R>>;

template <viewable R>
using view_t = std::remove_reference_t<std::ranges::range_reference_t<R>>;

template <typename T>
class view {
public:
    using vector = std::vector<T*>;

    using value_type = T;
    using reference = T&;

    struct iterator {
        vector::const_iterator iter;

        using difference_type = std::ptrdiff_t;
        using iterator_concept = std::input_iterator_tag;
        using value_type = T;
        using reference = T&;

        T& operator*() const { return **iter; }

        iterator& operator++() { iter++; return *this; }
        iterator operator++(int) { return { .iter = iter++ }; }

        bool operator==(const iterator&) const = default;
    };

    view() = default;

    template <viewable R>
    view(std::from_range_t, R&& range)
        : m_vec(
            std::from_range,
            std::forward<R>(range)
            | std::views::transform([] (auto& item) { return &item; })
        ) {}

    iterator begin() const { return { .iter = m_vec.begin() }; }
    iterator end() const { return { .iter = m_vec.end() }; }

    bool empty() const { return m_vec.empty(); }
    std::size_t size() const { return m_vec.size(); }

    void clear() { m_vec.clear(); }
    void push_back(T& item) { m_vec.push_back(&item); }

private:
    vector m_vec;
};

template <viewable R>
view(std::from_range_t, R&& range) -> view<view_t<R>>;

inline class as_view_t {} as_view;

template <viewable R>
view<view_t<R>> operator|(R&& range, as_view_t) {
    return {std::from_range, std::forward<R>(range) };
}

static_assert(std::ranges::range<view<int>>);
static_assert(std::ranges::input_range<view<int>>);
static_assert(std::ranges::viewable_range<view<int>>);

static_assert(std::same_as<
    decltype(
        std::declval<std::vector<int*>>()
        | std::views::transform(std::declval<int&(int*)>())
        | as_view
    ),
    view<int>
>);
}

#endif
