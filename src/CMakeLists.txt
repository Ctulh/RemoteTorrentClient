set(LIB_NAME TorrentManagerLib)

set(INCLUDE_PATH ${PROJECT_SOURCE_DIR}/include)

set(HEADERS ${INCLUDE_PATH}/Framework/Adapters/TgAdapter.hpp
            ${INCLUDE_PATH}/Utils/WrongConfigPathException.hpp
            ${INCLUDE_PATH}/Application/IApplication.hpp
            ${INCLUDE_PATH}/Domain/TransmissionImpl/TransmissionTorrentClient.hpp
            ${INCLUDE_PATH}/Utils/FileWriter.hpp)



set(SOURCES
            Application/ApplicationImpl.cpp
            Utils/WrongConfigPathException.cpp
            Framework/Adapters/TgAdapter.cpp
            Domain/TransmissionImpl/TransmissionTorrentClient.cpp
            Domain/TransmissionImpl/TransmissionTorrentParser.cpp
            Domain/TransmissionImpl/TransmissionTorrentPerformer.cpp
            Utils/StringOperations.cpp
            Utils/FileWriter.cpp
            Utils/FileReader.cpp
            Utils/JsonConfigReader.cpp)


add_library(${LIB_NAME} ${SOURCES} ${HEADERS})

target_include_directories(${LIB_NAME} PUBLIC ${INCLUDE_PATH} ${CONAN_INCLUDE_DIRS})
target_link_libraries(${LIB_NAME} PRIVATE ${CONAN_LIBS_NLOHMAN_JSON})
