#pragma once

#include <functional>

#include <Shape.h>
#include <Entity.h>

template<GLenum Prim>
class Particles : public Entity {
private:
	std::unique_ptr<Shape<Prim>> _particleShape;
	uint64_t _meshRadius;
	DistributionShape _distributionShape{ DistributionShape::QUBE };
public:
	Particles(Shape<Prim> * const particleShape, std::size_t meshRadius);
	Particles(Particles<Prim> const& obj_copy) = delete;
	Particles(Particles<Prim>&& obj_move) = default;
	Particles& operator=(Particles<Prim> const& obj_copy) = delete;
	Particles& operator=(Particles<Prim>&& obj_move) = default;
	~Particles() override = default;
	void Initialize() override;
	void Calculate() override;
	void Draw() const override;
	void Bind() const;
	void UpdateBoundingDimensions();
	details_map Details() override;
	DistributionShape& GetDistributionShape();
	uint64_t& GetMeshRadius();
};

template<GLenum Prim>
Particles<Prim>::Particles(Shape<Prim>* const particleShape, uint64_t _meshRadius)
	:Entity(PhysicsType::DYNAMIC),
	_particleShape{ std::unique_ptr<Shape<Prim>>(particleShape) },
	_meshRadius{ _meshRadius }
{
	Initialize();
}
template<GLenum Prim>
void Particles<Prim>::Initialize()
{
	UpdateBoundingDimensions();
	_physicsDispatch.InitDefaultShape(GetDistributionShape(), GetPhysicsType());
}
template<GLenum Prim>
void Particles<Prim>::Calculate()
{
	_physicsDispatch.GenerateForces();
}
template<GLenum Prim>
void Particles<Prim>::Draw() const
{
	if (_visible) {
		glm::ivec3 const& meshDimensions = _physicsDispatch.GetMeshDimensions();
		_particleShape->Bind();
		_physicsDispatch.GetParticleMeshBuffer().Bind(_particleShape->GetRenderer().ID());
		_(glDrawElementsInstanced(_particleShape->GetDrawPrimitive(), _particleShape->GetVA().Size(), _particleShape->GetVA().IndexBufferType(), nullptr, meshDimensions.x * meshDimensions.y * meshDimensions.z));
		_physicsDispatch.GetParticleMeshBuffer().Unbind(_particleShape->GetRenderer().ID());
	}
}
template<GLenum Prim>
inline void Particles<Prim>::UpdateBoundingDimensions() {
	_physicsDispatch.UpdateMeshDimensions(glm::ivec3(_meshRadius));
}

template<GLenum Prim>
Particles<Prim>::details_map Particles<Prim>::Details()
{
	details_map details = Entity::Details();
	details.push_back({ "Location", { [=]() {return std::ref(this->_particleShape->GetLocation()); }, DetailsType::VEC3 } });
	details.push_back({ "Rotation", { [=]() {return std::ref(this->_particleShape->GetRotate()); }, DetailsType::VEC3 } });
	details.push_back({ "Scale", { [=]() {return std::ref(this->_particleShape->GetScale()); }, DetailsType::VEC3 } });
	details.push_back({ "Light", { [=]() {return std::ref(this->_particleShape->EnableLight()); }, DetailsType::BOOL } });
	details.push_back({ "Subdivision", { [=]() {return std::ref(this->_particleShape->GetSubdivision()); }, DetailsType::UINT64 } });
	details.push_back({ "Radius", { [=]() {return std::ref(this->_particleShape->GetRadius()); }, DetailsType::UINT64 } });
	details.push_back({ "Distribution shape", { [=]() {return std::ref(this->GetDistributionShape()); }, DetailsType::DISTSHAPE } });
	details.push_back({ "Mesh radius", { [=]() {return std::ref(this->GetMeshRadius()); }, DetailsType::UINT64 } });
	return details;
}

template<GLenum Prim>
DistributionShape& Particles<Prim>::GetDistributionShape()
{
	return _distributionShape;
}

template<GLenum Prim>
uint64_t& Particles<Prim>::GetMeshRadius()
{
	return _meshRadius;
}

