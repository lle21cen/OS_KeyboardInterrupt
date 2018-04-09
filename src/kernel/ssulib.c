#include <ssulib.h>
#include <device/io.h>
#include <syscall.h>

// void memcpy(void* from, void* to, uint32_t len)
// {
// 	uint32_t *p1 = (uint32_t*)from;
// 	uint32_t *p2 = (uint32_t*)to;
// 	int i, e;

// 	e = len/sizeof(uint32_t);
// 	for(i = 0; i<e; i++)
// 		p2[i] = p1[i];

// 	e = len%sizeof(uint32_t);
// 	if( e != 0)
// 	{
// 		uint8_t *p3 = (uint8_t*)p1;
// 		uint8_t *p4 = (uint8_t*)p2;

// 		for(i = 0; i<e; i++)
// 			p4[i] = p3[i];
// 	}
// }

int strncmp(char* b1, char* b2, int len)
{
	int i;

	for(i = 0; i < len; i++)
	{
		char c = b1[i] - b2[i];
		if(c)
			return c;
		if(b1[i] == 0)
			return 0;
	}
	return 0;
}

char getchar()
{
	return ssuread();
}

int getToken(char* buf, int len)
{
	char* stopper = " \t\n";
	int off = 0;
	while(1)
	{
		char c = -1;
		char *p;
		while(c == -1)
		{
			c = ssuread();
		}

		p = stopper;
		while(*p != 0)
		{
			if(*p == c)
			{
				buf[off++] = 0;
				return off;
			}
			p++;
		}

		if (c == 0x08 && off == 0)
			continue;

		else if (c == -128 || c == -127) 
			continue;
		
		printk("%c", c);

		buf[off++] = c;

		if (c==0x08) {
			off-=2;
			buf[off] = 0;
		}

		if(off >= len)
		{
			return off;
		}
	}
}
