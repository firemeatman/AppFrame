
#ifndef __CORE_NODE_H_
#define __CORE_NODE_H_

#ifdef __cplusplus 
extern "C" {
#endif  //__cplusplus


#include "Memory/mem.h"
#include "dataStruct/list.h"


typedef struct {
	struct list_head list; // 代表本身可作为链表节点
	const char* name;

	struct Node_Struct* childNodeList; // 子节点链表头节点
	int childNum;
	struct Node_Struct* parent; // 父节点
	//int refCount;
} Node_Struct;


Node_Struct* Node_create(Node_Struct* parent);
void Node_delete(Node_Struct* node);


// 添加子节点。新节点child必须没有父节点，如果有请调用Node_reparent()。
int Node_add_child(Node_Struct* node, Node_Struct* child);
// 将节点移出树。
int Node_moveout(Node_Struct* node);
// 更换父节点。node必须已有父节点，如果没有父节点请调用Node_add_child()。
int Node_reparent(Node_Struct* node, Node_Struct* new_parent);


int Node_count_child_num(Node_Struct* node);

Node_Struct* Node_find_child(Node_Struct* node, Node_Struct* child);

//int Node_get_node_num();


#ifdef __cplusplus
}
#endif  //__cplusplus

#endif