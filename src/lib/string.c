#include "common.h"
#include "string.h"

/* 注意！itoa只有一个缓冲，因此
 * char *p = itoa(100);
 * char *q = itoa(200);
 * 后p和q所指内容都是"200"。
 */
char *itoa(int a) {
	static char buf[30];
	char *p = buf + sizeof(buf);
	do {
		*--p = '0' + a % 10;
	} while (a /= 10);
	return p;
}

void memcpy(void *dest, const void *src, size_t size) {
	asm volatile ("cld; rep movsb" : : "c"(size), "S"(src), "D"(dest));
}

void memset(void *dest, int data, size_t size) {
	asm volatile ("cld; rep stosb" : : "c"(size), "a"(data), "D"(dest));
}

size_t strlen(const char *str) {
	int len = 0;
	while (*str ++) len ++;
	return len;
}

/*char *strcat(const char *str1, const char *str2) {
    //有问题  不知道如何解决
    //int l1 = strlen(str1);
    //int l2 = strlen(str2);
    //assert (l1 < 5);
    //assert (l2 < 5);
    static char buf[10];
    //char *p = buf;// + sizeof(buf);
    char *p = buf;
    int i = 0, j = 0;
    //for(i = 0; i < l1; i++)  *p++ = str1[i];
    while(((*p++ = str1[i]) != '\0') && (i < 3)) i++;
    while(((*p++ = str2[j]) != '\0') && (j < 5)){i++; j++;}
    //for(i = 0; i < l2; i++)  *p++ = str2[i];
    *p = '\0';
    return buf;//(p - (l1 * sizeof(char)) - (l2 * sizeof(char)));
}*/

