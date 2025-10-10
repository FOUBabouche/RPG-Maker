#ifndef BRUSH_H
#define BRUSH_H

class Brush {
public:
	void SetSize(unsigned int size);
	unsigned int GetSize(void) const;
private:
	unsigned int m_size;
};

#endif