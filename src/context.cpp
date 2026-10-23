#include <buildx/context.hpp>

#include <buildx/rule.hpp>

namespace bx {
const std::filesystem::path& context::root() const { return m_root; }

std::filesystem::path context::path(const std::string& path) const {
    return m_root / path;
}

const std::filesystem::path& context::prefix() const { return m_prefix; }

context& context::prefix(const std::filesystem::path& path) {
    m_prefix = path;
    return *this;
}

const std::filesystem::path& context::binary_path() const { return m_binary; }

context& context::binary_path(const std::filesystem::path& path) {
    m_binary = path;
    return *this;
}

const std::filesystem::path& context::include_path() const { return m_include; }

context& context::include_path(const std::filesystem::path& path) {
    m_include = path;
    return *this;
}

const std::filesystem::path& context::library_path() const { return m_library; }

context& context::library_path(const std::filesystem::path& path) {
    m_library = path;
    return *this;
}

std::filesystem::path context::scratch_path(const rule& rule) const {
    return m_scratch / rule.name();
}

context& context::scratch_path_prefix(const std::filesystem::path& path) {
    m_scratch = path;
    return *this;
}

context& context::install(const rule& rule) {
    m_install.depends_on(rule);
    return *this;
}
const phony& context::install() const { return m_install; }

std::string_view consume(int argc, char** argv, int& iter) {
    return argv[iter++];
}

bool context::verbose() const { return m_verbose; }

const std::filesystem::path& context::build_script() const { return m_script; }

auto split(std::string_view option, char at = '=') {
    auto idx = option.find(at);
    return std::pair{
        option.substr(0, idx),
        idx == std::string_view::npos ? "" : option.substr(idx + 1)
    };
}

auto user_option(
    std::unordered_map<std::string, std::string>& map,
    std::string_view option
) {
    option.remove_prefix(2);
    auto [key, value] = split(option);

    if (key.empty()) {
        throw context::parse_error("-D must be followed by a name.");
    }

    map[static_cast<std::string>(key)] = value;
}

void context::parse(int argc, char** argv) {
    if (argc < 2) throw parse_error("missing build script.");
    int iter = 1;

    auto script = consume(argc, argv, iter);
    m_script = std::filesystem::current_path() / script;
    if (not std::filesystem::exists(m_script))
        throw parse_error("build script {} does not exist.", script);

    while (iter < argc) {
        auto option = consume(argc, argv, iter);
        if (option.starts_with("-D")) {
            user_option(m_options, option);
        } else if (option == "--verbose" or option == "-v") {
            m_verbose = true;
        } else {
            throw parse_error("unknown option {}", option);
        }
    }
}
}
