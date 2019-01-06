#ifndef MYMATHS_H
#define MYMATHS_H

double myfmod(double x, double y)
{
    return y*( (x/y) - (size_t)(x/y) );
}


double mysine(double x)
{
    x = myfmod(x, 2 * M_PI);
    return 0.08179420144 * (x - M_PI) * (x - 2*M_PI) * x; //didn't seem to be giving values of sine in range of -1 to 1 messing up asin function
}


#endif
