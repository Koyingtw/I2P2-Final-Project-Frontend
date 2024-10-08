cmake_minimum_required(VERSION 3.27)
project(2024_I2P2_TowerDefense_with_answer)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -fsanitize=address")

set(CMAKE_OSX_ARCHITECTURES "arm64")

include_directories(.)
include_directories(Resource)
include_directories(/opt/homebrew/Cellar/websocketpp/0.8.2/include)
include_directories(/opt/homebrew/Cellar/boost/1.85.0/include)
include_directories(${CMAKE_SOURCE_DIR}/include)

find_package(Boost REQUIRED system thread)

file(COPY Resource/audios DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY Resource/fonts DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY Resource/images DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY Resource DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY allegro_monolith-5.2.dll DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

add_executable(2024_I2P2_TowerDefense_with_answer
        Engine/Allegro5Exception.cpp
        Engine/Allegro5Exception.hpp
        Engine/AudioHelper.cpp
        Engine/AudioHelper.hpp

        Engine/Collider.cpp
        Engine/Collider.hpp
        UI/Animation/DirtyEffect.cpp
        UI/Animation/DirtyEffect.hpp

        UI/Animation/ExplosionEffect.cpp
        UI/Animation/ExplosionEffect.hpp

        Engine/GameEngine.cpp
        Engine/GameEngine.hpp
        Engine/Group.cpp
        Engine/Group.hpp
        Engine/IControl.cpp
        Engine/IControl.hpp
        UI/Component/Image.cpp
        UI/Component/Image.hpp
        UI/Component/ImageButton.cpp
        UI/Component/ImageButton.hpp
        Engine/IObject.cpp
        Engine/IObject.hpp
        Engine/IScene.cpp
        Engine/IScene.hpp
        UI/Component/Label.cpp
        UI/Component/Label.hpp


        Engine/LOG.cpp
        Engine/LOG.hpp
        Scene/LoseScene.cpp
        Scene/LoseScene.hpp

        main.cpp

        # UI/Animation/Plane.cpp
        # UI/Animation/Plane.hpp

        Scene/PlayScene.cpp
        Scene/PlayScene.hpp
        Engine/Point.cpp
        Engine/Point.hpp
        Engine/Resources.cpp
        Engine/Resources.hpp
        UI/Component/Slider.cpp
        UI/Component/Slider.hpp

        Engine/Sprite.cpp
        Engine/Sprite.hpp
        Scene/StageSelectScene.cpp
        Scene/StageSelectScene.hpp

        Scene/WinScene.cpp
        Scene/WinScene.hpp

        # TOODO: [HACKATHON-1-SCENE] (2/4) Add the new scene source files here
        Scene/StartScene.cpp
        Scene/StartScene.h
        Scene/SettingsScene.cpp
        Scene/SettingsScene.hpp
#        UI/Component/TextInput.cpp
#        UI/Component/TextInput.hpp

#        add here

        Scene/ScoreboardScene.cpp
        Scene/ScoreboardScene.hpp

        Square/Square.cpp
        Square/Square.hpp

        Square/I_Square.cpp
        Square/I_Square.hpp

        Square/J_Square.cpp
        Square/J_Square.hpp

        Square/L_Square.cpp
        Square/L_Square.hpp

        Square/O_Square.cpp
        Square/O_Square.hpp

        Square/S_Square.cpp
        Square/S_Square.hpp

        Square/T_Square.cpp
        Square/T_Square.hpp

        Square/Z_Square.cpp
        Square/Z_Square.hpp

        Cube/Cube.cpp
        Cube/Cube.hpp

        Player/Player.cpp
        Player/Player.hpp

        Websocket/client.cpp
        Websocket/client.hpp
)

IF (WIN32)
    target_include_directories(2024_I2P2_TowerDefense_with_answer PUBLIC C:/allegro/include)
    target_link_directories(2024_I2P2_TowerDefense_with_answer PUBLIC C:/allegro/lib)
    target_compile_options(2024_I2P2_TowerDefense_with_answer PUBLIC ${ALLEGRO5_CFLAGS_OTHER})
    target_link_libraries(2024_I2P2_TowerDefense_with_answer liballegro_monolith)
ELSE()
    find_package(PkgConfig)
    pkg_check_modules(ALLEGRO5 REQUIRED allegro-5 allegro_main-5 allegro_font-5 allegro_dialog-5 allegro_primitives-5 allegro_image-5 allegro_ttf-5 allegro_audio-5 allegro_acodec-5)
    target_include_directories(2024_I2P2_TowerDefense_with_answer PUBLIC lib)
    target_include_directories(2024_I2P2_TowerDefense_with_answer PUBLIC ${ALLEGRO5_INCLUDE_DIRS})
    target_compile_options(2024_I2P2_TowerDefense_with_answer PUBLIC ${ALLEGRO5_CFLAGS_OTHER})
    target_link_libraries(2024_I2P2_TowerDefense_with_answer ${ALLEGRO5_LIBRARIES})
    target_link_libraries(2024_I2P2_TowerDefense_with_answer Boost::system Boost::thread pthread)
    target_link_directories(2024_I2P2_TowerDefense_with_answer PUBLIC ${ALLEGRO5_LIBRARY_DIRS})
    set(CMAKE_OSX_ARCHITECTURES "arm64")
ENDIF()