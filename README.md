# `BitBool` library for C++ ![Version 1.2.0](https://img.shields.io/badge/Version-1.2.0-blue.svg)
#### *The ultimate bit manipulation tool*
![C++98](https://img.shields.io/badge/C%2B%2B-98-yellow.svg) ![C++11](https://img.shields.io/badge/C%2B%2B-11-orange.svg)  

**Written by:** *Christopher Andrews.*  
**Licence:** *MIT*

This class provides an efficient and easy to use method of dealing with bits. The library is infact a drop-in replacement for a `bool` array. However it has many more uses and is perfect for use on embedded systems where performance and efficiency matters.

### Contents
- Installation.
  - Arduino Users.
  - General C++ usage.
- Basic Usage
  - Creating a **`BitBool`**.
  - Turn something else into a **`BitBool`**.
  - Reference a single bit inside another object, or **`BitBool`**.
- Advanced features.
   - Iterating a **`BitBool`**.
  - Selectively iterating a range of bits.
  - Customizing how a **`BitBool`** treats the data.

### Installation

#### **Arduino** users
You can download this library from within the IDE using the built in *library manager*. If you need to install this on an older IDE (pre 1.6.2) and need help installing, leave a message on the Arduino forum [here](http://forum.arduino.cc/index.php?topic=128407.0) for instructions. However if you know how to install a library all you need is `BitBool.h` & `BitBool.cpp` inside a folder named `BitBool`.

#### Everyone else (General C++ usage).
Just add `BitBool.h` and `BitBool.cpp` to your project.

----

### Basic usage

##### 1. Creating a `BitBool`.

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

##### 2. Turn something else into a `BitBool` ![C++11 Only!](https://img.shields.io/badge/Requires-C++11-orange.svg) / ![At least IDE 1.6.6](https://img.shields.io/badge/Minimum_Arduino_IDE-1.6.6-blue.svg)

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

##### 3. Reference a single bit of another object. ![C++11 Only!](https://img.shields.io/badge/Requires-C++11-orange.svg) / ![At least IDE 1.6.6](https://img.shields.io/badge/Minimum_Arduino_IDE-1.6.6-blue.svg)
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

### Advanced usage.

#### Iterating a **`BitBool`**.

#### Selectively iterating a range of bits.

#### Customizing how a **`BitBool`** treats the data.


----
This product is provided under MIT licence and the only requirement I impose
is to link to the original source here on GitHub and ensure my name is clearly noted as the Author.

https://github.com/Chris--A/BitBool/
