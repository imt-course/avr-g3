#include <stdio.h>
#include <stdarg.h>

void print(char* str, ...);

void print(char* str, ...) {
	va_list var_list;
	va_start(var_list, str);
	while(*str != '\0') {
		if (*str == '%') {
			str++;
			switch(*str) {
				case 'c':
					printf("%c", (char)va_arg(var_list, int));
					break;
				case 'd':
					printf("%d", (int)va_arg(var_list, int));
					break;
				case 'u':
					printf("%u", (unsigned int)va_arg(var_list, unsigned int));
					break;
				case 'l':
					printf("%ld", (long int)va_arg(var_list, long int));
					break;
				case 'f':
					printf("%f", (double)va_arg(var_list, double));
					break;
				default:
					printf("%c", *str);
					break;
			}
		}
		else {
			printf("%c", *str);
		}
		str++;
	}
}


int main (void) {
	print("Val = %d %c %u %l %f", 25, 65, -10, 94696, 25.2);
}