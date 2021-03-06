# Find Boost library
find_package(Boost REQUIRED)

if(REAKTORO_USE_OPENLIBM)
    find_package(openlibm REQUIRED)
endif()

# Find nlohmann_json installed from conda-forge
find_package(nlohmann_json 3.4.0 REQUIRED)

# Find ThermoFun library and define a pre-processor macro REAKTORO_USING_THERMOFUN if so
find_package(ThermoFun REQUIRED)

if(ThermoFun_FOUND)
    add_compile_definitions(REAKTORO_USING_THERMOFUN)
endif()

# Find pybind11 library (if needed)
if(REAKTORO_BUILD_PYTHON)
    find_package(pybind11 REQUIRED)
    if(NOT pybind11_FOUND)
        message(WARNING "Could not find pybind11 - the Python module `reaktoro` will not be built.")
        set(REAKTORO_BUILD_PYTHON OFF)
    else()
        message(STATUS "Found pybind11 v${pybind11_VERSION}: ${pybind11_INCLUDE_DIRS}")
    endif()
endif()
