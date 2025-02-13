#include "Cube.h"
#include <vector>

Cube::Cube(ID3D11Device* dxdevice, ID3D11DeviceContext* dxdevice_context)
    : Model(dxdevice, dxdevice_context)
{
    vertices[0].Position = { -0.5f, -0.5f, 0.0f };
    vertices[0].Normal = { 0, 0, 1 };
    vertices[0].TexCoord = { 0, 0 };
    vertices[1].Position = { 0.5f, -0.5f, 0.0f };
    vertices[1].Normal = { 0, 0, 1 };
    vertices[1].TexCoord = { 0, 1 };
    vertices[2].Position = { 0.5f, 0.5f, 0.0f };
    vertices[2].Normal = { 0, 0, 1 };
    vertices[2].TexCoord = { 1, 1 };
    vertices[3].Position = { -0.5f, 0.5f, 0.0f };
    vertices[3].Normal = { 0, 0, 1 };
    vertices[3].TexCoord = { 1, 0 };

    vertices[4].Position = { 0.5f, 0.5f, 0.0f };
    vertices[4].Normal = { -1, 0, 0 };
    vertices[4].TexCoord = { 0, 0 };
    vertices[5].Position = { 0.5f, -0.5f, 0.0f };
    vertices[5].Normal = { -1, 0, 0 };
    vertices[5].TexCoord = { 0, 1 };
    vertices[6].Position = { 0.5f, -0.5f, -1.0f };
    vertices[6].Normal = { -1, 0, 0 };
    vertices[6].TexCoord = { 1, 1 };
    vertices[7].Position = { 0.5f, 0.5f, -1.0f };
    vertices[7].Normal = { -1, 0, 0 };
    vertices[7].TexCoord = { 1, 0 };

    vertices[8].Position = { -0.5f, -0.5f, 0.0f };
    vertices[8].Normal = { 1, 0, 0 };
    vertices[8].TexCoord = { 0, 0 };
    vertices[9].Position = { -0.5f, 0.5f, 0.0f };
    vertices[9].Normal = { 1, 0, 0 };
    vertices[9].TexCoord = { 0, 1 };
    vertices[10].Position = { -0.5f, 0.5f, -1.0f };
    vertices[10].Normal = { 1, 0, 0 };
    vertices[10].TexCoord = { 1, 1 };
    vertices[11].Position = { -0.5f, -0.5f, -1.0f };
    vertices[11].Normal = { 1, 0, 0 };
    vertices[11].TexCoord = { 1, 0 };

    vertices[12].Position = { 0.5f, 0.5f, -1.0f };
    vertices[12].Normal = { 0, 0, -1 };
    vertices[12].TexCoord = { 0, 0 };
    vertices[13].Position = { 0.5f, -0.5f, -1.0f };
    vertices[13].Normal = { 0, 0, -1 };
    vertices[13].TexCoord = { 0, 1 };
    vertices[14].Position = { -0.5f, -0.5f, -1.0f };
    vertices[14].Normal = { 0, 0, -1 };
    vertices[14].TexCoord = { 1, 1 };
    vertices[15].Position = { -0.5f, 0.5f, -1.0f };
    vertices[15].Normal = { 0, 0, -1 };
    vertices[15].TexCoord = { 1, 0 };

    vertices[16].Position = { -0.5f, 0.5f, -1.0f };
    vertices[16].Normal = { 0, 1, 0 };
    vertices[16].TexCoord = { 0, 0 };
    vertices[17].Position = { -0.5f, 0.5f, 0.0f };
    vertices[17].Normal = { 0, 1, 0 };
    vertices[17].TexCoord = { 0, 1 };
    vertices[18].Position = { 0.5f, 0.5f, 0.0f };
    vertices[18].Normal = { 0, 1, 0 };
    vertices[18].TexCoord = { 1, 1 };
    vertices[19].Position = { 0.5f, 0.5f, -1.0f };
    vertices[19].Normal = { 0, 1, 0 };
    vertices[19].TexCoord = { 1, 0 };

    vertices[20].Position = { -0.5f, -0.5f, -1.0f };
    vertices[20].Normal = { 0, -1, 0 };
    vertices[20].TexCoord = { 0, 0 };
    vertices[21].Position = { 0.5f, -0.5f, -1.0f };
    vertices[21].Normal = { 0, -1, 0 };
    vertices[21].TexCoord = { 0, 1 };
    vertices[22].Position = { 0.5f, -0.5f, 0.0f };
    vertices[22].Normal = { 0, -1, 0 };
    vertices[22].TexCoord = { 1, 1 };
    vertices[23].Position = { -0.5f, -0.5f, 0.0f };
    vertices[23].Normal = { 0, -1, 0 };
    vertices[23].TexCoord = { 1, 0 };


    // Skapa index buffer
    indices = {
        0, 1, 2, 2, 3, 0,
        4, 5, 6, 6, 7, 4,
        8, 9, 10, 10, 11, 8,
        12, 13, 14, 14, 15, 12,
        16, 17, 18, 18, 19, 16,
        20, 21, 22, 22, 23, 20
    };

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

Cube::~Cube() { }

void Cube::Render() const
{
    UINT stride = sizeof(Vertex);
    UINT offset = 0;
    m_dxdevice_context->IASetVertexBuffers(0, 1, &m_vertex_buffer, &stride, &offset);
    m_dxdevice_context->IASetIndexBuffer(m_index_buffer, DXGI_FORMAT_R32_UINT, 0);
    m_dxdevice_context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

    m_dxdevice_context->DrawIndexed(36, 0, 0);
}
