#include <buildx/build.hpp>

#include <buildx/gxx.hpp>
#include <buildx/script.hpp>

constexpr char libbx_e[] = {
#   embed LIBBX_FILE
};

constexpr char headers_e[] = {
#   embed HEADERS_FILE
};

void bx::build(context& ctx) {
    auto& build = ctx
        .add<script>(
            embed_file{
                .name = LIBBX_NAME,
                .data = libbx_e,
                .size = sizeof(libbx_e)
            },
            embed_file{
                .name = HEADERS_NAME,
                .data = headers_e,
                .size = sizeof(headers_e)
            }
        )
        .file(ctx.build_script())
        .use<gxx>(
            gxx::flags,
            gxx::std(26),
            gxx::include(ctx.scratch_path() / "include")
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
