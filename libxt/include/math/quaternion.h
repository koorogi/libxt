#ifndef LIBXT_MATH_QUATERNION_H
#define LIBXT_MATH_QUATERNION_H

#include <math/fixedpoint.h>

typedef struct {
    XtFixed8 w, x, y, z;
} XtQuaternion;

typedef struct {
    XtFixed8 x, y, z;
} XtVector3;

XtQuaternion xt_quat_mult(XtQuaternion q1, XtQuaternion q2);
XtQuaternion xt_quat_conj(XtQuaternion q);

XtVector3    xt_quat_rotate_vect(XtQuaternion rotate, XtVector3 v);
XtQuaternion xt_quat_rotate_make(XtFixed8 angle, XtVector3 axis);

#endif

