fips_begin_lib(basisu)
    fips_files(
        basisu_transcoder.cpp basisu_transcoder.h
        basisu_sokol.cpp basisu_sokol.h
    )
fips_end_lib()
target_compile_definitions(basisu PRIVATE BASISD_SUPPORT_BC7=0)
if (FIPS_GCC OR FIPS_CLANG)
    target_compile_options(basisu PRIVATE -Wno-unused-variable -Wno-unused-parameter -Wno-type-limits)
endif()
if (FIPS_GCC)
    target_compile_options(basisu PRIVATE -Wno-maybe-uninitialized -Wno-class-memaccess)
endif()
