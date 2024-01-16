# SF_Module_27
## Приложение для сетевого чата (использование протокола TCP, многопоточного программирования)
**Установка / Начало работы**

:white_check_mark: ___В каждый каталог необходимо скопировать библиотеку nlohmann/json.hpp: git@github.com:nlohmann/json.git___

___Сервер должен быть запущен первым!___

Запустить приложения: Server, Client1, Client2

При передаче данных на Server от Client в зависимости от режима автоматически создаются файлы:
clients.json (данные клиентов), log.json (сообщение с указанием даты отправки).

:white_check_mark: ___Чтобы начать, необходимо пройти регистрацию (режим 1) ввести:___
1. имя
2. логин
3. пароль (пароль сохраняется в виде хэша с использованием алгоритма SHA-1)

___Каждый из зарегистрированных пользователей, автоматически авторизуется___

:white_check_mark: ___Чтобы высылать сообщения другим пользователям или просмотреть личные сообщения,___

___необходимо авторизоваться (режим 2) ввести:___
1. логин
2. пароль (автоматически преобразовывается с использованием хэш-функции)

:white_check_mark: ___Высылать сообщения другим пользователям (режим 3), также передаются сообщения для пользователя от других клиентов___ 


:white_check_mark: ___Можно получить сообщения от других пользователей не высылая сообщения (режим 4)___


:white_check_mark: ___Отсоедениться от чата (режим 5)___ 


:white_check_mark: ___Выход из приложения (режим 6) Server остается активным и готов принимать данные от других Client___ 


___Cообщения сохраняются в файлах *.json на Server___

## Разработан
:wink: Поповой Оксаной Станиславовной (студент SkillFactory CPLUS-33)

### c использованием:

Паттерна проектирования Наблюдатель (Observer)
   
### Структура проекта

1. Класс Logger (на Server) через который происходит работа с файлами: чтение файла, запись файла на диск.
2. Класс ClientCode обеспечивает вызов функций для взаимодействия пользователей с чатом.
3. Класс User (пользователь IObserver) позволяет конкретному пользователю взаимодействовать с чатом:
      - создание нового пользователя;
      - авторизация;
      - выход из чата;
      - отправка сообщений  и получение сообщений;
4. Класс Chat (чат ISubject) взаимодействует с пользователем по сети:
      - добавление нового пользователя;
      - подключение пользователя к чату;
      - отсоединение пользователя от чата;
      - хранение и рассылка сообщений.
5. Класс Messages связан с классом Chat и User, позволяет отправлять и принимать сообщения по сети.
6. Класс ConnectionTCP обеспечивает связь пользователя и сервера с использованием протокола TCP.
7. В проекте реализованы:
      - Многопоточное программирование в функции void Messages::get_messages(ISubject* chat) и использование мьютексов в функции void Messages::receive_message(ISubject* chat, int connection, std::mutex& mtx).
      - Абстрактные классы: IObserver, ISubject.
      - Использованы принципы ООП: наследование, абстракция, инкапсуляция, RAII (Resource Acquisition Is Initialization).
      - Использован механизм Run-Time Type Information (RTTI).
      - Добавлена возможность обработки исключений.
      - Использованы контейнеры cтандартной библиотеки шаблонов STL.
