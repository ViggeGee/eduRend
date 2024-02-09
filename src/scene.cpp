
#include "Scene.h"
#include "QuadModel.h"
#include "OBJModel.h"
#include "C:\Users\victo\OneDrive\Desktop\eduRend-main\cube.h"

Scene::Scene(
	ID3D11Device* dxdevice,
	ID3D11DeviceContext* dxdevice_context,
	int window_width,
	int window_height) :
	m_dxdevice(dxdevice),
	m_dxdevice_context(dxdevice_context),
	m_window_width(window_width),
	m_window_height(window_height)
{ }

void Scene::OnWindowResized(
	int new_width,
	int new_height)
{
	m_window_width = new_width;
	m_window_height = new_height;
}

OurTestScene::OurTestScene(
	ID3D11Device* dxdevice,
	ID3D11DeviceContext* dxdevice_context,
	int window_width,
	int window_height) :
	Scene(dxdevice, dxdevice_context, window_width, window_height)
{
	InitTransformationBuffer();
	InitLightCamBuffer();
	InitMaterialBuffer();
	InitSampler(dxdevice, dxdevice_context);
}

//
// Called once at initialization
//
void OurTestScene::Init()
{
	m_camera = new Camera(
		45.0f * fTO_RAD,		// field-of-view (radians)
		(float)m_window_width / m_window_height,	// aspect ratio
		1.0f,					// z-near plane (everything closer will be clipped/removed)
		500.0f);				// z-far plane (everything further will be clipped/removed)

	// Move camera to (0,0,5)
	m_camera->MoveTo({ 0, 0, 5 });

	// Create objects
	if (loadCube)
		m_quad = new cube(m_dxdevice, m_dxdevice_context);
	if (loadSponza)
		m_sponza = new OBJModel("assets/crytek-sponza/sponza.obj", m_dxdevice, m_dxdevice_context);

	m_earth = new OBJModel("assets/sphere/sphere.obj", m_dxdevice, m_dxdevice_context);
	m_sun = new OBJModel("assets/sphere/sphere.obj", m_dxdevice, m_dxdevice_context);
	m_planet = new OBJModel("assets/sphere/sphere.obj", m_dxdevice, m_dxdevice_context);
}

//
// Called every frame
// dt (seconds) is time elapsed since the previous frame
//
void OurTestScene::Update(
	float dt,
	const InputHandler& input_handler)
{
	// Basic camera control
	if (input_handler.IsKeyPressed(Keys::Up) || input_handler.IsKeyPressed(Keys::W))
		m_camera->Move((m_camera->m_rotation * vec4f(0.0f, 0.0f, -m_camera_velocity *dt,0)).xyz());
	if (input_handler.IsKeyPressed(Keys::Down) || input_handler.IsKeyPressed(Keys::S))
		m_camera->Move((m_camera->m_rotation * vec4f(0.0f, 0.0f, m_camera_velocity * dt, 0)).xyz());
	if (input_handler.IsKeyPressed(Keys::Right) || input_handler.IsKeyPressed(Keys::D))
		m_camera->Move((m_camera->m_rotation * vec4f(m_camera_velocity * dt, 0.0f, 0.0f, 0)).xyz());
	if (input_handler.IsKeyPressed(Keys::Left) || input_handler.IsKeyPressed(Keys::A))
		m_camera->Move((m_camera->m_rotation * vec4f(-m_camera_velocity * dt, 0.0f, 0.0f, 0)).xyz());

	float mousedx = input_handler.GetMouseDeltaX() * 0.01f;
	float mousedy = input_handler.GetMouseDeltaY() * 0.01f;

	xRot += mousedx;
	yRot += mousedy;

	m_camera->Rotate(0, -xRot, -yRot);
	





	// Now set/update object transformations
	// This can be done using any sequence of transformation matrices,
	// but the T*R*S order is most common; i.e. scale, then rotate, and then translate.
	// If no transformation is desired, an identity matrix can be obtained 
	// via e.g. Mquad = linalg::mat4f_identity; 

	// Quad model-to-world transformation
	if (loadCube)
	{
		m_quad_transform = mat4f::translation(0, 0, 0) *			// No translation
			//mat4f::rotation(-m_angle, 0.0f, 1.0f, 0.0f) *	// Rotate continuously around the y-axis
			//mat4f::rotation(-m_angle, 0.0f, 0.0f, 1.0f) *	// Rotate continuously around the y-axis

			mat4f::scaling(1.5, 1.5, 1.5);				// Scale uniformly to 150%

	}

	if (loadSponza)
	{
		// Sponza model-to-world transformation
		m_sponza_transform = mat4f::translation(0, -5, 0) *		 // Move down 5 units
			mat4f::rotation(fPI / 2, 0.0f, 1.0f, 0.0f) * // Rotate pi/2 radians (90 degrees) around y
			mat4f::scaling(0.05f);						 // The scene is quite large so scale it down to 5%
	}

	m_sun_transform = mat4f::translation(0, 0, 0) *
		mat4f::rotation(-m_angle, 0.0f, 1.0f, 0.0f) *
		mat4f::scaling(0.9f);

	m_earth_transform = mat4f::translation(2, 0, 0) *
		mat4f::rotation(-m_angle, 0.0f, 1.0f, 0.0f) *
		mat4f::scaling(0.3f);

	m_planet_transform = mat4f::translation(2, 0, 0) *
		mat4f::rotation(-m_angle, 1.0f, 0.0f, 0.0f) *
		mat4f::scaling(0.2f);

	m_earth_transform = m_sun_transform * m_earth_transform;
	m_planet_transform = m_earth_transform * m_planet_transform;

	// Increment the rotation angle.
	m_angle += m_angular_velocity * dt;

	// Print fps
	m_fps_cooldown -= dt;
	if (m_fps_cooldown < 0.0)
	{
		std::cout << "fps " << (int)(1.0f / dt) << std::endl;
		//		printf("fps %i\n", (int)(1.0f / dt));
		m_fps_cooldown = 2.0;
	}

	
}

//
// Called every frame, after update
//
void OurTestScene::Render()
{
	// Bind transformation_buffer to slot b0 of the VS
	m_dxdevice_context->VSSetConstantBuffers(0, 1, &m_transformation_buffer);
	m_dxdevice_context->PSSetConstantBuffers(0, 1, &m_lightcam_buffer);
	m_dxdevice_context->PSSetConstantBuffers(1, 1, &m_material_buffer);
	// Obtain the matrices needed for rendering from the camera
	m_view_matrix = m_camera->WorldToViewMatrix();
	m_projection_matrix = m_camera->ProjectionMatrix();
	UpdateLightCam(m_camera->GetPosition(), m_view_matrix * float4(0.0f,0.0f,-1.0f,0.0f));
	UpdateMaterialBuffer(float4(150, 100, 150,1), float4(150, 100, 150,0.0f), float4(150,150,150, 0.0f), 10.0f);
	
	
	// Load matrices + the Quad's transformation to the device and render it
	if (loadCube)
	{
		UpdateTransformationBuffer(m_quad_transform, m_view_matrix, m_projection_matrix);
		m_quad->Render();

	}

	if (loadSponza)
	{
		// Load matrices + Sponza's transformation to the device and render it
		UpdateTransformationBuffer(m_sponza_transform, m_view_matrix, m_projection_matrix);

		m_sponza->Render();
	}

	UpdateTransformationBuffer(m_sun_transform, m_view_matrix, m_projection_matrix);
	UpdateMaterialBuffer(float4(255, 255, 0, 1), float4(255, 255, 0, 0.0f), float4(150, 150, 150, 0.0f), 10.0f);
	m_sun->Render();


	UpdateTransformationBuffer(m_earth_transform, m_view_matrix, m_projection_matrix);
	UpdateMaterialBuffer(float4(100, 200, 100, 1), float4(65, 150, 70, 0.0f), float4(150, 150, 150, 0.0f), 10.0f);
	m_earth->Render();	

	UpdateTransformationBuffer(m_planet_transform, m_view_matrix, m_projection_matrix);
	UpdateMaterialBuffer(float4(150, 150, 150, 1), float4(150, 150, 150, 0.0f), float4(150, 150, 150, 0.0f), 10.0f);
	m_planet->Render();
}

void OurTestScene::Release()
{
	if (loadCube)
		SAFE_DELETE(m_quad);
	if (loadSponza)
		SAFE_DELETE(m_sponza);
	SAFE_DELETE(m_camera);
	SAFE_DELETE(m_sun);
	SAFE_DELETE(m_earth);
	SAFE_DELETE(m_planet);
	SAFE_RELEASE(m_lightcam_buffer);
	SAFE_RELEASE(m_material_buffer);
	SAFE_RELEASE(m_transformation_buffer);
	SAFE_RELEASE(sampler);
	// + release other CBuffers
}

void OurTestScene::OnWindowResized(
	int new_width,
	int new_height)
{
	if (m_camera)
		m_camera->SetAspect(float(new_width) / new_height);

	Scene::OnWindowResized(new_width, new_height);
}



// Inside the OurTestScene class in Scene.cpp
ID3D11Buffer* m_lightcam_buffer;

// Define the InitLightCamBuffer() function in OurTestScene class
void OurTestScene::InitLightCamBuffer()
{
	HRESULT hr;
	D3D11_BUFFER_DESC lightcamBufferDesc = { 0 };
	lightcamBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	lightcamBufferDesc.ByteWidth = sizeof(LightCamBuffer);
	lightcamBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	lightcamBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	lightcamBufferDesc.MiscFlags = 0;
	lightcamBufferDesc.StructureByteStride = 0;
	ASSERT(hr = m_dxdevice->CreateBuffer(&lightcamBufferDesc, nullptr, &m_lightcam_buffer));
}

void OurTestScene::InitMaterialBuffer()
{
	HRESULT hr;
	D3D11_BUFFER_DESC materialBufferDesc = { 0 };
	materialBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	/*materialBufferDesc.ByteWidth = sizeof(MaterialBuffer);*/
	materialBufferDesc.ByteWidth = ((sizeof(Material) + 15) / 16) * 16;  // Round up to the nearest multiple of 16

	materialBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	materialBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	materialBufferDesc.MiscFlags = 0;
	materialBufferDesc.StructureByteStride = 0;
	ASSERT(hr = m_dxdevice->CreateBuffer(&materialBufferDesc, nullptr, &m_material_buffer));
}

void OurTestScene::InitSampler(ID3D11Device* dxdevice, ID3D11DeviceContext* dxdevice_context)
{
	samplerdesc =
	{
	D3D11_FILTER_MIN_MAG_MIP_LINEAR, // Filter
	D3D11_TEXTURE_ADDRESS_CLAMP, // AddressU
	D3D11_TEXTURE_ADDRESS_CLAMP, // AddressV
	D3D11_TEXTURE_ADDRESS_CLAMP, // AddressW
	0.0f, // MipLODBias
	1, // MaxAnisotropy
	D3D11_COMPARISON_NEVER, // ComapirsonFunc
	{ 1.0f, 1.0f, 1.0f, 1.0f }, // BorderColor
	-FLT_MAX, // MinLOD
	FLT_MAX, // MaxLOD
	};
	dxdevice->CreateSamplerState(&samplerdesc, &sampler);

	dxdevice_context->PSSetSamplers(
		0, // slot #
		1, // number of samplers to bind (1)
		&sampler);

}

void OurTestScene::UpdateMaterialBuffer(float4 ambient, float4 diffuse, float4 specular, float shininess)
{
	D3D11_MAPPED_SUBRESOURCE resource;
	m_dxdevice_context->Map(m_material_buffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &resource);
	Material* matrixBuffer = (Material*)resource.pData;
	matrixBuffer->AmbientColour = ambient;
	matrixBuffer->DiffuseColour = diffuse;
	matrixBuffer->SpecularColour = specular;
	matrixBuffer->Shininess = shininess;
	m_dxdevice_context->Unmap(m_material_buffer, 0);
}

void OurTestScene::UpdateLightCam(vec3f camPos, float4 lightPos)
{
	D3D11_MAPPED_SUBRESOURCE resource;
	m_dxdevice_context->Map(m_lightcam_buffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &resource);
	LightCamBuffer* matrixBuffer = (LightCamBuffer*)resource.pData;
	matrixBuffer->CameraPosition = float4(camPos, 1.0f);
	matrixBuffer->LightPosition = lightPos;
	m_dxdevice_context->Unmap(m_lightcam_buffer, 0);
}

void OurTestScene::UpdateTransformationBuffer(
	mat4f ModelToWorldMatrix,
	mat4f WorldToViewMatrix,
	mat4f ProjectionMatrix)
{
	// Map the resource buffer, obtain a pointer and then write our matrices to it
	D3D11_MAPPED_SUBRESOURCE resource;
	m_dxdevice_context->Map(m_transformation_buffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &resource);
	TransformationBuffer* matrixBuffer = (TransformationBuffer*)resource.pData;
	matrixBuffer->ModelToWorldMatrix = ModelToWorldMatrix;
	matrixBuffer->WorldToViewMatrix = WorldToViewMatrix;
	matrixBuffer->ProjectionMatrix = ProjectionMatrix;
	m_dxdevice_context->Unmap(m_transformation_buffer, 0);
}



// Inside the OurTestScene class in Scene.cpp
ID3D11Buffer* m_mtl_buffer;




void OurTestScene::InitTransformationBuffer()
{
	HRESULT hr;
	D3D11_BUFFER_DESC matrixBufferDesc = { 0 };
	matrixBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	matrixBufferDesc.ByteWidth = sizeof(TransformationBuffer);
	matrixBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	matrixBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	matrixBufferDesc.MiscFlags = 0;
	matrixBufferDesc.StructureByteStride = 0;
	ASSERT(hr = m_dxdevice->CreateBuffer(&matrixBufferDesc, nullptr, &m_transformation_buffer));
}