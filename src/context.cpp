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
  return m_scratch / "targets" / rule.name();
}

const std::filesystem::path& context::scratch_path() const { return m_scratch; }

context& context::scratch_path_prefix(const std::filesystem::path& path) {
  m_scratch = path;
  return *this;
}

context& context::install(rule& rule) {
  m_install.depends_on(rule);
  return *this;
}
phony& context::install() { return m_install; }

toolchain& context::tools() {
  if (not m_tc) throw no_toolchain();
  return *m_tc;
}

bool context::verbose() const { return m_verbose; }

const std::filesystem::path& context::build_script() const { return m_script; }

int context::argc() const { return m_argc; }

char** context::argv() const { return m_argv; }

std::string_view consume(int argc, char** argv, int& iter) {
  return argv[iter++];
}

auto split(std::string_view option, char at = '=') {
  auto idx = option.find(at);
  return std::pair{option.substr(0, idx),
                   idx == std::string_view::npos ? "" : option.substr(idx + 1)};
}

auto user_option(std::unordered_map<std::string, std::string>& map,
                 std::string_view option) {
  option.remove_prefix(2);
  auto [key, value] = split(option);

  if (key.empty()) {
    throw context::parse_error("-D must be followed by a name.");
  }

  map[static_cast<std::string>(key)] = value;
}

void context::parse(int argc, char** argv) {
  m_argc = argc;
  m_argv = argv;

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

context::no_toolchain::no_toolchain() : error("no global toolchain provided") {}
}  // namespace bx
