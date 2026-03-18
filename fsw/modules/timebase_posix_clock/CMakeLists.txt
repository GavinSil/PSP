######################################################################
#
# CMAKE build recipe for modular PSP component
#
######################################################################

# Create the module
add_psp_module(timebase_posix_clock cfe_psp_timebase_posix_clock.c)

# When stepping is enabled, link ESA public API for stepping headers
if (CFE_SIM_STEPPING)
    target_link_libraries(timebase_posix_clock PRIVATE esa_public_api)
endif()
