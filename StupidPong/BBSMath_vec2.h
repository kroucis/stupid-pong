//
//  BBSVec2.h
//  BBSit
//
//  Copyright (c) 2011, Apple Inc. All rights reserved.
//

#ifndef __BBS_VECTOR_2_H
#define __BBS_VECTOR_2_H

#if defined(__ARM_NEON__)
#include <arm_neon.h>
#endif

#include "BBSMath_types.h"

#ifdef __cplusplus
extern "C" {
#endif
    
#pragma mark -
#pragma mark Prototypes
#pragma mark -

MATH_EXPORT MATH_STATIC_INLINE BBSVec2 BBSVec2Make(float x, float y);
MATH_EXPORT MATH_STATIC_INLINE BBSVec2 BBSVec2MakeWithArray(float values[2]);
	
MATH_EXPORT MATH_STATIC_INLINE BBSPoint2 BBSPoint2Make(float x, float y);
MATH_EXPORT MATH_STATIC_INLINE BBSTex2 BBSTex2Make(float u, float v);
MATH_EXPORT MATH_STATIC_INLINE BBSSize2 BBSSize2Make(float w, float h);

MATH_EXPORT MATH_STATIC_INLINE BBSVec2 BBSVec2Negate(BBSVec2 vector);

MATH_EXPORT MATH_STATIC_INLINE BBSVec2 BBSVec2Add(BBSVec2 vectorLeft, BBSVec2 vectorRight);
MATH_EXPORT MATH_STATIC_INLINE BBSVec2 BBSVec2Subtract(BBSVec2 vectorLeft, BBSVec2 vectorRight);
MATH_EXPORT MATH_STATIC_INLINE BBSVec2 BBSVec2Multiply(BBSVec2 vectorLeft, BBSVec2 vectorRight);
MATH_EXPORT MATH_STATIC_INLINE BBSVec2 BBSVec2Divide(BBSVec2 vectorLeft, BBSVec2 vectorRight);
        
MATH_EXPORT MATH_STATIC_INLINE BBSVec2 BBSVec2AddScalar(BBSVec2 vector, float value);
MATH_EXPORT MATH_STATIC_INLINE BBSVec2 BBSVec2SubtractScalar(BBSVec2 vector, float value);
MATH_EXPORT MATH_STATIC_INLINE BBSVec2 BBSVec2MultiplyScalar(BBSVec2 vector, float value);
MATH_EXPORT MATH_STATIC_INLINE BBSVec2 BBSVec2DivideScalar(BBSVec2 vector, float value);
        
/*
 Returns a vector whose elements are the larger of the corresponding elements of the vector arguments.
 */
MATH_EXPORT MATH_STATIC_INLINE BBSVec2 BBSVec2Maximum(BBSVec2 vectorLeft, BBSVec2 vectorRight);
/*
 Returns a vector whose elements are the smaller of the corresponding elements of the vector arguments.
 */
MATH_EXPORT MATH_STATIC_INLINE BBSVec2 BBSVec2Minimum(BBSVec2 vectorLeft, BBSVec2 vectorRight);
    
/*
 Returns true if all of the first vector's elements are equal to all of the second vector's arguments.
 */
MATH_EXPORT MATH_STATIC_INLINE bool BBSVec2AllEqualToVector2(BBSVec2 vectorLeft, BBSVec2 vectorRight);
/*
 Returns true if all of the vector's elements are equal to the provided value.
 */
MATH_EXPORT MATH_STATIC_INLINE bool BBSVec2AllEqualToScalar(BBSVec2 vector, float value);
/*
 Returns true if all of the first vector's elements are greater than all of the second vector's arguments.
 */
MATH_EXPORT MATH_STATIC_INLINE bool BBSVec2AllGreaterThanVector2(BBSVec2 vectorLeft, BBSVec2 vectorRight);
/*
 Returns true if all of the vector's elements are greater than the provided value.
 */
MATH_EXPORT MATH_STATIC_INLINE bool BBSVec2AllGreaterThanScalar(BBSVec2 vector, float value);
/*
 Returns true if all of the first vector's elements are greater than or equal to all of the second vector's arguments.
 */
MATH_EXPORT MATH_STATIC_INLINE bool BBSVec2AllGreaterThanOrEqualToVector2(BBSVec2 vectorLeft, BBSVec2 vectorRight);
/*
 Returns true if all of the vector's elements are greater than or equal to the provided value.
 */
MATH_EXPORT MATH_STATIC_INLINE bool BBSVec2AllGreaterThanOrEqualToScalar(BBSVec2 vector, float value);
    
MATH_EXPORT MATH_STATIC_INLINE BBSVec2 BBSVec2Normalize(BBSVec2 vector);

MATH_EXPORT MATH_STATIC_INLINE float BBSVec2DotProduct(BBSVec2 vectorLeft, BBSVec2 vectorRight);
MATH_EXPORT MATH_STATIC_INLINE float BBSVec2Magnitude(BBSVec2 vector);
MATH_EXPORT MATH_STATIC_INLINE float BBSVec2Distance(BBSVec2 vectorStart, BBSVec2 vectorEnd);

MATH_EXPORT MATH_STATIC_INLINE BBSVec2 BBSVec2Lerp(BBSVec2 vectorStart, BBSVec2 vectorEnd, float t);

/*
 Project the vector, vectorToProject, onto the vector, projectionVector.
 */
MATH_EXPORT MATH_STATIC_INLINE BBSVec2 BBSVec2Project(BBSVec2 vectorToProject, BBSVec2 projectionVector);

#pragma mark -
#pragma mark Implementations
#pragma mark -
    
MATH_EXPORT MATH_STATIC_INLINE BBSVec2 BBSVec2Make(float x, float y)
{
    BBSVec2 v = { x, y };
    return v;
}
	
MATH_EXPORT MATH_STATIC_INLINE BBSPoint2 BBSPoint2Make(float x, float y)
{
	return BBSVec2Make(x, y);
}
	
MATH_EXPORT MATH_STATIC_INLINE BBSTex2 BBSTex2Make(float u, float v)
{
	return BBSVec2Make(u, v);
}
	
MATH_EXPORT MATH_STATIC_INLINE BBSSize2 BBSSize2Make(float w, float h)
{
	return BBSVec2Make(w, h);
}
    
MATH_EXPORT MATH_STATIC_INLINE BBSVec2 BBSVec2MakeWithArray(float values[2])
{
#if defined(__ARM_NEON__)
    float32x2_t v = vld1_f32(values);
    return *(BBSVec2 *)&v;
#else
    BBSVec2 v = { values[0], values[1] };
    return v;
#endif
}
    
MATH_EXPORT MATH_STATIC_INLINE BBSVec2 BBSVec2Negate(BBSVec2 vector)
{
#if defined(__ARM_NEON__)
    float32x2_t v = vneg_f32(*(float32x2_t *)&vector);
    return *(BBSVec2 *)&v;
#else
    BBSVec2 v = { -vector.v[0] , -vector.v[1] };
    return v;
#endif
}
 
MATH_EXPORT MATH_STATIC_INLINE BBSVec2 BBSVec2Add(BBSVec2 vectorLeft, BBSVec2 vectorRight)
{
#if defined(__ARM_NEON__)
    float32x2_t v = vadd_f32(*(float32x2_t *)&vectorLeft,
                             *(float32x2_t *)&vectorRight);
    return *(BBSVec2 *)&v;
#else
    BBSVec2 v = { vectorLeft.v[0] + vectorRight.v[0],
                     vectorLeft.v[1] + vectorRight.v[1] };
    return v;
#endif
}
  
MATH_EXPORT MATH_STATIC_INLINE BBSVec2 BBSVec2Subtract(BBSVec2 vectorLeft, BBSVec2 vectorRight)
{
#if defined(__ARM_NEON__)
    float32x2_t v = vsub_f32(*(float32x2_t *)&vectorLeft,
                             *(float32x2_t *)&vectorRight);
    return *(BBSVec2 *)&v;
#else
    BBSVec2 v = { vectorLeft.v[0] - vectorRight.v[0],
                     vectorLeft.v[1] - vectorRight.v[1] };
    return v;
#endif
}
    
MATH_EXPORT MATH_STATIC_INLINE BBSVec2 BBSVec2Multiply(BBSVec2 vectorLeft, BBSVec2 vectorRight)
{
#if defined(__ARM_NEON__)
    float32x2_t v = vmul_f32(*(float32x2_t *)&vectorLeft,
                             *(float32x2_t *)&vectorRight);
    return *(BBSVec2 *)&v;
#else
    BBSVec2 v = { vectorLeft.v[0] * vectorRight.v[0],
                     vectorLeft.v[1] * vectorRight.v[1] };
    return v;
#endif
}
    
MATH_EXPORT MATH_STATIC_INLINE BBSVec2 BBSVec2Divide(BBSVec2 vectorLeft, BBSVec2 vectorRight)
{
#if defined(__ARM_NEON__)
    float32x2_t *vLeft = (float32x2_t *)&vectorLeft;
    float32x2_t *vRight = (float32x2_t *)&vectorRight;
    float32x2_t estimate = vrecpe_f32(*vRight);    
    estimate = vmul_f32(vrecps_f32(*vRight, estimate), estimate);
    estimate = vmul_f32(vrecps_f32(*vRight, estimate), estimate);
    float32x2_t v = vmul_f32(*vLeft, estimate);
    return *(BBSVec2 *)&v;
#else
    BBSVec2 v = { vectorLeft.v[0] / vectorRight.v[0],
                     vectorLeft.v[1] / vectorRight.v[1] };
    return v;
#endif
}

MATH_EXPORT MATH_STATIC_INLINE BBSVec2 BBSVec2AddScalar(BBSVec2 vector, float value)
{
#if defined(__ARM_NEON__)
    float32x2_t v = vadd_f32(*(float32x2_t *)&vector,
                             vdup_n_f32((float32_t)value));
    return *(BBSVec2 *)&v;
#else
    BBSVec2 v = { vector.v[0] + value,
                     vector.v[1] + value };
    return v;
#endif
}
    
MATH_EXPORT MATH_STATIC_INLINE BBSVec2 BBSVec2SubtractScalar(BBSVec2 vector, float value)
{
#if defined(__ARM_NEON__)
    float32x2_t v = vsub_f32(*(float32x2_t *)&vector,
                             vdup_n_f32((float32_t)value));
    return *(BBSVec2 *)&v;
#else    
    BBSVec2 v = { vector.v[0] - value,
                     vector.v[1] - value };
    return v;
#endif
}
    
MATH_EXPORT MATH_STATIC_INLINE BBSVec2 BBSVec2MultiplyScalar(BBSVec2 vector, float value)
{
#if defined(__ARM_NEON__)
    float32x2_t v = vmul_f32(*(float32x2_t *)&vector,
                             vdup_n_f32((float32_t)value));
    return *(BBSVec2 *)&v;
#else
    BBSVec2 v = { vector.v[0] * value,
                     vector.v[1] * value };
    return v;
#endif
}
    
MATH_EXPORT MATH_STATIC_INLINE BBSVec2 BBSVec2DivideScalar(BBSVec2 vector, float value)
{
#if defined(__ARM_NEON__)
    float32x2_t values = vdup_n_f32((float32_t)value);
    float32x2_t estimate = vrecpe_f32(values);    
    estimate = vmul_f32(vrecps_f32(values, estimate), estimate);
    estimate = vmul_f32(vrecps_f32(values, estimate), estimate);
    float32x2_t v = vmul_f32(*(float32x2_t *)&vector, estimate);
    return *(BBSVec2 *)&v;
#else
    BBSVec2 v = { vector.v[0] / value,
                     vector.v[1] / value };
    return v;
#endif
}
    
MATH_EXPORT MATH_STATIC_INLINE BBSVec2 BBSVec2Maximum(BBSVec2 vectorLeft, BBSVec2 vectorRight)
{
#if defined(__ARM_NEON__)
    float32x2_t v = vmax_f32(*(float32x2_t *)&vectorLeft,
                             *(float32x2_t *)&vectorRight);
    return *(BBSVec2 *)&v;
#else
    BBSVec2 max = vectorLeft;
    if (vectorRight.v[0] > vectorLeft.v[0])
        max.v[0] = vectorRight.v[0];
    if (vectorRight.v[1] > vectorLeft.v[1])
        max.v[1] = vectorRight.v[1];
    return max;
#endif
}

MATH_EXPORT MATH_STATIC_INLINE BBSVec2 BBSVec2Minimum(BBSVec2 vectorLeft, BBSVec2 vectorRight)
{
#if defined(__ARM_NEON__)
    float32x2_t v = vmin_f32(*(float32x2_t *)&vectorLeft,
                             *(float32x2_t *)&vectorRight);
    return *(BBSVec2 *)&v;
#else
    BBSVec2 min = vectorLeft;
    if (vectorRight.v[0] < vectorLeft.v[0])
        min.v[0] = vectorRight.v[0];
    if (vectorRight.v[1] < vectorLeft.v[1])
        min.v[1] = vectorRight.v[1];
    return min;
#endif
}
   
MATH_EXPORT MATH_STATIC_INLINE bool BBSVec2AllEqualToVector2(BBSVec2 vectorLeft, BBSVec2 vectorRight)
{
#if defined(__ARM_NEON_)
    float32x2_t v1 = *(float32x2_t *)&vectorLeft;
    float32x2_t v2 = *(float32x2_t *)&vectorRight;
    uint32x2_t vCmp = vceq_f32(v1, v2);
    uint32x2_t vAnd = vand_u32(vCmp, vext_u32(vCmp, vCmp, 1));
    vAnd = vand_u32(vAnd, vdup_n_u32(1));
    return (bool)vget_lane_u32(vAnd, 0);
#else
    bool compare = false;
    if (vectorLeft.v[0] == vectorRight.v[0] &&
        vectorLeft.v[1] == vectorRight.v[1])
        compare = true;
    return compare;
#endif
}

MATH_EXPORT MATH_STATIC_INLINE bool BBSVec2AllEqualToScalar(BBSVec2 vector, float value)
{
#if defined(__ARM_NEON_)
    float32x2_t v1 = *(float32x2_t *)&vector;
    float32x2_t v2 = vdup_n_f32(value);
    uint32x2_t vCmp = vceq_f32(v1, v2);
    uint32x2_t vAnd = vand_u32(vCmp, vext_u32(vCmp, vCmp, 1));
    vAnd = vand_u32(vAnd, vdup_n_u32(1));
    return (bool)vget_lane_u32(vAnd, 0);
#else
    bool compare = false;
    if (vector.v[0] == value &&
        vector.v[1] == value)
        compare = true;
    return compare;
#endif
}

MATH_EXPORT MATH_STATIC_INLINE bool BBSVec2AllGreaterThanVector2(BBSVec2 vectorLeft, BBSVec2 vectorRight)
{
#if defined(__ARM_NEON_)
    float32x2_t v1 = *(float32x2_t *)&vectorLeft;
    float32x2_t v2 = *(float32x2_t *)&vectorRight;
    uint32x2_t vCmp = vcgt_f32(v1, v2);
    uint32x2_t vAnd = vand_u32(vCmp, vext_u32(vCmp, vCmp, 1));
    vAnd = vand_u32(vAnd, vdup_n_u32(1));
    return (bool)vget_lane_u32(vAnd, 0);
#else
    bool compare = false;
    if (vectorLeft.v[0] > vectorRight.v[0] &&
        vectorLeft.v[1] > vectorRight.v[1])
        compare = true;
    return compare;
#endif
}

MATH_EXPORT MATH_STATIC_INLINE bool BBSVec2AllGreaterThanScalar(BBSVec2 vector, float value)
{
#if defined(__ARM_NEON_)
    float32x2_t v1 = *(float32x2_t *)&vector;
    float32x2_t v2 = vdup_n_f32(value);
    uint32x2_t vCmp = vcgt_f32(v1, v2);
    uint32x2_t vAnd = vand_u32(vCmp, vext_u32(vCmp, vCmp, 1));
    vAnd = vand_u32(vAnd, vdup_n_u32(1));
    return (bool)vget_lane_u32(vAnd, 0);
#else
    bool compare = false;
    if (vector.v[0] > value &&
        vector.v[1] > value)
        compare = true;
    return compare;
#endif
}

MATH_EXPORT MATH_STATIC_INLINE bool BBSVec2AllGreaterThanOrEqualToVector2(BBSVec2 vectorLeft, BBSVec2 vectorRight)
{
#if defined(__ARM_NEON_)
    float32x2_t v1 = *(float32x2_t *)&vectorLeft;
    float32x2_t v2 = *(float32x2_t *)&vectorRight;
    uint32x2_t vCmp = vcge_f32(v1, v2);
    uint32x2_t vAnd = vand_u32(vCmp, vext_u32(vCmp, vCmp, 1));
    vAnd = vand_u32(vAnd, vdup_n_u32(1));
    return (bool)vget_lane_u32(vAnd, 0);
#else
    bool compare = false;
    if (vectorLeft.v[0] >= vectorRight.v[0] &&
        vectorLeft.v[1] >= vectorRight.v[1])
        compare = true;
    return compare;
#endif
}

MATH_EXPORT MATH_STATIC_INLINE bool BBSVec2AllGreaterThanOrEqualToScalar(BBSVec2 vector, float value)
{
#if defined(__ARM_NEON_)
    float32x2_t v1 = *(float32x2_t *)&vector;
    float32x2_t v2 = vdup_n_f32(value);
    uint32x2_t vCmp = vcge_f32(v1, v2);
    uint32x2_t vAnd = vand_u32(vCmp, vext_u32(vCmp, vCmp, 1));
    vAnd = vand_u32(vAnd, vdup_n_u32(1));
    return (bool)vget_lane_u32(vAnd, 0);
#else
    bool compare = false;
    if (vector.v[0] >= value &&
        vector.v[1] >= value)
        compare = true;
    return compare;
#endif
}
    
MATH_EXPORT MATH_STATIC_INLINE BBSVec2 BBSVec2Normalize(BBSVec2 vector)
{
    float scale = 1.0f / BBSVec2Magnitude(vector);
    BBSVec2 v = BBSVec2MultiplyScalar(vector, scale);
    return v;
}

MATH_EXPORT MATH_STATIC_INLINE float BBSVec2DotProduct(BBSVec2 vectorLeft, BBSVec2 vectorRight)
{
#if defined(__ARM_NEON__)
    float32x2_t v = vmul_f32(*(float32x2_t *)&vectorLeft,
                             *(float32x2_t *)&vectorRight);
    v = vpadd_f32(v, v);
    return vget_lane_f32(v, 0);
#else
    return vectorLeft.v[0] * vectorRight.v[0] + vectorLeft.v[1] * vectorRight.v[1];
#endif
}

MATH_EXPORT MATH_STATIC_INLINE float BBSVec2Magnitude(BBSVec2 vector)
{
#if defined(__ARM_NEON__)
    float32x2_t v = vmul_f32(*(float32x2_t *)&vector,
                             *(float32x2_t *)&vector);
    v = vpadd_f32(v, v);
    return sqrt(vget_lane_f32(v, 0)); 
#else
    return sqrt(vector.v[0] * vector.v[0] + vector.v[1] * vector.v[1]);
#endif
}

MATH_EXPORT MATH_STATIC_INLINE float BBSVec2Distance(BBSVec2 vectorStart, BBSVec2 vectorEnd)
{
    return BBSVec2Magnitude(BBSVec2Subtract(vectorEnd, vectorStart));
}
    
MATH_EXPORT MATH_STATIC_INLINE BBSVec2 BBSVec2Lerp(BBSVec2 vectorStart, BBSVec2 vectorEnd, float t)
{
#if defined(__ARM_NEON__)
    float32x2_t vDiff = vsub_f32(*(float32x2_t *)&vectorEnd,
                                 *(float32x2_t *)&vectorStart);
    vDiff = vmul_f32(vDiff, vdup_n_f32((float32_t)t));
    float32x2_t v = vadd_f32(*(float32x2_t *)&vectorStart, vDiff);
    return *(BBSVec2 *)&v;
#else
    BBSVec2 v = { vectorStart.v[0] + ((vectorEnd.v[0] - vectorStart.v[0]) * t),
                     vectorStart.v[1] + ((vectorEnd.v[1] - vectorStart.v[1]) * t) };
    return v;
#endif
}

MATH_EXPORT MATH_STATIC_INLINE BBSVec2 BBSVec2Project(BBSVec2 vectorToProject, BBSVec2 projectionVector)
{
    float scale = BBSVec2DotProduct(projectionVector, vectorToProject) / BBSVec2DotProduct(projectionVector, projectionVector);
    BBSVec2 v = BBSVec2MultiplyScalar(projectionVector, scale);
    return v;
}

#ifdef __cplusplus
}
#endif

#endif /* __BBS_VECTOR_2_H */
