//#include <kernel.h>

extern "C" void main()
{
//    char* VID_MEM = (char*) 0xB8000;
//    VID_MEM = 'Q';
    *(char*)0xb8000 = 'Q';
    return;
}
