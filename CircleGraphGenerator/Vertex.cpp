#include "Vertex.h"



Vertex::Vertex()
{
}


Vertex::~Vertex()
{
}

bool Vertex::operator=(const Vertex& v) const {
    return this->word == v.word && this->type == v.type;
}
