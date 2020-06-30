#include "maixpy.h"

void * __dso_handle = 0 ;

extern char* EXTEDED_INFO_STR;
/*
===============
     PPGv2
  K210 inside
    ver1.00
===============
*/
static char extInfoStr[] = "===============\r\n     PPGv2\r\n  K210 inside\r\n    ver1.00\r\n===============\r\n";

int main()
{
    EXTEDED_INFO_STR = &extInfoStr[0];
    maixpy_main();
    return 0;
}

