/***
	Uncomment the #define below to use a standard bool array rather than a BitBool.
***/

//#define USE_STANDARD_BOOL
#define MAX_ITEMS 100
 
#include <BitBool.h>
 
#ifdef USE_STANDARD_BOOL
  bool b_Array[ MAX_ITEMS ] = { true, true, true };
#else
  BitBool< MAX_ITEMS > b_Array = { B00000111 };
#endif
 
void setup() { Serial.begin(9600); }
 
void loop(){
    bool b_TempCopy = b_Array[ MAX_ITEMS - 1 ];
     
    //Roll items up.
    for( int i_Index = MAX_ITEMS - 1 ; i_Index ; --i_Index )
      b_Array[ i_Index ] = b_Array[ i_Index - 1 ];
    b_Array[ 0 ] = b_TempCopy;
     
    //Show contents.
    Serial.print('[');
    for( int i_Index = 0 ; i_Index < MAX_ITEMS ; ++i_Index ) 
      Serial.print( b_Array[ i_Index ] ? '#' : '-' );
    Serial.print("]\r\n");
  }