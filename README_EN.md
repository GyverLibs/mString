This is an automatic translation, may be incorrect in some places. See sources and examples!

# mstring
Sharp as diarrhea and light as a peryshko replacement String
- almost a complete analogue of String, but static
- Additional functions for flash string
- There are several built -in functions of parsing lines

## compatibility
Compatible with all arduino platforms (used arduino functions)

## Content
- [installation] (# Install)
- [initialization] (#init)
- [use] (#usage)
- [Example] (# Example)
- [versions] (#varsions)
- [bugs and feedback] (#fedback)

<a id="install"> </a>
## Installation
- The library can be found by the name ** mstring ** and installed through the library manager in:
    - Arduino ide
    - Arduino ide v2
    - Platformio
- [download the library] (https://github.com/gyverlibs/mstring/archive/refs/heads/main.zip) .Zip archive for manual installation:
    - unpack and put in * C: \ Program Files (X86) \ Arduino \ Libraries * (Windows X64)
    - unpack and put in * C: \ Program Files \ Arduino \ Libraries * (Windows X32)
    - unpack and put in *documents/arduino/libraries/ *
    - (Arduino id) Automatic installation from. Zip: * sketch/connect the library/add .Zip library ... * and specify downloaded archive
- Read more detailed instructions for installing libraries [here] (https://alexgyver.ru/arduino-first/#%D0%A3%D1%81%D1%82%D0%B0%BD%D0%BE%BE%BE%BED0%B2%D0%BA%D0%B0_%D0%B1%D0%B8%D0%B1%D0%BB%D0%B8%D0%BE%D1%82%D0%B5%D0%BA)
### Update
- I recommend always updating the library: errors and bugs are corrected in the new versions, as well as optimization and new features are added
- through the IDE library manager: find the library how to install and click "update"
- Manually: ** remove the folder with the old version **, and then put a new one in its place.“Replacement” cannot be done: sometimes in new versions, files that remain when replacing are deleted and can lead to errors!


<a id="init"> </a>
## initialization
The library can work in two modes:
- internal buffer (default) - the text buffer is created inside the object `mstring <size>`
- External buffer - when creating an object, the external Char of the Massive and its size are transmitted.To turn on the external buffer mode, you need to declare `#define ms_external` before connecting the library

### inner buffer
`` `CPP
#include <mstring.h>
// Inner buffer
// size in the number of characters
MSTring <DARAS> STR;
`` `

## Outside Boofer
`` `CPP
mstring (char* nbuf, uint16_t size, bool clear = true);
// nbuf - external char buffer
// size - its size
// Clear - Clean in initialization
`` `

Example:
`` `CPP
#define ms_external
#include <mstring.h>

// with cleaning for the correct initialization of memory
Char Buf1 [10];
Mstring str1 (BUF, 10);

// without cleaning (line "Hello" will remain)
Char Buf2 [10] = "HELLO";
Mstring str2 (BUF2, 10, FALSE);
`` `

<a id="usage"> </a>
## Usage
`` `CPP
// =========== System =================
uint16_t Length ();// current size (in the number of characters)
VOID updatelength ();// count the length (if the line changes from the outside)
Uint16_T Capacy ();// maximum size (in the number of characters)
Void Clear ();// Clean

// ========= Effect ==============
VOID Add ([char / char* / fstring / number / string]);// Add (almost any type of data)
VOID Add_P (pgm_p s);// Add a string from flash
VOID Add (Char* str, uint16_t Len);// Add a line from the buffer
VOID Add (uint8_t* str, uint16_t len);// Add a line from the buffer

str += [char / char* / fstring / number / string];// Add (almost any type of data)
str = str + [char / char* / fstring / numbers / string];// Summage (almost any type of data)

// ========== Comparison ==============
Bool Equals (Char* S);// coincides with the line
Bool Equals_P (pgm_p s);// coincides with a string of flash

str == [char / char* / number / string];// compare (almost any type of data)

// ======= Access to the buffer ===========
// Reading the symbol by index
str [idx];
str.buf [idX];
Str.Charat (IDX);

// recording a symbol by index
str [idX] = C;
str.buf [idx] = s;
Str.Setcharat (IDX, C);

// Access to Char Boofer
Char [] buf;
char* c_str ();

// =========== Export ==============
int32_t toint (from = 0);// B 32 bits the whole starting with from from
Float Tofloat (from = 0);// Float starting with from from
VOID Substring (from, to, char* arr);// copy from frombrom to to external arr

// ======= Transformation ============
VOID TRUNCATE (amount);// Cut from the end to amount
VOID Remove (IDX, Amount);// remove (cut) amount characters starting with IDX

VOID TolowerCase ();// Transform letters to the lower register (ascii)
VOID TUPPERCASE ();// Transform letters to the upper register (ASCII)

// ============ Search ================
int indexof (char, from = 0);// Find the Char symbol, search for from from from
int indexof (char*, from = 0);// Find the line char, search for from from from

int Lastindexof (char);// Find the last Charus Symbol
int Lastindexof (Char, from);// Find the last symbol of Char, search for from from from

Bool Startswith (Char* S);// begin with
Bool Startswith_p (PGM_P S);// starts with a line from flash

Bool Endswith (Char *S);// ends on
Bool endswith_p (pgm_p s);// ends on a line from Flash

// ========= Separation ===============
int splitamount (char div = ',');// Count the number of tuning by the separator
int split (char ** str, char div = ',');// divide into lines by divider DIV
VOID UNSPLIT (Char Div = ',');// Return dividers after split

// ========== Parsing ==============
// Parsing package in which the data is separated
// DATA - integer array of any type
// bsize - weight type weight (byte - 1, uint16_t - 2, long - 4)
// Len - the size of the array in the number of cells
// div - division
int Parse (Void* Data, Uint8_t Bsize, Int Len, Char Div = ',');

// Outdated
int Parsebytes (Data, Len, Div);// Parrow the contents into the BYTE array Len Len
Intseints (Data, Len, Div);// Parisen the contents into the INT array LEN LEN
`` `

<a id="EXAMPLE"> </a>
## Example
`` `CPP
#include "Mstring.h"
VOID setup () {
  Serial.Begin (9600);
  /*
    Mstring <50> str;
    str = "Kek";
    str = str + ',' + 12345 + ',' + 3.14 + ',' + "hello";
    Serial.println (str.buf);
    str = 1234;
    Serial.println (str.toint ());
    // sketch occupies 2522/198 byte
  */
  /*
    // Comparison with String
    String Str;
    str = "Kek";
    str = str + ',' + 12345 + ',' + 3.14 + ',' + "hello";
    Serial.println (str);
    str = 1234;
    Serial.println (str.toint ());
    // sketch occupies 5370/208 byte
  */

  // other tests
  Mstring <50> test;

  Test = "PUK";
  Test += "Kek";
  Test = test + "Cheburek" + ',' + 123 + ',' + 3.14;

  Serial.println (test.buf);// Puk Kek Cheburek, 123,3.14
  test.clear ();// Clean
  // test = "";// similarly

  Mstring <10> some;
  some = "Added";
  String str = "string";
  Test += some.buf;
  Test += str;

  Serial.println (test.buf);// Added String

  // Parsing
  Test = "1234,2345,Cranberries -3456,4567,5,6 ";
  Serial.println (test.startswith ("lol2"));// 0
  Serial.println (test.startswith ("1234"));// 1
  Serial.println (test.indexof ('k'));// -1

  Int16_t Data [10];
  int side = test.parse (Data, 2, 10);// 10 cells of 2 bytes
  Serial.println (get);// 6
  Serial.println ();

  for (int i = 0; i <get; i ++) {
    Serial.println (Data [i]);// 1234 2345 -3456 4567 5 6
  }

  // search
  Test = "PUK KEK HELLO FREEND HELLO World";
  Serial.println (test.indexof ('h'));// 8
  Serial.println (test.indexof ('h', 9));// 21
  Serial.println (Test.indexof ("Friend"));// 14

  // Comparison
  Test = 12;
  Serial.println (test == 12);// 1

  Test = "Kek";
  Serial.println (test == "Kek");// 1

  Mstring <4> test2;
  Test2 = "Kek";
  Serial.println (test == test2.buf);// 1

  // Selection
  Test = "ABCD, 123, -456.3.14";
  Serial.println (test.toint (5));// 123
  Serial.println (test.toint (9));// -456
  Serial.println (test.tofloat (14));// 3.14

  Char Buf3 [10];
  test.substring (0, 5, buf3);
  Serial.println (BUF3);// ABCD, 1

  Test.remove (5, 4);
  Serial.println (test.buf);// ABCD, -456.3.14
  test.touppercase ();
  Serial.println (test.buf);// ABCD, -456.3.14
  test.truncate (4);
  Serial.println (test.buf);// ABCD, -456,

  // Separation
  Test = "Hello, 1234, Test, 5678";
  Char* strings [test.splitamount (',')];
  int amount = test.split (strings, ',');
  // Action will ruin the line by adding NULLS to it!

  for (int i = 0; i <amount; i ++) {
    Serial.println (strings [i]);
  }
  
  Serial.println (atoi (strings [1]));
  Serial.println (atof (strings [2]));
  
  // Return the line to the original form
  test.unsplit ();
}

VOID loop () {
}
`` `

<a id="versions"> </a>
## versions
- V1.0
- V1.1 - broke the utilities into .H .cpp
- v1.1.1 - Fixed compilation error
- V1.2
    - Fixed update uint32_t numbers
    - Added the mode of the external buffer
    - Added _p functions for lines from flash
    - Added UNSPLIT ()
- v1.3 - added the universal function PARSE
- V1.4 - the possibility of initializing an external buffer without cleaning
- v1.5 - added updatelength ()
- V1.6 - Fixed error on ESP32, added Splitamount ()
- V1.7 - speed optimization, added Add (uint8_t* str, uint16_t Len), Lastindexof and Endswith

<a id="feedback"> </a>
## bugs and feedback
Create ** Issue ** when you find the bugs, and better immediately write to the mail [alex@alexgyver.ru] (mailto: alex@alexgyver.ru)
The library is open for refinement and your ** pull Request ** 'ow!


When reporting about bugs or incorrect work of the library, it is necessary to indicate:
- The version of the library
- What is MK used
- SDK version (for ESP)
- version of Arduino ide
- whether the built -in examples work correctly, in which the functions and designs are used, leading to a bug in your code
- what code has been loaded, what work was expected from it and how it works in reality
- Ideally, attach the minimum code in which the bug is observed.Not a canvas of a thousand lines, but a minimum code