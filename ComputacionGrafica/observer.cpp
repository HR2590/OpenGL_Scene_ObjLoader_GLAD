#include "observer.h"

#include "baselight.h"
#include "mesh.h"

class baselight;



void observer::Bind(mesh* InMesh)
{
	Meshes.push_back(InMesh);
	
}

void observer::BindLight(mesh* InLight)
{
	Lights.push_back(InLight);
}

void observer::Draw(const mat4& InProj,const mat4& InView,const vec3& InPos) const
{
	for (auto* InMesh : Meshes)
	{
		InMesh->SetProjectionMatrix(InProj);
		InMesh->SetViewMatrix(InView);
		InMesh->SetViewSpec(InPos);
		SendLightData(InMesh);
		InMesh->Draw();
		
	}

}

void observer::SendLightData(const mesh* InMesh) const
{
	int i = 0;
	for (auto* InLight : Lights)
	{
		InMesh->SetLightData(InLight->GetData(),i);
		i++;
		
	}
}

void observer::UnbindAll() const
{
	for (auto* InMesh : Meshes)
	{
		
		delete InMesh;
		
	}

	for (auto* InLight:Lights)
	{
		delete InLight;
	}
}
