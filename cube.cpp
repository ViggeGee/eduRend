#include "cube.h"

cube::cube(
	ID3D11Device* dxdevice,
	ID3D11DeviceContext* dxdevice_context)
	: Model(dxdevice, dxdevice_context)
	
	{

	std::vector<Vertex> vertices;
	std::vector<unsigned> indices;

	Vertex v00, v01, v02, v03;
	v00.Position = { -0.5, -0.5f, 0.5f };
	v01.Position = { 0.5, -0.5f, 0.5f };
	v02.Position = { 0.5, 0.5f, 0.5f };
	v03.Position = { -0.5, 0.5f, 0.5f };
	v00.Normal = { 0, 0, 1 };
	v01.Normal = { 0, 0, 1 };
	v02.Normal = { 0, 0, 1 };
	v03.Normal = { 0, 0, 1 };
	v00.TexCoord = { 0, 0 };
	v01.TexCoord = { 0, 1 };
	v02.TexCoord = { 1, 1 };
	v03.TexCoord = { 1, 0 };
	vertices.push_back(v00);
	vertices.push_back(v01);
	vertices.push_back(v02);
	vertices.push_back(v03);
	
	indices.push_back(0);
	indices.push_back(1);
	indices.push_back(3);
	
	indices.push_back(1);
	indices.push_back(2);
	indices.push_back(3);

	Vertex v10, v11, v12, v13;
	v10.Position = { -0.5, -0.5f, -0.5f };
	v11.Position = { 0.5, -0.5f, -0.5f };
	v12.Position = { 0.5, 0.5f, -0.5f };
	v13.Position = { -0.5, 0.5f, -0.5f };
	v10.Normal = { 0, 0, 1 };
	v11.Normal = { 0, 0, 1 };
	v12.Normal = { 0, 0, 1 };
	v13.Normal = { 0, 0, 1 };
	v10.TexCoord = { 0, 0 };
	v11.TexCoord = { 0, 1 };
	v12.TexCoord = { 1, 1 };
	v13.TexCoord = { 1, 0 };
	vertices.push_back(v10);
	vertices.push_back(v11);
	vertices.push_back(v12);
	vertices.push_back(v13);

	indices.push_back(4);
	indices.push_back(7);
	indices.push_back(5);
	
	indices.push_back(5);
	indices.push_back(7);
	indices.push_back(6);


	Vertex v20, v21, v22, v23;
	v20.Position = { -0.5, -0.5f, -0.5f };
	v21.Position = { -0.5, -0.5f, 0.5f };
	v22.Position = { -0.5, 0.5f, 0.5f };
	v23.Position = { -0.5, 0.5f, -0.5f };
	v20.Normal = { 1, 0, 0 };
	v21.Normal = { 1, 0, 0 };
	v22.Normal = { 1, 0, 0 };
	v23.Normal = { 1, 0, 0 };
	v20.TexCoord = { 0, 0 };
	v21.TexCoord = { 0, 1 };
	v22.TexCoord = { 1, 1 };
	v23.TexCoord = { 1, 0 };
	vertices.push_back(v20);
	vertices.push_back(v21);
	vertices.push_back(v22);
	vertices.push_back(v23);

	indices.push_back(8);
	indices.push_back(9);
	indices.push_back(11);

	indices.push_back(9);
	indices.push_back(10);
	indices.push_back(11);

	Vertex v30, v31, v32, v33;
	v30.Position = { 0.5, -0.5f, -0.5f };
	v31.Position = { 0.5, -0.5f, 0.5f };
	v32.Position = { 0.5, 0.5f, 0.5f };
	v33.Position = { 0.5, 0.5f, -0.5f };
	v30.Normal = { 1, 0, 0 };
	v31.Normal = { 1, 0, 0 };
	v32.Normal = { 1, 0, 0 };
	v33.Normal = { 1, 0, 0 };
	v30.TexCoord = { 0, 0 };
	v31.TexCoord = { 0, 1 };
	v32.TexCoord = { 1, 1 };
	v33.TexCoord = { 1, 0 };
	vertices.push_back(v30);
	vertices.push_back(v31);
	vertices.push_back(v32);
	vertices.push_back(v33);

	indices.push_back(12);
	indices.push_back(15);
	indices.push_back(13);

	indices.push_back(13);
	indices.push_back(15);
	indices.push_back(14);

	Vertex v40, v41, v42, v43;
	v40.Position = { -0.5, -0.5f, -0.5f };
	v41.Position = { -0.5, -0.5f, 0.5f };
	v42.Position = { 0.5, -0.5f, 0.5f };
	v43.Position = { 0.5, -0.5f, -0.5f };
	v40.Normal = { 0, 1, 0 };
	v41.Normal = { 0, 1, 0 };
	v42.Normal = { 0, 1, 0 };
	v43.Normal = { 0, 1, 0 };
	v40.TexCoord = { 0, 0 };
	v41.TexCoord = { 0, 1 };
	v42.TexCoord = { 1, 1 };
	v43.TexCoord = { 1, 0 };
	vertices.push_back(v40);
	vertices.push_back(v41);
	vertices.push_back(v42);
	vertices.push_back(v43);

	indices.push_back(16);
	indices.push_back(19);
	indices.push_back(17);

	indices.push_back(17);
	indices.push_back(19);
	indices.push_back(18);

	Vertex v50, v51, v52, v53;
	v50.Position = { -0.5, 0.5f, -0.5f };
	v51.Position = { -0.5, 0.5f, 0.5f };
	v52.Position = { 0.5, 0.5f, 0.5f };
	v53.Position = { 0.5, 0.5f, -0.5f };
	v50.Normal = { 0, 1, 0 };
	v51.Normal = { 0, 1, 0 };
	v52.Normal = { 0, 1, 0 };
	v53.Normal = { 0, 1, 0 };
	v50.TexCoord = { 0, 0 };
	v51.TexCoord = { 0, 1 };
	v52.TexCoord = { 1, 1 };
	v53.TexCoord = { 1, 0 };
	vertices.push_back(v50);
	vertices.push_back(v51);
	vertices.push_back(v52);
	vertices.push_back(v53);

	indices.push_back(20);
	indices.push_back(21);
	indices.push_back(23);

	indices.push_back(21);
	indices.push_back(22);
	indices.push_back(23);


	// Vertex array descriptor
	D3D11_BUFFER_DESC vertexbufferDesc{ 0 };
	vertexbufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexbufferDesc.CPUAccessFlags = 0;
	vertexbufferDesc.Usage = D3D11_USAGE_DEFAULT;
	vertexbufferDesc.MiscFlags = 0;
	vertexbufferDesc.ByteWidth = (UINT)(vertices.size() * sizeof(Vertex));
	// Data resource
	D3D11_SUBRESOURCE_DATA vertexData = { 0 };
	vertexData.pSysMem = &vertices[0];
	// Create vertex buffer on device using descriptor & data
	dxdevice->CreateBuffer(&vertexbufferDesc, &vertexData, &m_vertex_buffer);
	SETNAME(m_vertex_buffer, "VertexBuffer");

	//  Index array descriptor
	D3D11_BUFFER_DESC indexbufferDesc = { 0 };
	indexbufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indexbufferDesc.CPUAccessFlags = 0;
	indexbufferDesc.Usage = D3D11_USAGE_DEFAULT;
	indexbufferDesc.MiscFlags = 0;
	indexbufferDesc.ByteWidth = (UINT)(indices.size() * sizeof(unsigned));
	// Data resource
	D3D11_SUBRESOURCE_DATA indexData{ 0 };
	indexData.pSysMem = &indices[0];
	// Create index buffer on device using descriptor & data
	dxdevice->CreateBuffer(&indexbufferDesc, &indexData, &m_index_buffer);
	SETNAME(m_index_buffer, "IndexBuffer");

	m_number_of_indices = (unsigned int)indices.size();
}


void cube::Render() const
{
	// Bind our vertex buffer
	const UINT32 stride = sizeof(Vertex); //  sizeof(float) * 8;
	const UINT32 offset = 0;
	m_dxdevice_context->IASetVertexBuffers(0, 1, &m_vertex_buffer, &stride, &offset);

	// Bind our index buffer
	m_dxdevice_context->IASetIndexBuffer(m_index_buffer, DXGI_FORMAT_R32_UINT, 0);

	// Make the drawcall
	m_dxdevice_context->DrawIndexed(m_number_of_indices, 0, 0);
}

