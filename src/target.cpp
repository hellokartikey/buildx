#include <buildx/target.hpp>

#include <buildx/library.hpp>

namespace bx {
target::target(const std::string& name) : rule(name) {}

void target::build_steps(step& first, step& last) const {
    if (not m_tc) throw no_toolchain(*this);

    if (files().empty() and headers().empty()) {
        last.depends_on(first);
    } else {
        compile_steps(first, last);
    }
}

const toolchain& target::toolchain() const {
    if (not m_tc) throw no_toolchain(*this);
    return *m_tc;
}

const std::vector<std::filesystem::path>& target::files() const {
    return m_files;
}

const std::vector<std::filesystem::path>& target::headers() const {
    return m_headers;
}

const view<library>& target::link_libraries() const { return m_link; }

view<library> target::all_link_libraries() const {
    return std::views::concat(
            link_libraries(),
            link_libraries()
                | std::views::transform(&target::all_link_libraries)
                | std::views::join)
        | as_view;
}

target::no_toolchain::no_toolchain(const target& target)
    : error("no toolchain provided for target {:?}", target.name()) {}
}
