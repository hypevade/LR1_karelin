cmake_minimum_required(VERSION 3.26) # Обновляем минимально требуемую версию CMake до 3.26
project(LR1)

# Версия С++
set(CMAKE_CXX_STANDARD 17)

# Включение FetchContent модуля для загрузки внешних зависимостей
include(FetchContent)

# Определение nlohmann/json как внешней зависимости
FetchContent_Declare(
  json
  GIT_REPOSITORY https://github.com/nlohmann/json.git
  GIT_TAG v3.10.5 # Можете указать другую версию, если требуется
)

# Сделать библиотеку nlohmann/json доступной для проекта
FetchContent_MakeAvailable(json)

# Добавление в проект директорий lib, bin и tests
add_subdirectory(lib)
add_subdirectory(bin)

# Включение тестирования и добавление директории с тестами
enable_testing()
add_subdirectory(tests)

# Теперь вы можете связать nlohmann_json с вашими исполняемыми файлами или библиотеками
# используя target_link_libraries(ваша_цель nlohmann_json::nlohmann_json)
# Добавляем исполняемый файл для тестов

# Связываем исполняемый файл тестов с библиотекой nlohmann_json и необходимыми библиотеками для тестирования
target_link_libraries(lr1_tests nlohmann_json::nlohmann_json)
