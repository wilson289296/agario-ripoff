#ifndef Colors_hpp
#define Colors_hpp

class Colors {
    float r;
    float g;
    float b;
public:
    Colors(float = 1.0, float = 1.0, float = 1.0);

	void setR(float);
	void setG(float);
	void setB(float);

	float getR() const;
	float getG() const;
	float getB() const;
	
};

#endif
