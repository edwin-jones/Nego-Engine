// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include <SDKDDKVer.h>
#include <Windows.h>

#include <stdio.h>
#include <tchar.h>
#include <math.h>
#include <iostream>
#include <vector>

#include "glew\include\GL\glew.h"
#include <gl/GL.h>
#include <gl/GLU.h>


#include <string>

using namespace std;

#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"

typedef Vector2<float> Vector2F;
typedef Vector2<double> Vector2D;
typedef Vector2<int> Vector2I;
typedef Vector2<short> Vector2S;

typedef Vector3<float> Vector3F;
typedef Vector3<double> Vector3D;
typedef Vector3<int> Vector3I;
typedef Vector3<short> Vector3S;

typedef Vector4<float> Vector4F;
typedef Vector4<double> Vector4D;
typedef Vector4<int> Vector4I;
typedef Vector4<short> Vector4S;

#include "Bitmap.h"
#include "Model.h"
#include "Camera.h"
#include "Renderer.h"

