#pragma once
#include <vector>
#include <glm/gtc/type_ptr.hpp>

#include "meshdata.h"


class baselight;
class mesh;

using namespace std;
using namespace glm;

class observer
{
	vector<mesh*> Meshes;
	vector<mesh*> Lights;

	void SendLightData(const mesh* InMesh) const;
public:
	void Bind(mesh* InMesh);
	void BindLight(mesh* InLight);
	void Draw(const mat4& InProj, const mat4& InView, const vec3& InPos) const;
	void UnbindAll() const;
};

