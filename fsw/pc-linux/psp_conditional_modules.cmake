# Conditional PSP modules for pc-linux
# This file is included optionally by the PSP CMakeLists.txt
# Add modules here based on CMake conditions

# Add sim_stepping module when CFE_SIM_STEPPING is enabled
# This must match the variable set in global_build_options.cmake
if (DEFINED CFE_SIM_STEPPING AND CFE_SIM_STEPPING)
    list(APPEND PSP_TARGET_MODULE_LIST sim_stepping)
endif()
