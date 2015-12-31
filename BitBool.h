/*
    The MIT License (MIT)

    Copyright (c) 2012-2015 Christopher Andrews
    http://arduino.land/Code/BitBool/

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
*/

#ifndef HEADER_BITBOOL
    #define HEADER_BITBOOL

    #include <stdint.h> //uintX_t types
    #include <stddef.h> //size_t

    enum REVERSE_OPTIONS{
        REVERSE_NONE,    //This will read data as big endian.
        REVERSE_BITS,    //Bit index zero references MSB, instead of LSB.
        REVERSE_BYTES,    //Byte index zero references sizeof(T) - 1.
        REVERSE_BOTH,    //This will read data as little endian.
        REVERSE_DEFAULT = REVERSE_NONE
    };

    #define REVERSE_BITS_MASK 0x01
    #define REVERSE_BYTES_MASK 0x02

    template< uint8_t reverse = REVERSE_DEFAULT >
    struct BitRef{

        // Construct a BitRef using dynamically calculated offsets (original)
        BitRef( uint8_t &dataRef, const uint8_t idx ) :
            data( dataRef ),
            index( (reverse & REVERSE_BITS_MASK) ? ( 0x80 >> idx ) : ( 0x1 << idx ) )
            { return; }

        // Construct a BitRef using a lookup table.
        BitRef( uint8_t &dataRef, const uint8_t idx, bool lookupTable ) :
            data( dataRef ),
            index( shift[idx] )
            { return; }

        //Implicit conversion to bit value.
        operator bool() const { return data & index; }

        bool operator =( const BitRef &copy ) const { return *this = ( const bool ) copy; }

        bool operator =( const bool &copy ) const {
            if( copy ) data |= index;
            else       data &= ~index;
            return copy;
        }

        //Unconditionally invert the bit.
        void invert() const{ data ^= index; }

        uint8_t &data;                  //Reference to byte being accessed.
        uint8_t const index;            //Index of bit inside 'data' to access.
        static const uint8_t shift[8]; //The lookup table if used.
    };

    struct NumType{
        constexpr explicit NumType( size_t num ) : value(num) {}
        constexpr operator size_t() { return value; }
        size_t value;
    };

    /*
        count: number of bits required in array.
        reverse: See REVERSE_OPTIONS, default is no reverse.
        lookUp: If true, a lookup table is utilized.
    */
    template< size_t count, uint8_t reverse = REVERSE_DEFAULT, bool lookUp = false>
    struct BitBool{

        //Data accessors.
        enum{ bitCount = count, byteCount = ( bitCount / 0x8 ) + ( ( bitCount % 0x8 ) ? 0x1 : 0x0 ) };

        //Ranged loop iteration structure.
        struct bIterator{
            bIterator( BitBool &o, uint16_t i ) : owner(o), idx(i) {}
            BitBool &owner;
            uint16_t idx;

            bool operator !=( const bIterator &b ){ return b.idx != idx; }
            bIterator &operator ++(){ return ++idx, *this; }
            BitRef<reverse> operator *(){ return owner[idx]; }
        };

        //Proxy for arbitrary ranges
        struct anyIterator{
            anyIterator( BitBool &o, uint16_t s, uint16_t f ) : owner(o), start(s), finish(f) {}
            bIterator begin(){ return bIterator( owner, start ); }
            bIterator end(){ return bIterator( owner, finish ); }
            BitBool &owner;
            uint16_t start;
            uint16_t finish;
        };

        //Basic iterator functionality.
        bIterator begin(){ return bIterator( *this, 0 ); }
        bIterator end(){ return bIterator( *this, count ); }

        //Arbitrary range iterator functionality.
        anyIterator iterate(){ return anyIterator(*this, 0, count); }  //Duplicate of basic iteration.
        anyIterator iterate( uint16_t start ){ return anyIterator(*this, start, count); }
        anyIterator iterate( uint16_t start, uint16_t length ){ return anyIterator(*this, start, start + length); }

        //Read / write access using subscript.
        BitRef<reverse> operator []( const uint16_t index ){
            const uint16_t offset = ( reverse & REVERSE_BYTES_MASK ) ? (byteCount - 1) - (index >> 0x3): (index >> 0x3);
            if(lookUp) return BitRef<reverse>( data[ offset ], index & 0x7, true );
            else    return BitRef<reverse>( data[ offset ], index & 0x7 );
        }

        //Read / write access using get and set method.
        bool get( uint16_t index ){ return (*this)[index]; }
        void set( uint16_t index, bool value ){ return (*this)[index] = value; }

        //Public data object (Free for users to manipulate).
        uint8_t data[ byteCount ];
    };

    #define TBITS (sizeof(T)*8)

    //Reference any object as a BitBool
    template<uint8_t reverse, bool lookUp, typename T>
    inline BitBool<TBITS, reverse, lookUp> &toBitBool( T &t ){
        union{
            T *_t;
            BitBool<TBITS, reverse, lookUp> *_u;
        } _t = {&t};
        return *_t._u;
    }

    template<uint8_t reverse, typename T>
    inline BitBool<TBITS, reverse, false> &toBitBool( T &t ){
        return toBitBool<reverse, false, T>(t);
    }

    template<typename T>
    inline BitBool<TBITS, false, false> &toBitBool( T &t ){
        return toBitBool<REVERSE_DEFAULT, false, T>(t);
    }


    //Reference a single bit inside an object.
    template<uint8_t reverse, bool lookUp, typename T>
    inline BitRef<reverse> toBitRef( T &t, uint16_t bit ){
        return toBitBool<reverse, lookUp>(t)[ bit ];
    }

    template<uint8_t reverse, typename T>
    inline BitRef<reverse> toBitRef( T &t, uint16_t bit ){
        return toBitRef<reverse, false>(t, bit);
    }

    template<typename T>
    inline BitRef<REVERSE_DEFAULT> toBitRef( T &t, uint16_t bit ){
        return toBitRef<REVERSE_DEFAULT, false>(t, bit);
    }

    #undef TBITS
    #undef REVERSE_BITS_MASK
    #undef REVERSE_BYTES_MASK
#endif