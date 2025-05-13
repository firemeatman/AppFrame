
#ifndef __APPFRAME_MEM_H_
#define __APPFRAME_MEM_H_

//
//该文件mem.h有框架的内存分配函数的设置，以及相关的宏
// 


#ifdef __cplusplus 
extern "C" {
#endif  //__cplusplus

#include <stdlib.h>
#include <stddef.h>



#define APP_MALLOC(byte_num) malloc(byte_num)
#define APP_FREE(ptr) free(ptr)
#define APP_NULL NULL

#define APP_SAFE_FREE(ptr) do{\
	if(ptr){\
		APP_FREE(ptr);\
		ptr = APP_NULL;\
	}\
}while(0);


#ifdef __cplusplus
}
#endif  //__cplusplus

#endif