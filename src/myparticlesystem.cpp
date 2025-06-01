#include "AGL.h"
#include "AGLM.h"
#include <cmath>
#include "myparticlesystem.h"

using namespace std;
using namespace agl;
using namespace glm;

vec3 offset = vec3(0);
vec3 color = random_unit_cube();

void MyParticleSystem::createParticles(int size)
{

	fire_texture = theRenderer.loadTexture("textures/ParticleFirecloud.png");

	for (int i = 0; i < 20; i++)
	{

		Particle p;
		p.pos = offset;
		p.pos.y = offset.y + random_float(0, 0.05f);
		p.size = 0.1f;

		p.vel = vec3(0, -2.0f + random_float(0, 0.05f), 0);

		p.color = vec4(fw_color.r + random_float(0, 0.1f), fw_color.g + random_float(0, 0.1f), fw_color.b + random_float(0, 0.1f), 0.95f);

		mParticles.push_back(p); // add to particles
	}
}

void MyParticleSystem::explodeParticles(int size)
{

	for (int i = 0; i < size; i++)
	{

		Particle p;
		p.pos = offset + vec3(0, -3, 0);
		p.size = 0.1f;

		p.vel = random_unit_cube();
		p.color = vec4(fw_color.r + random_float(0, 0.05f), fw_color.g + random_float(0, 0.05f), fw_color.b + random_float(0, 0.05f), 1);

		mParticles.push_back(p); // add to particles
	}
}

void MyParticleSystem::removeTrail()
{
	for (int i = 0; i < 20; i++)
	{
		mParticles[i].pos = vec3(0, 10, 0);
		mParticles[i].vel = vec3(0, 0, 0);
	}
}
void MyParticleSystem::update(float dt)
{

	if (count == 3200)
	{
		explodeParticles(100);
	}

	vec3 explosion_pos = offset + vec3(0, -3, 0);
	for (int i = 0; i < mParticles.size(); i++)
	{

		Particle p = mParticles[i];

		const glm::vec3 gravity(0, 0.2f, 0);

		p.pos += p.vel * dt;
		p.vel += gravity * dt;

		if (p.color[3] < 1 && p.pos.y <= explosion_pos.y)
		{
			p.pos = vec3(0, 10, 0);
			p.vel = vec3(0, 0, 0);
		}

		mParticles[i] = p;
	}

	for (int i = 1; i < mParticles.size(); i++)
	{

		Particle p2 = mParticles[i];
		Particle p1 = mParticles[i - 1];

		float d2 = length(theRenderer.cameraPosition() - p2.pos);
		float d1 = length(theRenderer.cameraPosition() - p1.pos);

		if (d2 > d1)
		{
			swap(mParticles[i], mParticles[i - 1]);
		}
	}
}

void MyParticleSystem::setOffset(vec3 needed_offset)
{
	offset = needed_offset;
}

void MyParticleSystem::setColor(vec3 needed_color)
{
	fw_color = needed_color;
}
