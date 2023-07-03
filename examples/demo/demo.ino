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
  char* strings[test.splitAmount(',')];
  
  int amount = test.split(strings, ',');
  // также вернёт количество подстрок (равное splitAmount выше)
  // действие испортит строку, добавив в неё NULLы!

  for (int i = 0; i < amount; i++) {
    Serial.println(strings[i]);
  }
  
  test.unsplit(',');    // вернуть строку к исходному виду
}

void loop() {
}
