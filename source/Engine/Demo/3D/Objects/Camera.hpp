//
//  Camera.hpp
//  TestEngine
//
//  Created by Vladas Zakrevskis on 9/17/18.
//  Copyright © 2017 VladasZ. All rights reserved.
//

#pragma once

#include "Matrix4.hpp"

class Camera {

	float _near = 0.1f;
	float _far = 100.0f;
	float _ratio;
	float _fov;

	Matrix4 _mvp;

public:

	Camera();

	const Matrix4& mvp();

};
