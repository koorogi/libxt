#include <math.h>

#include <math/quaternion.h>

XtQuaternion xt_quat_rotate_make(XtFixed8 angle, XtVector3 axis) {
    XtFixed8 half_angle = angle >> 1;
    XtFixed8 half_cos   = xt_fixed_cos(half_angle);
    XtFixed8 half_sin   = xt_fixed_sin(half_angle);

    XtFixed8 x = xt_fixed_8x8(axis.x, half_sin);
    XtFixed8 y = xt_fixed_8x8(axis.y, half_sin);
    XtFixed8 z = xt_fixed_8x8(axis.z, half_sin);
    XtFixed8 norm = xt_fixed_sqrt(xt_fixed_8x8(half_cos, half_cos) + xt_fixed_8x8(x, x) + xt_fixed_8x8(y, y) + xt_fixed_8x8(z, z));

    XtQuaternion ret;
    ret.w = xt_fixed_8d8(half_cos, norm);
    ret.x = xt_fixed_8d8(x, norm);
    ret.y = xt_fixed_8d8(y, norm);
    ret.z = xt_fixed_8d8(z, norm);
    return ret;
}

