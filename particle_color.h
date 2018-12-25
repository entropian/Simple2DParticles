#include <vector>
#include "particle.h"

class ParticleColorCalculator
{
public:
	ParticleColorCalculator(const float brightness_modifier);
	virtual void calcColor(float &r, float &g, float &b, const Particle& p) = 0;
protected:
	const float brightness_modifier;
};

class ForceColor : public ParticleColorCalculator
{
public:
	ForceColor(const float brightness_modifier);
	void calcColor(float &r, float &g, float &b, const Particle &p) override;
};

class VelocityColor : public ParticleColorCalculator
{
public:
	VelocityColor(const float brightness_modifier);
	void calcColor(float &r, float &g, float &b, const Particle &p) override;
};