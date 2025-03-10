#include <stdlib.h>
#include <unistd.h>
#include <stdarg.h>

void ft_putstr(char *str, int *size)
{
	if(!str)
		str = "(null)";
	while(*str)
	{
		write(1, str, 1);
		*size = *size + 1;
		str++;
	}
}

void	ft_putnbr(long long int nbr, int base, int *size)
{
	char *digits = "0123456789abcdef";

	if(nbr < 0)
	{
		*size = *size + 1;
		write(1, "-", 1);
		nbr = nbr * - 1;
	}
	if (nbr >= base)
		ft_putnbr(nbr / base, base, size);
	write(1, &digits[nbr % base], 1);
	*size = *size + 1;
}

int	ft_printf(const char *format, ...)
{
	int size = 0;
	va_list pointer;

	va_start(pointer, format);
	while(*format)
	{
		if(*format == '%' && (*(format + 1) == 's' || *(format + 1) == 'd' || *(format + 1) == 'x'))
		{
			format++;
			if (*format == 's')
				ft_putstr(va_arg(pointer, char *), & size);
			else if(*format == 'd')
				ft_putnbr((long long int)va_arg(pointer, int), 10, &size);
			else if(*format == 'x')
				ft_putnbr((long long int)va_arg(pointer, unsigned int), 16, &size);
		}
		else
		{
			write(1, format, 1);
			size++;
		}
		format++;
	}
	va_end(pointer);
	return(size);
}

#include <stdio.h>
int main()
{ 
    int return1 = ft_printf("My name is %s and I am  %d years old\n", "Clara", 23);
    int return2 = ft_printf("Testing the number %d in hexadecimals: %x\n", 42, 42);
    printf("%d\n", return1);
    printf("%d\n", return2);
    return1 = printf("My name is %s and I am  %d years old\n", "Clara", 23);
    return2 = printf("Testing the number %d in hexadecimals: %x\n", 42, 42);
    printf("%d\n", return1);
    printf("%d\n", return2);
}
