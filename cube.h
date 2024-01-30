#pragma once
#include "C:\Users\victo\OneDrive\Desktop\eduRend-main\src\model.h"

class cube : public Model
{
	unsigned m_number_of_indices = 0;
public:

	cube(ID3D11Device* dxdevice, ID3D11DeviceContext* dxdevice_context);

	
	virtual void Render() const;

	
	~cube() { }
};


