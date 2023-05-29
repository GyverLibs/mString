[![latest](https://img.shields.io/github/v/release/GyverLibs/mString.svg?color=brightgreen)](https://github.com/GyverLibs/mString/releases/latest/download/mString.zip)
[![Foo](https://img.shields.io/badge/Website-AlexGyver.ru-blue.svg?style=flat-square)](https://alexgyver.ru/)
[![Foo](https://img.shields.io/badge/%E2%82%BD$%E2%82%AC%20%D0%9D%D0%B0%20%D0%BF%D0%B8%D0%B2%D0%BE-%D1%81%20%D1%80%D1%8B%D0%B1%D0%BA%D0%BE%D0%B9-orange.svg?style=flat-square)](https://alexgyver.ru/support_alex/)
[![Foo](https://img.shields.io/badge/README-ENGLISH-blueviolet.svg?style=flat-square)](https://github-com.translate.goog/GyverLibs/mString?_x_tr_sl=ru&_x_tr_tl=en)  

[![Foo](https://img.shields.io/badge/ПОДПИСАТЬСЯ-НА%20ОБНОВЛЕНИЯ-brightgreen.svg?style=social&logo=telegram&color=blue)](https://t.me/GyverLibs)

# mString
РЕЗКАЯ КАК ПОНОС И ЛЁГКАЯ КАК ПЁРЫШКО ЗАМЕНА STRING
- Практически полный аналог String, но статический
- Есть несколько встроенных функций парсинга строк

### Совместимость
Совместима со всеми Arduino платформами (используются Arduino-функции)

## Содержание
- [Установка](#install)
- [Инициализация](#init)
- [Использование](#usage)
- [Пример](#example)
- [Версии](#versions)
- [Баги и обратная связь](#feedback)

<a id="install"></a>
## Установка
- Библиотеку можно найти по названию **mString** и установить через менеджер библиотек в:
    - Arduino IDE
    - Arduino IDE v2
    - PlatformIO
- [Скачать библиотеку](https://github.com/GyverLibs/mString/archive/refs/heads/main.zip) .zip архивом для ручной установки:
    - Распаковать и положить в *C:\Program Files (x86)\Arduino\libraries* (Windows x64)
    - Распаковать и положить в *C:\Program Files\Arduino\libraries* (Windows x32)
    - Распаковать и положить в *Документы/Arduino/libraries/*
    - (Arduino IDE) автоматическая установка из .zip: *Скетч/Подключить библиотеку/Добавить .ZIP библиотеку…* и указать скачанный архив
- Читай более подробную инструкцию по установке библиотек [здесь](https://alexgyver.ru/arduino-first/#%D0%A3%D1%81%D1%82%D0%B0%D0%BD%D0%BE%D0%B2%D0%BA%D0%B0_%D0%B1%D0%B8%D0%B1%D0%BB%D0%B8%D0%BE%D1%82%D0%B5%D0%BA)
### Обновление
- Рекомендую всегда обновлять библиотеку: в новых версиях исправляются ошибки и баги, а также проводится оптимизация и добавляются новые фичи
- Через менеджер библиотек IDE: найти библиотеку как при установке и нажать "Обновить"
- Вручную: **удалить папку со старой версией**, а затем положить на её место новую. "Замену" делать нельзя: иногда в новых версиях удаляются файлы, которые останутся при замене и могут привести к ошибкам!


<a id="init"></a>
## Инициализация
Библиотека может работать в двух режимах:
- Внутренний буфер (по умолчанию) - текстовый буфер создаётся внутри объекта `mString<размер>`
- Внешний буфер - при создании объекта mString передаётся внешний char массив и его размер. Для включения режима внешнего буфера нужно объявить `#define MS_EXTERNAL` перед подключением библиотеки

```cpp
// в обычном режиме (внутренний буфер)
// размер в количестве символов
mString<размер> str;

// внешний буфер
// размер в количестве байт (буфер должен быть на 1 длиннее макс. длины текста)
char buf[размер];
mString str(buf, размер);
```

<a id="usage"></a>
## Использование
```cpp
str.length();                                           // текущий размер
str.capacity();                                         // максимальный размер (в кол-ве символов)
str.clear();                                            // очистить
str.add( [char / char* / Fchar / числа / String] );     // добавить
str += [char / char* / Fchar / числа / String];         // добавить
str = str + [char / char* / Fchar / числа / String];    // суммировать
str == [char / char* / числа / String];                 // сравнить

// Для добавления/сравнения с mString используй str.buf

// Чтение символа по индексу
str[idx];
str.buf[idx];
str.charAt(idx);

// Запись символа по индексу
str[idx] = с;
str.buf[idx] = с;
str.setCharAt(idx, c);

// Доступ к char буферу
str.buf;
str.c_str();

str.toInt(from);            // преобразовать в int начиная с from
str.toUint(from);           // преобразовать в uint начиная с from
str.toFloat(from);          // преобразовать в float начиная с from
str.startsWith(char*);      // начинается с
str.substring(from, to, char* arr); // скопировать с from до to во внешний arr
str.truncate(amount);       // обрезать с конца на amount
str.remove(idx, amount);    // удалить (вырезать) amount символов начиная с idx
str.toLowerCase();          // преобразовать буквы в нижний регистр
str.toUpperCase();          // преобразовать буквы в верхний регистр
str.indexOf(char, from);    // найти символ char, искать начиная с from
str.indexOf(char*, from);   // найти строку char, искать начиная с from
str.split(char* str[], div);// разделить на строки по разделителю div

// Парсинг пакета, в котором данные разделены разделителем div и оканчиваются символом ter
str.parseBytes(data, len, div, ter);    // распарсить содержимое в массив byte длиной len
str.parseInts(data, len, div, ter);     // распарсить содержимое в массив int длиной len

// div и ter по умолчанию ',' и NULL
// Например для парсинга таких пакетов: "12,34,56"
// Кастомные: "12;34;56;78\n"
// Парсим str.parseBytes(data, len, ';', '\n')
```

<a id="example"></a>
## Пример
```cpp
#include "mString.h"
void setup() {
  Serial.begin(9600);
  /*
    mString<50> str;
    str = "kek";
    str = str + ',' + 12345 + ',' + 3.14 + ',' + "hello";
    Serial.println(str.buf);
    str = 1234;
    Serial.println(str.toInt());
    // скетч занимает 2522/198 байт
  */
  /*
    // сравнение со String
    String str;
    str = "kek";
    str = str + ',' + 12345 + ',' + 3.14 + ',' + "hello";
    Serial.println(str);
    str = 1234;
    Serial.println(str.toInt());
    // скетч занимает 5370/208 байт
  */

  // прочие тесты
  mString<50> test;

  test = "puk ";
  test += "kek ";
  test = test + "cheburek" + ',' + 123 + ',' + 3.14;

  Serial.println(test.buf);   // puk kek cheburek,123,3.14
  test.clear();   // очистить
  //test = "";    // аналогично

  mString<10> some;
  some = "added ";
  String str = "String";
  test += some.buf;
  test += str;

  Serial.println(test.buf);   // added String

  // парсинг
  test = "1234,2345,3456,4567,5,6";
  Serial.println(test.startsWith("lol2"));  // 0
  Serial.println(test.startsWith("1234"));  // 1
  Serial.println(test.indexOf('k'));    // -1

  int data[10];
  byte get = test.parseInts(data, 10);
  Serial.println(get);    // 6
  Serial.println();

  for (int i = 0; i < get; i++) {
    Serial.println(data[i]);   // 1234 2345 3456 4567 5 6
  }

  // поиск
  test = "puk kek hello friend hello world";
  Serial.println(test.indexOf('h'));       // 8
  Serial.println(test.indexOf('h', 9));    // 21
  Serial.println(test.indexOf("friend"));  // 14

  // сравнение
  test = 12;
  Serial.println(test == 12);     // 1

  test = "kek";
  Serial.println(test == "kek");  // 1

  mString<40> test2;
  test2 = "kek";
  Serial.println(test == test2.buf);  // 1

  // выделение
  test = "abcd,123,-456,3.14";
  Serial.println(test.toInt(5));    // 123
  Serial.println(test.toInt(9));    // -456
  Serial.println(test.toFloat(14)); // 3.14

  char buf3[10];
  test.substring(0, 5, buf3);
  Serial.println(buf3);   // abcd,1

  test.remove(5, 4);
  Serial.println(test.buf);   // abcd,-456,3.14
  test.toUpperCase();
  Serial.println(test.buf);   // ABCD,-456,3.14
  test.truncate(4);
  Serial.println(test.buf);   // ABCD,-456,

  // разделение
  test = "hello,1234,test,5678";
  char* strings[5];
  int amount = test.split(strings, ',');
  // действие испортит строку, добавив в неё NULLы!

  for (int i = 0; i < amount; i++) {
    Serial.println(strings[i]);
  }
}

void loop() {
}
```

<a id="versions"></a>
## Версии
- v1.0
- v1.1 - разбил утилиты на .h .cpp
- v1.1.1 - исправлена ошибка компиляции
- v1.2 - исправлено прибавление uint32_t чисел, добавлен режим внешнего буфера

<a id="feedback"></a>
## Баги и обратная связь
При нахождении багов создавайте **Issue**, а лучше сразу пишите на почту [alex@alexgyver.ru](mailto:alex@alexgyver.ru)  
Библиотека открыта для доработки и ваших **Pull Request**'ов!


При сообщении о багах или некорректной работе библиотеки нужно обязательно указывать:
- Версия библиотеки
- Какой используется МК
- Версия SDK (для ESP)
- Версия Arduino IDE
- Корректно ли работают ли встроенные примеры, в которых используются функции и конструкции, приводящие к багу в вашем коде
- Какой код загружался, какая работа от него ожидалась и как он работает в реальности
- В идеале приложить минимальный код, в котором наблюдается баг. Не полотно из тысячи строк, а минимальный код
