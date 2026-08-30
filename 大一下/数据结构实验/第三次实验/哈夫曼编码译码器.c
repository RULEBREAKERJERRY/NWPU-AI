#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct {
    int weight, parent, lchild, rchild;
} HtNode; //哈夫曼树节点
typedef struct {
    HtNode ht[210];
    int root;
} HtTree, *PHtTree; //哈夫曼树
typedef char **huffmancode; //哈夫曼编码表
char alpha[101]; //原始字母表
PHtTree huffman(int n, int *w); //构建哈夫曼树
void Select(
    PHtTree root, int pos, int *x1,
    int *x2); //选择当前哈夫曼树中权值最小两节点，并使用指针进行保存，规避了函数返回值只有一个的问题
void huffmancoding(PHtTree pht, huffmancode *HC, int n); //编码表法一：自底向上
void Traversehuffmancoding(PHtTree pht, huffmancode *HC, int i,
                           int n); //编码表法二：自顶向下深度优先搜索，注意保护现场
char *CODEIT(char *input, huffmancode HC, int n); //编码正法，不用HC查找的效率太低，不考虑
char *DECODE(char *doge, huffmancode HC, int n); //解码法一：编码表查找
char *decode(char *doge, PHtTree pht); //解码法二：哈夫曼树直接查询
void freehc(huffmancode HC, int n); //空间释放函数
int main() {
    int n;
    int w[101]; //保存权值
    scanf("%d", &n);
    int i;
    for (i = 1; i <= n; i++) {
        getchar(); //清空缓存区
        scanf("%c", alpha + i);
    }
    for (i = 1; i <= n; i++)
        scanf("%d", w + i);
    getchar(); //清空缓存区
    char input[110]; //待编码原始字符串
    scanf("%s", input);
    PHtTree pht = huffman(n, w); //哈夫曼树
    huffmancode HC; //哈夫曼编码表
    huffmancoding(pht, &HC, n); //编码表法一
    //HC = (huffmancode)malloc((n+1)*sizeof(char*));//编码表法二
    //Traversehuffmancoding(pht,&HC,pht->root,n);//编码表法二
    char *doge = CODEIT(input, HC, n); //doge为编码后字符串
    printf("%s\n", doge);
    //char* edog = DECODE(doge,HC,n);//解码法一
    char *edog = decode(doge, pht); //解码法二
    printf("%s\n", edog); //edog为解码后字符串，原则上和input相同
    free(pht); //释放哈夫曼树空间
    freehc(HC, n); //释放哈夫曼编码表空间
    free(doge);
    free(edog);
    return 0;
}
PHtTree huffman(int n, int *w) { //哈夫曼树构建
    int i, j;
    PHtTree pht = (PHtTree)malloc(sizeof(HtTree));
    for (i = 1; i <= 2 * n - 1; i++) { //初始化
        pht->ht[i].parent = 0;
        pht->ht[i].lchild = 0;
        pht->ht[i].rchild = 0;
        if (i <= n)
            pht->ht[i].weight = w[i]; //前n个节点为叶子节点，权值就是输入的权值
        else
            pht->ht[i].weight = 0; //后n-1个节点是非叶子节点，是接下来操作的重点，但初始权值为0
    }
    int min1, min2;
    for (i = 1; i < n; i++) {
        Select(pht, n + i, &min1, &min2); //选取当前权值最小的两个节点，合并成一棵树
        pht->ht[min1].parent = n + i;
        pht->ht[min2].parent = n + i;
        pht->ht[n + i].weight = pht->ht[min1].weight + pht->ht[min2].weight;
        pht->ht[n + i].lchild = min1;
        pht->ht[n + i].rchild = min2;
        pht->root = n + i;
    }
    return pht;
}
void Select(PHtTree root, int pos, int *x1, int *x2) {
    int i;
    int m1 = 1e9, m2 = 1e9;
    for (i = 1; i < pos; i++) {
        if (root->ht[i].parent)
            continue;
        if (root->ht[i].weight <
            m1) { //如果比m1小，则是目前最小，那么m1的值当下就是第二小，所以要赋给m2
            m2 = m1;
            *x2 = *x1;
            m1 = root->ht[i].weight;
            *x1 = i;
        } else if (root->ht[i].weight < m2) { //如果比m1大，但是比m2小，那么更新m2
            m2 = root->ht[i].weight;
            *x2 = i;
        }
    }
}
//编码表法一
void huffmancoding(PHtTree pht, huffmancode *HC, int n) {
    *HC = (huffmancode)malloc((n + 1) * sizeof(char *)); //申请空间
    char *cd = (char *)malloc(n * sizeof(char)); //临时字符数组
    cd[n - 1] = '\0'; //终止符不能丢，否则各种字符串操作函数无法正常工作
    int start;
    int i;
    int now, father;
    for (i = 1; i <= n; i++) {
        start = n - 1; //由于是从叶子到根，所以需要逆序存储
        now = i;
        father = pht->ht[now].parent;
        while (father) {
            if (pht->ht[father].lchild == now)
                cd[--start] = '0'; //左子节点则编码为0
            else
                cd[--start] = '1'; //右子节点则编码为1
            now = father;
            father = pht->ht[father].parent; //向根节点靠拢
        }
        (*HC)[i] = (char *)malloc((n - start + 1) * sizeof(char)); //strcpy需要包含终止符
        (*HC)[i] = strcpy((*HC)[i], cd + start); //调整首地址，方便后续编码译码操作
    }
    free(cd);
}
//编码表法二
void Traversehuffmancoding(PHtTree pht, huffmancode *HC, int i, int n) {
    static int codelen = 0; //深度搜索典型的保存现场
    static char cd[110]; //与上同理
    if (pht == NULL)
        return;
    if (pht->ht[i].rchild == 0) { //也可以改为pht->ht[n].lchild == 0
        cd[codelen] = '\0'; //已经到了叶子节点，此时cd数组中即为编码
        (*HC)[i] = (char *)malloc((n + 1) * sizeof(char));
        strcpy((*HC)[i], cd); //与编码表法一同理
    } else {
        cd[codelen++] = '0';
        Traversehuffmancoding(pht, HC, pht->ht[i].lchild, n); //先向左子树递归
        codelen--; //恢复现场
        cd[codelen++] = '1';
        Traversehuffmancoding(pht, HC, pht->ht[i].rchild, n); //再向右子树递归
        codelen--; //恢复现场
    }
}
char *CODEIT(char *input, huffmancode HC, int n) { //编码器
    char *t = (char *)malloc(110 * sizeof(char)); //存储编码结果
    int i, j;
    char *pos = t;
    int len_input = strlen(input);
    for (i = 0; i < len_input; i++) {
        for (j = 1; j <= n; j++) { //查字母表，找对应关系
            if (alpha[j] == input[i])
                break;
        }
        strcpy(pos, HC[j]); //找到编码表中对应编码填入存储数组中
        pos += strlen(HC[j]); //更新下一次接入位置
    }
    return t;
}
char *DECODE(char *doge, huffmancode HC, int n) { //解码法一：查表法解码
    char *t = (char *)malloc(110 * sizeof(char)); //保存解码字符串
    char *buffer = (char *)malloc(110 * sizeof(char)); //模拟缓冲区字符串，用于动态比较
    int len_doge = strlen(doge);
    char *pos = buffer; //每一步都要小心
    int i, j, len_t = 0, len_buffer = 0;
    for (i = 0; i < len_doge; i++) {
        buffer[len_buffer++] = doge[i]; //每加入一个字符比较一次
        buffer[len_buffer] = '\0'; //注意添加终止符，这样子字符串比较函数才能正常工作
        for (j = 1; j <= n; j++) {
            if (strcmp(pos, HC[j]) == 0) { //如果匹配成功，则将对应字母填入
                t[len_t++] = alpha[j];
                len_buffer = 0; //重置缓冲字符串
                buffer[0] = '\0'; //重置缓冲字符串
                break;
            }
        }
    }
    t[len_t++] = '\0'; //别忘了字符串终止符
    free(buffer); //及时释放使用的空间
    return t;
}
char *decode(char *doge, PHtTree pht) { //解码法二：哈夫曼树直接查询
    char *t = (char *)malloc(110 * sizeof(char)); //保存解码字符串
    int len_doge = strlen(doge);
    int i, j, len_t = 0;
    int root = pht->root, now;
    for (i = 0; i < len_doge; i++) { //自顶向下
        if (doge[i] == '0') { //0，则往左子树走
            now = pht->ht[root].lchild;
            if (!pht->ht[now].lchild) { //没有左子树（扩充二叉树性质），则说明已经到达叶子节点
                t[len_t++] = alpha[now];
                root = pht->root;
                continue;
            }
            root = now;
        } else if (doge[i] == '1') { //1，则往右子树走
            now = pht->ht[root].rchild;
            if (!pht->ht[now].rchild) { //没有右子树，则已经抵达叶子节点
                t[len_t++] = alpha[now];
                root = pht->root;
                continue;
            }
            root = now;
        }
    }
    t[len_t++] = '\0';
    return t;
}
void freehc(huffmancode HC, int n) { //释放编码表空间
    int i;
    for (i = 1; i <= n; i++)
        free(HC[i]);
    free(HC);
}
