# This file will be configured to contain variables for CPack. These variables
# should be set in the CMake list file of the project before CPack module is
# included. The list of available CPACK_xxx variables and their associated
# documentation may be obtained using
#  cpack --help-variable-list
#
# Some variables are common to all generators (e.g. CPACK_PACKAGE_NAME)
# and some are specific to a generator
# (e.g. CPACK_NSIS_EXTRA_INSTALL_COMMANDS). The generator specific variables
# usually begin with CPACK_<GENNAME>_xxxx.


set(CPACK_BUILD_SOURCE_DIRS "F:/JetBrains/CPP_SE;F:/JetBrains/CPP_SE/cmake-build-debug")
set(CPACK_CMAKE_GENERATOR "Ninja")
set(CPACK_COMPONENT_UNSPECIFIED_HIDDEN "TRUE")
set(CPACK_COMPONENT_UNSPECIFIED_REQUIRED "TRUE")
set(CPACK_DEFAULT_PACKAGE_DESCRIPTION_FILE "D:/Jetbrain/CLion 2024.1.1/bin/cmake/win/x64/share/cmake-3.28/Templates/CPack.GenericDescription.txt")
set(CPACK_DEFAULT_PACKAGE_DESCRIPTION_SUMMARY "CPP_SE built using CMake")
set(CPACK_GENERATOR "TGZ")
set(CPACK_INNOSETUP_ARCHITECTURE "x64")
set(CPACK_INSTALL_CMAKE_PROJECTS "F:/JetBrains/CPP_SE/cmake-build-debug;CPP_SE;ALL;/")
set(CPACK_INSTALL_PREFIX "C:/Program Files (x86)/CPP")
set(CPACK_MODULE_PATH "F:/JetBrains/CPP_SE/libpqxx/cmake")
set(CPACK_NSIS_DISPLAY_NAME "CPP_SE 7.9.3")
set(CPACK_NSIS_INSTALLER_ICON_CODE "")
set(CPACK_NSIS_INSTALLER_MUI_ICON_CODE "")
set(CPACK_NSIS_INSTALL_ROOT "$PROGRAMFILES64")
set(CPACK_NSIS_PACKAGE_NAME "CPP_SE 7.9.3")
set(CPACK_NSIS_UNINSTALL_NAME "Uninstall")
set(CPACK_OBJCOPY_EXECUTABLE "D:/Jetbrain/CLion 2024.1.1/bin/mingw/bin/objcopy.exe")
set(CPACK_OBJDUMP_EXECUTABLE "D:/Jetbrain/CLion 2024.1.1/bin/mingw/bin/objdump.exe")
set(CPACK_OUTPUT_CONFIG_FILE "F:/JetBrains/CPP_SE/cmake-build-debug/CPackConfig.cmake")
set(CPACK_PACKAGE_DEFAULT_LOCATION "/")
set(CPACK_PACKAGE_DESCRIPTION_FILE "D:/Jetbrain/CLion 2024.1.1/bin/cmake/win/x64/share/cmake-3.28/Templates/CPack.GenericDescription.txt")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "CPP_SE built using CMake")
set(CPACK_PACKAGE_FILE_NAME "CPP_SE-7.9.3-win64")
set(CPACK_PACKAGE_INSTALL_DIRECTORY "CPP_SE 7.9.3")
set(CPACK_PACKAGE_INSTALL_REGISTRY_KEY "CPP_SE 7.9.3")
set(CPACK_PACKAGE_NAME "CPP_SE")
set(CPACK_PACKAGE_RELOCATABLE "true")
set(CPACK_PACKAGE_VENDOR "Humanity")
set(CPACK_PACKAGE_VERSION "7.9.3")
set(CPACK_PACKAGE_VERSION_MAJOR "0")
set(CPACK_PACKAGE_VERSION_MINOR "1")
set(CPACK_PACKAGE_VERSION_PATCH "1")
set(CPACK_READELF_EXECUTABLE "D:/Jetbrain/CLion 2024.1.1/bin/mingw/bin/readelf.exe")
set(CPACK_RESOURCE_FILE_LICENSE "D:/Jetbrain/CLion 2024.1.1/bin/cmake/win/x64/share/cmake-3.28/Templates/CPack.GenericLicense.txt")
set(CPACK_RESOURCE_FILE_README "D:/Jetbrain/CLion 2024.1.1/bin/cmake/win/x64/share/cmake-3.28/Templates/CPack.GenericDescription.txt")
set(CPACK_RESOURCE_FILE_WELCOME "D:/Jetbrain/CLion 2024.1.1/bin/cmake/win/x64/share/cmake-3.28/Templates/CPack.GenericWelcome.txt")
set(CPACK_SET_DESTDIR "OFF")
set(CPACK_SOURCE_7Z "ON")
set(CPACK_SOURCE_GENERATOR "7Z;ZIP")
set(CPACK_SOURCE_OUTPUT_CONFIG_FILE "F:/JetBrains/CPP_SE/cmake-build-debug/CPackSourceConfig.cmake")
set(CPACK_SOURCE_ZIP "ON")
set(CPACK_SYSTEM_NAME "win64")
set(CPACK_THREADS "1")
set(CPACK_TOPLEVEL_TAG "win64")
set(CPACK_WIX_SIZEOF_VOID_P "8")

if(NOT CPACK_PROPERTIES_FILE)
  set(CPACK_PROPERTIES_FILE "F:/JetBrains/CPP_SE/cmake-build-debug/CPackProperties.cmake")
endif()

if(EXISTS ${CPACK_PROPERTIES_FILE})
  include(${CPACK_PROPERTIES_FILE})
endif()
