#include <stdio.h>
#include <stdarg.h>

void minprintf(char *fmt, ...);

int main(){
	minprintf ("My name %d\n", 10);
	minprintf ("My name %f\n", 10.1);
	minprintf ("My name %p\n", 10.1);
	minprintf ("My name %g\n", 10.1);
	minprintf ("My name %G\n", 10.1);
	return 0;
}

void minprintf(char *fmt, ...){
	va_list ap;
	char *p, *sval;
	int ival;
	double dval;
	unsigned uval;
	void *pval;

	va_start(ap, fmt);
	for (p = fmt; *p; p++) {
		if (*p != '%') {
			putchar(*p);
			continue;
		}
		switch (*++p) {
			case 'd':
			case 'i':
				ival = va_arg(ap, int);
				printf ("%d", ival);
				break;
			case 'x':
			case 'X':
				ival = va_arg(ap, int);
				printf ("%x", ival);
				break;
			case 'o':
				ival = va_arg(ap, int);
				printf ("%o", ival);
				break;
			case 'u':
				uval = va_arg(ap, unsigned);
				printf ("%u", uval);
				break;
			case 'c':
				ival = va_arg(ap, int);
				putchar(ival);
				break;
			case 'p':
				pval = va_arg(ap, void*);
				printf ("%p", pval);
				break;
			case 'f':
				dval = va_arg(ap, double);
				printf ("%f", dval);
				break;
			case 's':
				for (sval = va_arg(ap, char *); *sval; sval++)
					putchar(*sval);
				break;
			case 'e':
				dval = va_arg(ap, double);
				printf ("%e",dval);
				break;
			case 'E':
				dval = va_arg(ap, double);
				printf ("%E",dval);
				break;
			case 'g':
				dval = va_arg(ap, double);
				printf ("%g",dval);
				break;
			case 'G':
				dval = va_arg(ap, double);
				printf ("%G",dval);
				break;
			case '%':
				putchar('%');
				break;
			default:
				putchar(*p);
				break;
		}
	}
	va_end(ap);
}
