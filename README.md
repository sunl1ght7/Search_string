Search Engine Project

Проект поискового движка для обработки текстовых документов с возможностью полнотекстового поиска и ранжирования результатов по релевантности.

Особенности:
Полнотекстовый поиск по коллекции документов

Многопоточная индексация документов

Ранжирование результатов по релевантности

Поддержка JSON для конфигурации и запросов

Модульное тестирование с Google Test

Кроссплатформенность (Windows/Linux)

🛠 Технологии
C++17

CMake для сборки

nlohmann/json для работы с JSON

Google Test для модульного тестирования

STL (многопоточность, файловая система, алгоритмы)

Структура проекта
text
SearchEngine/
├── CMakeLists.txt              # Корневой файл сборки
├── src/                        # Исходный код
│   ├── CMakeLists.txt
│   ├── main.cpp               # Главная программа
│   ├── ConverterJSON.cpp      # Работа с JSON файлами
│   ├── ConverterJSON.h
│   ├── InvertedIndex.cpp      # Инвертированный индекс
│   ├── InvertedIndex.h
│   ├── SearchServer.cpp       # Поисковый сервер
│   └── SearchServer.h
├── tests/                      # Тесты
│   ├── CMakeLists.txt
│   ├── test_main.cpp          # Главный файл тестов
│   ├── test_invertedindex.cpp # Тесты индекса
│   └── test_searchserver.cpp  # Тесты поиска
├── resources/                  # Примеры документов
│   ├── file001.txt
│   ├── file002.txt
│   └── file003.txt
├── config.json                # Конфигурация
├── requests.json              # Поисковые запросы
└── answers.json               # Результаты поиска (генерируется)
📋 Требования
CMake 3.16+

C++17 совместимый компилятор (GCC 8+, Clang 7+, MSVC 2019+)

Git (для клонирования репозитория)

Установка и запуск
Клонирование репозитория
bash
git clone <url-репозитория>
cd search_engine
Сборка проекта
bash

Создание директории сборки
mkdir build
cd build

Генерация проекта
cmake ..

Сборка
cmake --build . --config Release

Запуск программы
bash

Копирование необходимых файлов
cp ../config.json ../requests.json ../resources/ ./bin/Release/


Запуск поискового движка
./bin/Release/search_engine

Запуск тестов
bash
./bin/Release/search_engine_tests

Формат результатов
Результаты сохраняются в answers.json:

json
{
  "answers": {
    "request001": {
      "relevance": [
        {"docid": 2, "rank": 1.0},
        {"docid": 0, "rank": 0.7},
        {"docid": 1, "rank": 0.3}
      ],
      "result": true
    }
  }
}

Тестирование
Проект включает comprehensive тесты:

Тесты инвертированного индекса - проверка индексации документов

Тесты поискового сервера - проверка алгоритмов поиска и ранжирования

Запуск тестов:

bash
cd build
ctest --verbose

Алгоритм работы
Загрузка конфигурации из config.json

Индексация документов - построение инвертированного индекса

Обработка запросов из requests.json

Поиск и ранжирование - нахождение релевантных документов

Сохранение результатов в answers.json


Настройка под свои нужды
Добавьте документы в папку resources/

Обновите config.json с путями к вашим файлам

Измените requests.json с вашими поисковыми запросами

Пересоберите и запустите проект
