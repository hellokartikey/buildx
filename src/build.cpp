#include <buildx/build.hpp>

constexpr char LIBBX_E[] = {
#   embed LIBBX_FILE
};

constexpr auto LIBBX_S = sizeof(LIBBX_E);

constexpr char HEAD_E[] = {
#   embed HEADERS_FILE
};

constexpr auto HEAD_S = sizeof(HEAD_E);

void bx::build(context& ctx) {
    auto& build = ctx
        .add<script>(
            embed_file{ .name = LIBBX_NAME, .data = LIBBX_E, .size = LIBBX_S },
            embed_file{ .name = HEADERS_NAME, .data = HEAD_E, .size = HEAD_S }
        )
        .file(ctx.build_script())
        .use<clangxx>(
            std::in_place,
            clangxx::std(26),
            clangxx::include(ctx.scratch_path() / "include")
        );

    char** argv = ctx.argv();
    auto flags = std::views::iota(0, ctx.argc())
        | std::views::transform([=] (int i) { return std::string{ argv[i] }; })
        | std::views::drop(1)
        | std::ranges::to<std::vector>();

    auto& run_build = build
        .run()
        .message("running build script")
        .flags(flags);

    ctx.install(run_build);
}
