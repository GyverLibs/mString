[![latest](https://img.shields.io/github/v/release/GyverLibs/mString.svg?color=brightgreen)](https://github.com/GyverLibs/mString/releases/latest/download/mString.zip)
[![Foo](https://img.shields.io/badge/Website-AlexGyver.ru-blue.svg?style=flat-square)](https://alexgyver.ru/)
[![Foo](https://img.shields.io/badge/%E2%82%BD$%E2%82%AC%20%D0%9D%D0%B0%20%D0%BF%D0%B8%D0%B2%D0%BE-%D1%81%20%D1%80%D1%8B%D0%B1%D0%BA%D0%BE%D0%B9-orange.svg?style=flat-square)](https://alexgyver.ru/support_alex/)
[![Foo](https://img.shields.io/badge/README-ENGLISH-blueviolet.svg?style=flat-square)](https://github-com.translate.goog/GyverLibs/mString?_x_tr_sl=ru&_x_tr_tl=en)  

[![Foo](https://img.shields.io/badge/ПОДПИСАТЬСЯ-НА%20ОБНОВЛЕНИЯ-brightgreen.svg?style=social&logo=telegram&color=blue)](https://t.me/GyverLibs)

# mString
РЕЗКАЯ КАК ПОНОС И ЛЁГКАЯ КАК ПЁРЫШКО ЗАМЕНА STRING
- Практически полный аналог String, но статический
- Дополнительные функции для Flash-строк
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

### Внутренний буфер
```cpp
#include <mString.h>
// внутренний буфер
// размер в количестве символов
mString<размер> str;
```

### Внешний буфер
```cpp
mString(char* nbuf, uint16_t size, bool clear = true);
// nbuf - внешний char буфер
// size - его размер
// clear - очищать при инициализации
```

Пример:
```cpp
#define MS_EXTERNAL
#include <mString.h>

// с очисткой для корректной инициализации памяти
char buf1[10];
mString str1(buf, 10);

// без очистки (строка "hello" останется)
char buf2[10] = "hello";
mString str2(buf2, 10, false);
```

<a id="usage"></a>
## Использование
```cpp
// =========== СИСТЕМА ===========
uint16_t length();                                      // текущий размер (в кол-ве символов)
void updateLength();                                    // пересчитать длину (если строка меняется извне)
uint16_t capacity();                                    // максимальный размер (в кол-ве символов)
void clear();                                           // очистить

// ========= ПРИБАВЛЕНИЕ =========
void add( [char / char* / fstring / числа / String] );  // добавить (почти любой тип данных)
void add_P(PGM_P s);                                    // добавить строку из Flash
void add(char* str, uint16_t len);                      // добавить строку из буфера
void add(uint8_t* str, uint16_t len);                   // добавить строку из буфера

str += [char / char* / fstring / числа / String];       // добавить (почти любой тип данных)
str = str + [char / char* / fstring / числа / String];  // суммировать (почти любой тип данных)

// ========== СРАВНЕНИЕ ==========
bool equals(char* s);                       // совпадает со строкой
bool equals_P(PGM_P s);                     // совпадает со строкой из Flash

str == [char / char* / числа / String];     // сравнить (почти любой тип данных)

// ======= ДОСТУП К БУФЕРУ ========
// Чтение символа по индексу
str[idx];
str.buf[idx];
str.charAt(idx);

// Запись символа по индексу
str[idx] = с;
str.buf[idx] = с;
str.setCharAt(idx, c);

// Доступ к char буферу
char[] buf;
char* c_str();

// =========== ЭКСПОРТ ===========
int32_t toInt(from = 0);                // в 32 бит целое начиная с from
float toFloat(from = 0);                // в float начиная с from
void substring(from, to, char* arr);    // скопировать с from до to во внешний arr

// ======= ПРЕОБРАЗОВАНИЕ ========
void truncate(amount);          // обрезать с конца на amount
void remove(idx, amount);       // удалить (вырезать) amount символов начиная с idx

void toLowerCase();             // преобразовать буквы в нижний регистр (ASCII)
void toUpperCase();             // преобразовать буквы в верхний регистр (ASCII)

// ============ ПОИСК ============
int indexOf(char, from = 0);    // найти символ char, искать начиная с from
int indexOf(char*, from = 0);   // найти строку char, искать начиная с from

int lastIndexOf(char);          // найти последний символ char
int lastIndexOf(char, from);    // найти последний символ char, искать начиная с from

bool startsWith(char* s);       // начинается с
bool startsWith_P(PGM_P s);     // начинается со строки из Flash

bool endsWith(char *s);         // заканчивается на
bool endsWith_P(PGM_P s);       // заканчивается на строку из Flash

// ========= РАЗДЕЛЕНИЕ =========
int splitAmount(char div = ',');        // посчитать количество подстрок по разделителю
int split(char** str, char div = ',');  // разделить на строки по разделителю div
void unsplit(char div = ',');           // вернуть разделители после split

// ========== ПАРСИНГ ==========
// Парсинг пакета, в котором данные разделены разделителем div
// data - целочисленный массив любого типа
// bsize - вес типа массива (byte - 1, uint16_t - 2, long - 4)
// len - размер массива в количестве ячеек
// div - разделитель
int parse(void* data, uint8_t bsize, int len, char div = ',');

// устаревшие
int parseBytes(data, len, div); // распарсить содержимое в массив byte длиной len
int parseInts(data, len, div);  // распарсить содержимое в массив int длиной len
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
  test = "1234,2345,-3456,4567,5,6";
  Serial.println(test.startsWith("lol2"));  // 0
  Serial.println(test.startsWith("1234"));  // 1
  Serial.println(test.indexOf('k'));    // -1

  int16_t data[10];
  int get = test.parse(data, 2, 10);   // 10 ячеек по 2 байта
  Serial.println(get);    // 6
  Serial.println();

  for (int i = 0; i < get; i++) {
    Serial.println(data[i]);   // 1234 2345 -3456 4567 5 6
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
  char* strings[test.splitAmount(',')];
  int amount = test.split(strings, ',');
  // действие испортит строку, добавив в неё NULLы!

  for (int i = 0; i < amount; i++) {
    Serial.println(strings[i]);
  }
  
  Serial.println(atoi(strings[1]));
  Serial.println(atof(strings[2]));
  
  // вернуть строку к исходному виду
  test.unsplit();
}

void loop() {
}
```

<a id="versions"></a>
## Версии
- v1.0
- v1.1 - разбил утилиты на .h .cpp
- v1.1.1 - исправлена ошибка компиляции
- v1.2
    - Исправлено прибавление uint32_t чисел
    - Добавлен режим внешнего буфера
    - Добавлены _P функции для строк из Flash
    - Добавлена unsplit()
- v1.3 - добавлена универсальная функция parse
- v1.4 - возможность инициализации внешнего буфера без очистки
- v1.5 - добавлена updateLength()
- v1.6 - исправлена ошибка на ESP32, добавлена splitAmount()
- v1.7 - оптимизация скорости, добавлены add(uint8_t* str, uint16_t len), lastIndexOf и endsWith

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
