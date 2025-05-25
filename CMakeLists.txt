cmake_minimum_required(VERSION 3.16)
project(mac_stat VERSION 1.0 LANGUAGES CXX)

# 병렬 빌드 활성화
include(ProcessorCount)
ProcessorCount(N)
if(NOT N EQUAL 0)
    set(CMAKE_BUILD_PARALLEL_LEVEL ${N})
endif()

# 디버그 모드로 설정
set(CMAKE_BUILD_TYPE Debug)

# 컴파일러 최적화 옵션
if(APPLE)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2")
endif()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Unity 빌드 비활성화 (디버깅을 위해)
set(CMAKE_UNITY_BUILD OFF)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# Qt 경로 설정
set(CMAKE_PREFIX_PATH "/opt/homebrew/opt/qt@6")
set(QT_LIBRARY_DIR "/opt/homebrew/opt/qt@6/lib")

# Qt 라이브러리 찾기
find_package(Qt6 COMPONENTS Core Widgets Gui DBus REQUIRED)

# macOS 번들 설정
set(CMAKE_MACOSX_BUNDLE ON)
set(MACOSX_BUNDLE_GUI_IDENTIFIER "com.yourdomain.mac_stat")
set(MACOSX_BUNDLE_BUNDLE_NAME "Mac Stat")
set(MACOSX_BUNDLE_BUNDLE_VERSION "1.0")
set(MACOSX_BUNDLE_SHORT_VERSION_STRING "1.0")
set(MACOSX_BUNDLE_INFO_PLIST ${CMAKE_SOURCE_DIR}/resources/Info.plist)
set(MACOSX_BUNDLE_ICON_FILE "AppIcon.icns")

# 아이콘 파일 설정
set(APP_ICON_MACOSX ${CMAKE_SOURCE_DIR}/AppIcon.icns)
set_source_files_properties(${APP_ICON_MACOSX} PROPERTIES
    MACOSX_PACKAGE_LOCATION "Resources"
)

# 소스 파일 추가
set(SOURCES
    src/main.cpp
    src/mainwindow.cpp
    src/system_stats/memory_stats.cpp
    ${APP_ICON_MACOSX}
)

# 헤더 파일 추가
set(HEADERS
    include/mainwindow.h
    include/system_stats/memory_stats.h
)

# 실행 파일 생성
add_executable(${PROJECT_NAME} MACOSX_BUNDLE ${SOURCES} ${HEADERS})

# Qt 라이브러리 링크
target_link_libraries(${PROJECT_NAME} PRIVATE
    Qt6::Core
    Qt6::Widgets
    Qt6::Gui
    Qt6::DBus
)

# 헤더 파일 경로 설정
target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_SOURCE_DIR}/include
)

# RPATH 설정
if(APPLE)
    # RPATH 설정
    set(CMAKE_INSTALL_RPATH "${QT_LIBRARY_DIR}")
    set(CMAKE_BUILD_WITH_INSTALL_RPATH TRUE)
    set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)

    set_target_properties(${PROJECT_NAME} PROPERTIES
        INSTALL_RPATH "@executable_path/../Frameworks;@loader_path/Frameworks;${QT_LIBRARY_DIR}"
        BUILD_WITH_INSTALL_RPATH TRUE
        BUILD_WITH_INSTALL_NAME_DIR TRUE
        MACOSX_BUNDLE_INFO_PLIST ${CMAKE_SOURCE_DIR}/resources/Info.plist
    )

    # macOS 번들에 Qt 프레임워크 포함
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E env DYLD_LIBRARY_PATH=${QT_LIBRARY_DIR}
        /opt/homebrew/opt/qt@6/bin/macdeployqt
        "${CMAKE_BINARY_DIR}/${PROJECT_NAME}.app"
        -verbose=1
        -always-overwrite
        -no-strip
        COMMENT "Deploying Qt frameworks..."
    )

    # 프레임워크 권한 설정
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND chmod -R +x "${CMAKE_BINARY_DIR}/${PROJECT_NAME}.app/Contents/Frameworks/"*
        COMMAND chmod +x "${CMAKE_BINARY_DIR}/${PROJECT_NAME}.app/Contents/MacOS/${PROJECT_NAME}"
        COMMAND chmod -R +x "${CMAKE_BINARY_DIR}/${PROJECT_NAME}.app/Contents/PlugIns"
        COMMENT "Setting executable permissions..."
    )

    # 서명
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND xattr -cr "${CMAKE_BINARY_DIR}/${PROJECT_NAME}.app"
        COMMAND codesign --force --deep --sign - "${CMAKE_BINARY_DIR}/${PROJECT_NAME}.app"
        COMMENT "Signing application..."
    )
endif() 