#include <buildx/gcc.hpp>

namespace bx::tc {
void gcc::apply(std_f flag) { m_cc.push_back(std::format("-std=c{}", flag.v)); }

void gcc::apply(define_f flag) { m_cc.push_back(std::format("-D{}", flag.v)); }

void gcc::apply(define_kv flag) {
    m_cc.push_back(std::format("-D{}={}", flag.k, flag.v));
}

void gcc::apply(include_f flag) {
    m_cc.push_back(std::format("-I{}", flag.v.string()));
}

void gcc::apply(prefix_f flag) { m_exe = std::format("{}gcc", flag.v); }

void gcc::apply(cc_f flag) { m_cc.push_back(flag.v); }

void gcc::apply(ld_f flag) { m_cc.push_back(std::format("-Wl,{}", flag.v)); }

void gcc::apply(ar_f flag) { m_ar.push_back(flag.v); }

void gcc::apply(md_f flag) {}
}
