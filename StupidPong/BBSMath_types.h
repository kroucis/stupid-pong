//
//  BBSMathTypes.h
//  BBSit
//
//  Copyright (c) 2011, Apple Inc. All rights reserved.
//

#ifndef __BBS_MATH_TYPES_H
#define __BBS_MATH_TYPES_H

#define MATH_STATIC_INLINE		static __inline__
#define MATH_STRUCT				typedef struct
#define MATH_UNION				typedef union
#define MATH_EXPORT			
#define MATH_IMPORT				

#ifdef __cplusplus
extern "C" {
#endif

#if defined(__STRICT_ANSI__)
struct _BBSMat2
{
    float m[4];
};
MATH_EXPORT MATH_STRUCT _BBSMat2 BBSMat2;
#else
union _BBSMat2
{
    struct
    {
        float m00, m01;
        float m10, m11;
    };
    float m2[2][2];
    float m[4];
	float m2x2[2][2];
};
MATH_EXPORT MATH_UNION _BBSMat2 BBSMat2;
#endif
    
#if defined(__STRICT_ANSI__)
struct _BBSMat3
{
    float m[9];
};
MATH_EXPORT MATH_STRUCT _BBSMat3 BBSMat3; 
#else
union _BBSMat3
{
    struct
    {
        float m00, m01, m02;
        float m10, m11, m12;
        float m20, m21, m22;
    };
    float m[9];
	float m3x3[3][3];
};
MATH_EXPORT MATH_UNION _BBSMat3 BBSMat3;
#endif
    
/*
 m30, m31, and m32 correspond to the translation values tx, ty, and tz, respectively.
 m[12], m[13], and m[14] correspond to the translation values tx, ty, and tz, respectively.
 */
#if defined(__STRICT_ANSI__)
struct _BBSMat4
{
    float m[16];
} __attribute__((aligned(16)));
MATH_EXPORT MATH_STRUCT _BBSMat4 BBSMat4;    
#else
union _BBSMat4
{
    struct
    {
        float m00, m01, m02, m03;
        float m10, m11, m12, m13;
        float m20, m21, m22, m23;
        float m30, m31, m32, m33;
    };
    float m[16];
	float m4x4[4][4];
} __attribute__((aligned(16)));
MATH_EXPORT MATH_UNION _BBSMat4 BBSMat4;
#endif
    
#if defined(__STRICT_ANSI__)
struct _BBSVec2
{
    float v[2];
};
typedef struct _BBSVec2 BBSVec2;
#else
union _BBSVec2
{
    struct { float x, y; };
    struct { float s, t; };
	struct { float width, height; };
    float v[2];
};
MATH_EXPORT MATH_UNION _BBSVec2 BBSVec2;
#endif
typedef BBSVec2 BBSPoint2;
typedef BBSVec2 BBSTex2;
typedef BBSVec2 BBSSize2;
    
#if defined(__STRICT_ANSI__)
struct _BBSVec3
{
    float v[3];
};
MATH_EXPORT MATH_STRUCT _BBSVec3 BBSVec3;   
#else
union _BBSVec3
{
    struct { float x, y, z; };
    struct { float r, g, b; };
    struct { float s, t, p; };
	struct { float width, height, depth; };
    float v[3];
};
MATH_EXPORT MATH_UNION _BBSVec3 BBSVec3;
#endif
typedef BBSVec3 BBSPoint3;
typedef BBSVec3 BBSColor3;
typedef BBSVec3 BBSTex3;
typedef BBSVec3 BBSSize3;
    
#if defined(__STRICT_ANSI__)
struct _BBSVec4
{
    float v[4];
} __attribute__((aligned(16)));
MATH_EXPORT MATH_STRUCT _BBSVec4 BBSVec4;  
#else
union _BBSVec4
{
    struct { float x, y, z, w; };
    struct { float r, g, b, a; };
    struct { float s, t, p, q; };
    float v[4];
} __attribute__((aligned(16)));
MATH_EXPORT MATH_UNION _BBSVec4 BBSVec4;
#endif
typedef BBSVec4 BBSPoint4;
typedef BBSVec4 BBSColor4;
typedef BBSVec4 BBSTex4;
typedef BBSVec4 BBSQuaternion;
    
#ifdef __cplusplus
}
#endif

#endif /* __BBS_MATH_TYPES_H */
