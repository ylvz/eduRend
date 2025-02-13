#pragma once
#include "model.h"
#include <vector> // Lägg till denna för std::vector

class Cube : public Model
{
unsigned m_number_of_indices = 0;

public:
    Cube(ID3D11Device* dxdevice, ID3D11DeviceContext* dxdevice_context);
    ~Cube();

    void Render() const override;

private:

    std::vector<Vertex> vertices{24};  // Samling av vertices
    std::vector<unsigned> indices;
};
