#include <buildx/c_family.hpp>

#include <buildx/target.hpp>
#include <buildx/this_build.hpp>

namespace bx {
c_family::std_f c_family::std(int v) { return { v }; }

c_family::define_f c_family::define(const std::string& v) { return { v }; }

c_family::define_kv c_family::define(
    const std::string& k,
    const std::string& v
) {
    return { k, v };
}

c_family::include_f c_family::include(const std::filesystem::path& v) {
    return { v };
}

c_family::prefix_f c_family::prefix(const std::string& v) { return { v }; }

c_family::cc_f c_family::flag(const std::string& v) { return { v }; }

c_family::ld_f c_family::link_flag(const std::string& v) { return { v }; }

c_family::ar_f c_family::archive_flag(const std::string& v) { return { v }; }

c_family::md_f c_family::module_flag(const std::string& v) { return { v }; }

std::filesystem::path to_object(
    const target& target,
    const std::filesystem::path& source
) {
    auto& ctx = this_build::context;
    using std::filesystem::relative;
    auto output = ctx.scratch_path(target) / relative(source, ctx.root());
    output += ".o";
    return output;
}
}
