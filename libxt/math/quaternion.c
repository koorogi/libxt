#include <math.h>

#include <math/quaternion.h>

XtQuaternion xt_quat_mult(XtQuaternion q1, XtQuaternion q2) {
    XtQuaternion ret;
    ret.w = xt_fixed_8x8(q1.w, q2.w) - xt_fixed_8x8(q1.x, q2.x) - xt_fixed_8x8(q1.y, q2.y) - xt_fixed_8x8(q1.z, q2.z);
    ret.x = xt_fixed_8x8(q1.w, q2.x) + xt_fixed_8x8(q1.x, q2.w) + xt_fixed_8x8(q1.y, q2.z) - xt_fixed_8x8(q1.z, q2.y);
    ret.y = xt_fixed_8x8(q1.w, q2.y) - xt_fixed_8x8(q1.x, q2.z) + xt_fixed_8x8(q1.y, q2.w) + xt_fixed_8x8(q1.z, q2.x);
    ret.z = xt_fixed_8x8(q1.w, q2.z) + xt_fixed_8x8(q1.x, q2.y) - xt_fixed_8x8(q1.y, q2.x) + xt_fixed_8x8(q1.z, q2.w);
    return ret;
}

XtQuaternion xt_quat_conj(XtQuaternion q) {
    q.x = -q.x;
    q.y = -q.y;
    q.z = -q.z;
    return q;
}

XtVector3 xt_quat_rotate_vect(XtQuaternion rotate, XtVector3 v) {
    XtQuaternion tmp;
    tmp.w = 0;
    tmp.x = v.x;
    tmp.y = v.y;
    tmp.z = v.z;

    tmp = xt_quat_mult(xt_quat_mult(rotate, tmp), xt_quat_conj(rotate));
    XtVector3 ret;
    ret.x = tmp.x;
    ret.y = tmp.y;
    ret.z = tmp.z;
    return ret;
}

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

