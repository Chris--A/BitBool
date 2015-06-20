/* 
    The MIT License (MIT)

    Copyright (c) 2012 Christopher Andrews
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

template< size_t _Count, bool _Reverse = false >
    class BitBool{
    protected:
        struct BitRef{

            BitRef( uint8_t &dataRef, const uint8_t idx ) : 
                data( dataRef ), 
                index( _Reverse ? ( 0x80 >> idx ) : ( 0x1 << idx ) ) 
                { return; }

            operator const bool() const { return data & index; }

            const bool operator =( const BitRef &copy ) const { return *this = ( const bool ) copy; }

            const bool operator =( const bool &copy ) const {
                if( copy ) data |= index;
                else       data &= ~index;
                return copy;
            }

            uint8_t &data;
            uint8_t const index;
        };  
    public:
        enum{ bitCount = _Count, byteCount = ( bitCount / 0x8 ) + ( ( bitCount % 0x8 ) ? 0x1 : 0x0 ) };

        BitRef operator []( const uint16_t index ) { return BitRef( data[ index >> 0x3 ], index & 0x7 ); }  
        uint8_t data[ byteCount ];
};
#endif