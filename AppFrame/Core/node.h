
#ifndef __CORE_NODE_H_
#define __CORE_NODE_H_

#ifdef __cplusplus 
extern "C" {
#endif  //__cplusplus


#include "Memory/mem.h"
#include "dataStruct/list.h"


typedef struct {
	const char* name;

	struct list_head childListHead;
	int childNum;
	struct Node_Struct* parent;
	//int refCount;
} Node_Struct;


Node_Struct* Node_create(Node_Struct* parent);
int Node_delete(Node_Struct* node);

// 添加子节点。新节点child必须没有父节点，如果有请调用Node_reparent()。
int Node_add_child(Node_Struct* node, Node_Struct* child);
// 删除子节点。不会释放Node的内存。
int Node_remove_child(Node_Struct* node, Node_Struct* child);
// 更换父节点。node必须已有父节点，如果没有父节点请调用Node_add_child()。
int Node_reparent(Node_Struct* node, Node_Struct* new_parent);

int Node_get_node_num();


#ifdef __cplusplus
}
#endif  //__cplusplus

#endif