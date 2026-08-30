#include <stdio.h>
#include <stdlib.h>
typedef struct node { //双向链表
    int data;
    struct node *pre;
    struct node *next;
} node, *linklist;
linklist initlist(int data); //创建链表
void extendlinklist(linklist m, int data); //双链表延伸（增大小数点后位数）
void linklistadd(linklist m, linklist n); //实现两个链表相加
void linklistmul(linklist m, int mul); //实现大数乘小数
void linklistdiv(linklist m, int div); //实现大数除小数
void linklistprint(linklist m, int n); //打印结果
void linklistfree(linklist m); //释放空间
int main() {
    int n;
    scanf("%d", &n);
    linklist L = initlist(2);
    linklist temp = initlist(2);
    int i, k;
    for (i = 0; i < 504; i++) { //增大小数点后位数到504位（数组要开大一点，以防万一）
        extendlinklist(L, 0);
        extendlinklist(temp, 0);
    }
    for (i = 1, k = 3; i < 1658;
         i++, k += 2) { //每次循环计算单项并累加（一开始循环次数太小，所以总是过不了）
        linklistmul(temp, i); //乘
        linklistdiv(temp, k); //除
        linklistadd(L, temp); //累加
    }
    linklistprint(L, n + 1); //打印结果
    linklistfree(L); //释放空间
    linklistfree(temp); //释放空间
    return 0;
}
linklist initlist(int data) { //创建链表
    linklist head = (linklist)malloc(sizeof(node));
    head->data = data;
    head->pre = head;
    head->next = head;
    return head;
}
void extendlinklist(linklist m, int data) { //双链表延伸（增大小数点后位数）
    if (m == NULL)
        return;
    node *new = (node *)malloc(sizeof(node));
    new->data = data;
    new->next = m;
    new->pre = m->pre;
    m->pre->next = new;
    m->pre = new;
}
void linklistadd(linklist m, linklist n) { //实现两个链表相加
    node *nowm = m->pre, *nown = n->pre;

    /*法一（分两次循环，第一次只负责相加，第二次统一处理进位） 
	do{
		nowm->data += nown->data;
		if(nowm->data >= 10){
			nowm->data -= 10;
			nowm->pre->data++;
		}
		nowm = nowm->pre;
		nown = nown->pre;
	}while(nowm != m->pre);
	*/

    //法二（只有一次循环，用ret保存进位值）
    int ret = 0;
    do {
        nowm->data += nown->data + ret;
        ret = nowm->data / 10;
        nowm->data %= 10;
        nowm = nowm->pre;
        nown = nown->pre;
    } while (nowm != m->pre);
}
void linklistmul(linklist m, int mul) { //实现大数乘小数
    node *now = m->pre;

    /*法一（分两次循环，第一次只负责乘，第二次只负责进位） 
	do{
		now->data *= mul;
		now = now->pre;
	}while(now != m->pre);
	do{
		if(now->data >= 10){
			now->pre->data += now->data / 10;
			now->data %= 10;
		}
		now = now->pre;
	}while(now != m->pre);
	*/

    //法二（一次循环搞定，通过ret保存进位值）(while可以改为dowhile进一步优化)
    int ret = 0;
    while (now != m) {
        now->data = now->data * mul + ret;
        ret = now->data / 10;
        now->data %= 10;
        now = now->pre;
    }
    now->data += ret;
}
void linklistdiv(linklist m, int div) { //实现大数除小数
    node *now = m;
    int rest = 0;
    do {
        now->data += rest * 10;
        rest = now->data % div;
        now->data /= div;
        now = now->next;
    } while (now != m);
}
void linklistprint(linklist m, int n) { //打印结果
    node *now = m;
    int i;
    for (i = 0; i < n; i++) {
        printf("%d", now->data);
        if (now == m)
            printf(".");
        now = now->next;
    }
}
void linklistfree(linklist m) { //释放空间
    node *now = m->next, *then = now->next;
    if (now == then) {
        free(now);
        return;
    }
    while (now != then) {
        free(now);
        now = then;
        if (then != m)
            then = now->next;
    }
    free(now);
}
