# `BitBool` library for C++ ![Version 1.2.0](https://img.shields.io/badge/Version-1.2.0-blue.svg)
#### *The ultimate C++ bit manipulation tool*
![C++98](https://img.shields.io/badge/C%2B%2B-98-yellow.svg) ![C++11](https://img.shields.io/badge/C%2B%2B-11-orange.svg)  

**Written by:** *Christopher Andrews.*  
**Licence:** *MIT*<sup>[*](https://github.com/Chris--A/BitBool#licence-information)</sup>

This class provides an efficient and easy to use method of dealing with bits. The library is infact a drop-in replacement for a `bool` array. However, it has many more uses and is perfect for use on embedded systems or critical systems where performance and efficiency matters.

### Contents
- [Installation](https://github.com/Chris--A/BitBool#installation)
  - [Arduino Users](https://github.com/Chris--A/BitBool#arduino-users)
  - [General C++ usage](https://github.com/Chris--A/BitBool#everyone-else-general-c-usage)
- [Basic Usage](https://github.com/Chris--A/BitBool#basic-usage)
  - [Creating a **`BitBool`**](https://github.com/Chris--A/BitBool#creating-a-bitbool)
  - [Turn something else into a **`BitBool`**](https://github.com/Chris--A/BitBool#turn-something-else-into-a-bitbool---)
  - [Reference a single bit of another object or **`BitBool`**](https://github.com/Chris--A/BitBool#reference-a-single-bit-of-another-object-or-bitbool---)
- [Advanced features](https://github.com/Chris--A/BitBool#advanced-features)
  - [Iterating a **`BitBool`**](https://github.com/Chris--A/BitBool#iterating-a-bitbool-)
  - [Selectively iterating a range of bits](https://github.com/Chris--A/BitBool#selectively-iterating-a-range-of-bits-)
  - [Customizing how a **`BitBool`** treats the data](https://github.com/Chris--A/BitBool#customizing-how-a-bitbool-treats-the-data)
    - Controlling the direction of bits and bytes
    - Optimization using a look-up table
- [Licence information](https://github.com/Chris--A/BitBool#licence-information)

### Installation

#### **Arduino** users
You can download this library from within the IDE using the built in *library manager*. If you need to install this on an older IDE (pre 1.6.2) and need help installing, leave a message on the Arduino forum [here](http://forum.arduino.cc/index.php?topic=128407.0) for instructions. However if you know how to install a library all you need is `BitBool.h` & `BitBool.cpp` inside a folder named `BitBool`.

#### Everyone else (General C++ usage)
Just add `BitBool.h` and `BitBool.cpp` to your project.

----

### Basic usage

##### Creating a `BitBool`

To create a `BitBool` object, you simply need to provide how many bits you need. This is done using the template syntax (A number between angle brackets`<` & `>`). You can use a count of bits as large as you like.

To read or write the bits, you use the variable just like an array.

```C++
//Create a BitBool variable named 'bits'.
BiBool<8> bits;

//Write a bit
bits[0] = true;

//Read a bit
if( bits[1] ){
  //Do something if a bit is 1, or true.
}
```

##### Turn something else into a `BitBool` ![C++11 Only!](https://img.shields.io/badge/Requires-C++11-orange.svg) / ![At least IDE 1.6.6](https://img.shields.io/badge/Minimum_Arduino_IDE-1.6.6-blue.svg)

If you have a pre-existing variable, and you need to access its bits individually, there is now a function available to make this an easy task. Using the methods described below you can either create a copy of existing data, or reference it.

- `toBitBool( object )`  
  This function accepts a single parameter which is the object you want to turn into a `BitBool`.
  Using C++11's `auto` specifier, you can easily create a copy, or reference of the data.
  ```C++
  uint64_t largeNumber = 0xAFEED0FDEADBEEF; //A large hexidecimal number.
  
  //Create a new BitBool. This is effectively a copy of the data to use as a BitBool
  auto bits = toBitBool( largeNumber );
  
  /*
    Reference the 'largeNumber' variable as a BitBool.
    Changes to 'ref' will be acutally changing 'largeNumber'.
  */
  auto &ref = toBitBool( largeNumber );
  ```

##### Reference a single bit of another object or **`BitBool`** ![C++11 Only!](https://img.shields.io/badge/Requires-C++11-orange.svg) / ![At least IDE 1.6.6](https://img.shields.io/badge/Minimum_Arduino_IDE-1.6.6-blue.svg)

If you have an object which contains a particualr bit you would like to modify easily, and it isn't a `BitBool`, you can use the method described below to access it easily. This is quite useful for repetitive tasks on the particular bit. If you already have a `BitBool` scroll down to the second example to see how you can achieve this.
- `toBitRef( object, bitIndex )`

This function does not allow creating a reference type of your own as it is already a reference to existing data. Changing the bit value is by default changing the bit you originally referenced.

```C++
char data; //An object containing a bit we would like to access.

auto bit = toBitRef( data, 0 );  //Create a bit reference to the first bit.

bit = 0; //Write to the bit.

//Read the bit.
if( bit ){
    //Bit is true or 1
}
```

**Note:** If you already have a `BitBool` and would like to reference a single bit, you can use a similar method:

```C++
BitBool<8> bits;

auto bit = bits[0];

//Use bit or bits[0] to access the first bit.
```

### Advanced features

#### Iterating a **`BitBool`** ![C++11 Only!](https://img.shields.io/badge/Requires-C++11-orange.svg)
If you have a `BitBool` object it is quite easy to traverse its contents using a `for` loop. However `BitBool` also supports C++11 ranged-loops. See the example below for C++11 style loops.

```C++
BitBool<8> bits;

//To read each bit:
for( auto bit : bits ){
    //Act on the contents of 'bit'.
}

//For read/write access, you'll need to use a reference.
for( auto &bit : bits ){
    //Act on the contents of 'bit'.
}
```

#### Selectively iterating a range of bits ![C++11 Only!](https://img.shields.io/badge/Requires-C++11-orange.svg)
Similar to simple iteration of a `BitBool` this feature allows traversing a discrete range of bits using a ranged for loop in C++11. The `BitBool` object provides a function named `iterate()` which has a few different overloads.

- `iterate()`  
This version is equivalent to the methoed described in the previous section. It is provided simply for completeness.
- `iterate( start )`  
This method takes a starting index. It will allow you to traverse the `BitBool` from a specific offset finishing at the last bit.
- `iterate( start, count )`  
This version allows selectively choosing a discrete range within a `BitBool`. The first parameter is the index to start traversing from, and the second is how many bits to traverse in total.

```C++
BitBool<8> bits;

//Traverse the last four bits.
for( auto bit : bits.iterate( 4 ) ){
    //Will iterate bits 4, 5, 6, 7
}

//Traverse the four middle bits.
for( auto bit : bits.iterate( 2, 4 ) ){
    //Will iterate bits 2, 3, 4, 5
}
```

#### Customizing how a **`BitBool`** treats the data


----

### Licence information

This product is provided under MIT licence and the only requirement I impose
is to link to the original source here on GitHub and ensure my name is clearly noted as the Author.

https://github.com/Chris--A/BitBool/

### MIT Licence:

> The MIT License (MIT)
Copyright (c) 2012-2016 Christopher Andrews  
https://github.com/Chris--A/BitBool/  
Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:  
The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.  
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.