#include "AGL.h"
#include "AGLM.h"
#include <cmath>
#include "myparticlesystem.h"
#include <algorithm>

using namespace std;
using namespace agl;
using namespace glm;

vec3 offset = vec3(0);
vec3 color = random_unit_cube();

vec3 lastTrailPos = vec3(0); // 🔸 Added: to store explosion position

void MyParticleSystem::createParticles(int size)
{
	fire_texture = theRenderer.loadTexture("textures/ParticleFirecloud.png");

	for (int i = 0; i < 20; i++)
	{
		Particle p;
		p.pos = offset;
		p.pos.y = offset.y + random_float(0, 0.05f);
		p.size = 0.1f;
		p.vel = vec3(0, -2.0f + random_float(0, 2.0f), 0);
		p.color = vec4(fw_color.r + random_float(0, 0.1f),
					   fw_color.g + random_float(0, 0.1f),
					   fw_color.b + random_float(0, 0.1f), 0.95f);

		mParticles.push_back(p); // Add trail particles
	}
}

void MyParticleSystem::explodeParticles(int size)
{
	mParticles.clear(); // Clear existing particles before explosion

	for (int i = 0; i < size; i++)
	{
		Particle p;
		p.pos = lastTrailPos; // 🔸 Use actual trail tip position
		p.size = 0.1f;
		p.vel = normalize(random_unit_cube()) * random_float(0.5f, 1.5f);
		p.color = vec4(fw_color.r + random_float(0, 0.05f),
					   fw_color.g + random_float(0, 0.05f),
					   fw_color.b + random_float(0, 0.05f), 1.0f);

		mParticles.push_back(p); // Explosion particles
	}
}

void MyParticleSystem::removeTrail()
{
	for (int i = 0; i < 20 && i < mParticles.size(); i++)
	{
		mParticles[i].pos = vec3(0, 10, 0); // Move out of view
		mParticles[i].vel = vec3(0);
		mParticles[i].color.a = 0.0f; // Fully transparent
	}
}

void MyParticleSystem::update(float dt)
{
	count++;

	// 🔸 Track last trail particle's position for explosion
	if (!mParticles.empty())
		lastTrailPos = mParticles[19].pos;

	if (count == 3200)
	{
		explodeParticles(100);
	}

	vec3 explosion_pos = offset + vec3(0, -3, 0);
	vec3 gravity = vec3(0, -9.81f, 0) * dt; // Simple gravity effect
	for (int i = 0; i < mParticles.size(); i++)
	{
		Particle &p = mParticles[i];

		p.pos += p.vel * dt;
		p.vel += gravity * dt;

		if (p.color[3] < 1 && p.pos.y <= explosion_pos.y)
		{
			p.pos = vec3(0, 10, 0);
			p.vel = vec3(0, 0, 0);
		}

		mParticles[i] = p;
	}

	// 🔸 Sort particles for correct rendering
	std::sort(mParticles.begin(), mParticles.end(), [](const Particle &a, const Particle &b)
			  {
				  float da = length(theRenderer.cameraPosition() - a.pos);
				  float db = length(theRenderer.cameraPosition() - b.pos);
				  return da > db; // Farther drawn first
			  });
}

void MyParticleSystem::setOffset(vec3 needed_offset)
{
	offset = needed_offset;
}

void MyParticleSystem::setColor(vec3 needed_color)
{
	fw_color = needed_color;
}
