#include <Camera.h>
#include <iostream>

Camera::Camera(WorldSpace area)
	:_worldSize{ area },
	_projection(glm::ortho(
		-_worldSize.width / 2.f, _worldSize.width / 2.f,
		-_worldSize.height / 2.f, _worldSize.height / 2.f,
		-_worldSize.depth / 2.f, _worldSize.depth / 2.f))
{}
Camera& Camera::GetCamera() {
	static Camera cameraObj({ 2.f, 2.f, 2.f });
	return cameraObj;
}
glm::mat4 Camera::View(){
	auto view = glm::lookAt(_position, _position + _forwardDir, _upDir);
	return view;
}
glm::mat4 const& Camera::Projection() const {
	return _projection;
}
glm::vec2 const& Camera::Viewport() const
{
	return { _worldSize.width, _worldSize.height };
}
void Camera::ProjectionRescale(int width, int height) {
	_worldSize.width = width;
	_worldSize.height = height;
	_worldSize.depth = 3 * glm::max(_worldSize.width, _worldSize.height);
	_projection = glm::infinitePerspective(glm::radians(60.f), _worldSize.width / _worldSize.height, 10.f);
	//_projection = glm::ortho(
	//	-_worldSize.width / 2.f, _worldSize.width / 2.f,
	//	-_worldSize.height / 2.f, _worldSize.height / 2.f,
	//	-_worldSize.depth / 2.f, _worldSize.depth / 2.f);
}
void Camera::Move(ImGuiKey direction) {
	auto tmpRightDir = glm::normalize(glm::cross(_forwardDir, _upDir));
	glm::vec3 moveDir{ 0.f };
	switch (direction)
	{
	case ImGuiKey_W:
		moveDir += _forwardDir;
		break;
	case ImGuiKey_S:
		moveDir -= _forwardDir;
		break;
	case ImGuiKey_A:
		moveDir -= tmpRightDir;
		break;
	case ImGuiKey_D:
		moveDir += tmpRightDir;
		break;
	case ImGuiKey_Q:
		moveDir -= _upDir;
		break;
	case ImGuiKey_E:
		moveDir += _upDir;
		break;
	default:
		break;
	}
	_position += moveDir * _moveSpeed;
}
void Camera::Rotate(glm::vec3 rotation) {
	rotation *= 0.1;
	glm::qua<float> lookingSpot = { 0.f, _forwardDir };
	auto angle = glm::atan(rotation);
	lookingSpot = glm::rotate(lookingSpot, glm::radians(angle.x), _upDir);
	_forwardDir = glm::normalize(glm::vec3(lookingSpot.x, lookingSpot.y, lookingSpot.z));
	
	auto tmpRightDir = glm::normalize(glm::cross(_forwardDir, _upDir));
	lookingSpot = glm::rotate(lookingSpot, glm::radians(angle.y), tmpRightDir);
	auto nextforwardDir = glm::normalize(glm::vec3(lookingSpot.x, lookingSpot.y, lookingSpot.z));

	tmpRightDir = glm::cross(nextforwardDir, _upDir);
	if (glm::dot(tmpRightDir, tmpRightDir) > 5e-5) {
		_forwardDir = nextforwardDir;
	}
	//_upDir = glm::normalize(glm::cross(tmpRightDir, _forwardDir));
}