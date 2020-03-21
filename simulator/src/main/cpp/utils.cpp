#include "utils.h"

/*HELPERS*/
int parse_int(char c)
{
    return (int)c - 48;
}

int parse_2digit_int(char* c)
{
    return (parse_int(c[0])*10) + parse_int(c[1]);
}

bool parse_bool(char c)
{
    if(((int)(c -48)) == 0)
    {
        return false;
    }
    else if(((int)(c -48)) == 1)
    {
        return true;
    }
}

char* serialize_int(int i)
{
    char* c = new char[1];
    c[0] = (char)(i + 48);
    return c;
}

char* serialize_2digit_int(int i)
{
    char* c = new char[2];
    c[1] = (char)((i % 10)+48);
    c[0] = (i<10) ? '0' : (char)((i - (i % 10))/10+48);
    return c;
}

char* serialize_int_array(int arr[], int size)
{
    char* c = new char[size];
    for(int i = 0; i < size; i++)
    {
        c[i] = (char)(arr[i] + 48);
    }
    return c;
}

char* serialize_bool(bool b)
{
    char* c = new char[1];
    c[0] = (char)((int)b + 48);
    return c;
}
