/**
 * @file model.h
 * @brief Contains model definitions
 * @author Carl Johan Gribel 2016, cjgribel@gmail.com
*/

#pragma once
#ifndef MODEL_H
#define MODEL_H

#include "stdafx.h"
#include <vector>
#include "vec\vec.h"
#include "vec\mat.h"
#include "Drawcall.h"
#include "OBJLoader.h"
#include "Texture.h"
#include "buffers.h"

using namespace linalg;

/**
 * @brief Abstract class. Defines the Render method and contains mesh data needed for a model.
*/
class Model
{
protected:
	// Pointers to the current device and device context
	ID3D11Device* const			m_dxdevice; //!< Graphics device, use for creating resources.
	ID3D11DeviceContext* const	m_dxdevice_context; //!< Graphics context, use for binding resources and draw commands.

	// Pointers to the class' vertex & index arrays
	ID3D11Buffer* m_vertex_buffer = nullptr; //!< Pointer to gpu side vertex buffer
	ID3D11Buffer* m_index_buffer = nullptr; //!< Pointer to gpu side index buffer
	ID3D11Buffer * m_material_buffer = nullptr;
	Material m_material;

	virtual void UpdateMaterialBuffer(const Material& material) const {
		if (!m_material_buffer) return;

		D3D11_MAPPED_SUBRESOURCE mapped;
		if (SUCCEEDED(m_dxdevice_context->Map(m_material_buffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mapped))) {
			MaterialBuffer* data = static_cast<MaterialBuffer*>(mapped.pData);
			data->ambient = vec4f(material.AmbientColour, 1.0f);
			data->diffuse = vec4f(material.DiffuseColour, 1.0f);
			data->specular = vec4f(material.SpecularColour, 1.0f);
			data->shininess = material.Shininess;
			m_dxdevice_context->Unmap(m_material_buffer, 0);
		}
	}

	virtual void InitMaterialBuffer() {
		if (m_material_buffer) return;

		D3D11_BUFFER_DESC desc = {};
		desc.ByteWidth = sizeof(MaterialBuffer);
		desc.Usage = D3D11_USAGE_DYNAMIC;
		desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		m_dxdevice->CreateBuffer(&desc, nullptr, &m_material_buffer);
	}

public:

	/**
	 * @brief Sets the protected member variables to the input params.
	 * @param dxdevice ID3D11Device to be used in the model.
	 * @param dxdevice_context ID3D11DeviceContext to be used in the model.
	*/
	Model(ID3D11Device* dxdevice, ID3D11DeviceContext* dxdevice_context) 
		:	m_dxdevice(dxdevice), m_dxdevice_context(dxdevice_context) { }

	/**
	 * @brief Abstract render method: must be implemented by derived classes
	*/
	virtual void Render() const = 0;

	void SetMaterial(const Material& new_material) { m_material = new_material; UpdateMaterialBuffer(m_material); }

	Material& GetMaterial() { return m_material; }
	virtual ~Model()
	{ 
		SAFE_RELEASE(m_vertex_buffer);
		SAFE_RELEASE(m_index_buffer);
		SAFE_RELEASE(m_material_buffer);
	}
};

#endif