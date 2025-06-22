#pragma once
#include "mesh.h"
#include "meshdata.h"
class baselight :public mesh
{

	light data;
public:
	baselight(const meshdata& InMeshData, const shadersource& InSource, const ftransform& InTransform, camera& InCamera,const ShaderProgram& InProgram, const light& InLight);
	void SetLightColor(const vec4& InColor, const string& InName);
	void SetLightPosition(const vec3& InPosition, const string& InName);
	virtual void SetLightData(const light& InLight, const int Index) const;
	virtual void SetViewSpec(const vec3& InPos) const;
	virtual void SetShininess()const;
	virtual light GetData() const;
};

