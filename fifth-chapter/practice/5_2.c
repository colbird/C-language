#include <stdio.h>

int getfloat(float *);

int main(){
	float f;
	int type;
	while ((type = getfloat(&f)) != EOF){
		if (type)
			printf("%g\n", f);
	}
	return 0;
}



#include <ctype.h>

int getch(void);
void ungetch(int);
void del(void);

int getfloat(float *fp){
	int c, t, sign, power;
	while (isspace(c = getch()))		//跳过空白
		;
	if (!isdigit(c) && c != '-' && c != '+' && c != '.')
		return 0;

	sign = (c == '-') ? -1 : 1;

	if (c == '-' || c == '+'){
		if (!isdigit(t = getch())){
			if (t == '\n'){
				del();
				return 0;
			}
			ungetch(c);
			return 0;
		}
		else
			c = t;
	}
	for (*fp = 0.0; isdigit(c); c = getch()){
		*fp = *fp * 10 + c - '0';
	}
	power = 1;
	if (c == '.'){
		while(isdigit(c = getch())){
			*fp = *fp * 10 + c - '0';
			power *= 10;
		}
	}
	*fp = *fp * (float)sign / (float)power;
	if (c != EOF)
		ungetch(c);
	return c;
}


#define MAXBUF 10

int buf[MAXBUF];
int bufp = 0;

int getch(){
	return (bufp >0) ? buf[--bufp] : getchar();
}
void ungetch(int s){
	buf[bufp++] = s;
}
void del(void){
	bufp = 0;
}
