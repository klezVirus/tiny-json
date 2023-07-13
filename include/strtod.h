//
// Created by d3adc0de on 13/07/2023.
//

#ifndef TINY_JSON_STRTOD_H
#define TINY_JSON_STRTOD_H

#include "defs.h"

double atof(char *arr)
{
    float val = 0;
    int afterdot=0;
    float scale=1;
    int neg = 0;

    if (*arr == '-') {
        arr++;
        neg = 1;
    }
    while (*arr) {
        if (afterdot) {
            scale = scale/10;
            val = val + (*arr-'0')*scale;
        } else {
            if (*arr == '.')
                afterdot++;
            else
                val = val * 10.0 + (*arr - '0');
        }
        arr++;
    }
    if(neg){
        return (double)-val;
    }
    else{
        return (double)val;
    }
}


/* Disclaimer: this is currently just used by CHILL in GDB and therefore
   has not been tested well.  It may have been tested for nothing except
   that it compiles.  */

double
strtod (const char *str, char **ptr)
{
    char *p;

    if (ptr == (char **)0)
        return atof ((char *)str);

    p = (char *)str;

    while (ISSPACE (*p))
        ++p;

    if (*p == '+' || *p == '-')
        ++p;

    /* INF or INFINITY.  */
    if ((p[0] == 'i' || p[0] == 'I')
        && (p[1] == 'n' || p[1] == 'N')
        && (p[2] == 'f' || p[2] == 'F'))
    {
        if ((p[3] == 'i' || p[3] == 'I')
            && (p[4] == 'n' || p[4] == 'N')
            && (p[5] == 'i' || p[5] == 'I')
            && (p[6] == 't' || p[6] == 'T')
            && (p[7] == 'y' || p[7] == 'Y'))
        {
            *ptr = p + 8;
            return atof ((char *)str);
        }
        else
        {
            *ptr = p + 3;
            return atof ((char *)str);
        }
    }

    /* NAN or NAN(foo).  */
    if ((p[0] == 'n' || p[0] == 'N')
        && (p[1] == 'a' || p[1] == 'A')
        && (p[2] == 'n' || p[2] == 'N'))
    {
        p += 3;
        if (*p == '(')
        {
            ++p;
            while (*p != '\0' && *p != ')')
                ++p;
            if (*p == ')')
                ++p;
        }
        *ptr = p;
        return atof ((char *)str);
    }

    /* digits, with 0 or 1 periods in it.  */
    if (ISDIGIT (*p) || *p == '.')
    {
        int got_dot = 0;
        while (ISDIGIT (*p) || (!got_dot && *p == '.'))
        {
            if (*p == '.')
                got_dot = 1;
            ++p;
        }

        /* Exponent.  */
        if (*p == 'e' || *p == 'E')
        {
            int i;
            i = 1;
            if (p[i] == '+' || p[i] == '-')
                ++i;
            if (ISDIGIT (p[i]))
            {
                while (ISDIGIT (p[i]))
                    ++i;
                *ptr = p + i;
                return atof ((char *)str);
            }
        }
        *ptr = p;
        return atof ((char *)str);
    }
    /* Didn't find any digits.  Doesn't look like a number.  */
    *ptr = (char *)str;
    return 0.0;
}

#endif //TINY_JSON_STRTOD_H
