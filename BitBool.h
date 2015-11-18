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

  #include <stdint.h>
  #include <stddef.h>

    template< bool _Reverse = false >
    struct BitRef{

        // Construct a BitRef using dynamically calculated offsets (original)
        BitRef( uint8_t &dataRef, const uint8_t idx ) :
            data( dataRef ),
            index( _Reverse ? ( 0x80 >> idx ) : ( 0x1 << idx ) )
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

       void invert() const{ data ^= index; }

        uint8_t &data;
        uint8_t const index;
        static const uint8_t shift[8];
    };


template< size_t _Count, bool _Reverse = false, bool LUT = false >
    struct BitBool{
        enum{ bitCount = _Count, byteCount = ( bitCount / 0x8 ) + ( ( bitCount % 0x8 ) ? 0x1 : 0x0 ) };

        BitRef<_Reverse> operator []( const uint16_t index ) {
            if(LUT) return BitRef<_Reverse>( data[ index >> 0x3 ], index & 0x7, true );
            else    return BitRef<_Reverse>( data[ index >> 0x3 ], index & 0x7 );
        }
        uint8_t data[ byteCount ];
};
#endif