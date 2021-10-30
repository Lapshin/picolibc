
/* @(#)e_tgamma.c 5.1 93/09/24 */
/*
 * ====================================================
 * Copyright (C) 1993 by Sun Microsystems, Inc. All rights reserved.
 *
 * Developed at SunPro, a Sun Microsystems, Inc. business.
 * Permission to use, copy, modify, and distribute this
 * software is freely granted, provided that this notice 
 * is preserved.
 * ====================================================
 *
 */

/* tgamma(x)
 * Gamma function. Returns gamma(x)
 *
 * Method: See lgamma_r
 */

#include "fdlibm.h"

double
tgamma(double x)
{
    int signgam_local = 1;
    double y = exp(lgamma_r(x, &signgam_local));
    if (signgam_local < 0)
        y = -y;
    return y;
}
