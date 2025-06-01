#include "particlesystem.h"
#include "AGLM.h"

using namespace glm;
using namespace std;
using namespace agl;

Renderer ParticleSystem::theRenderer;

Renderer &ParticleSystem::GetRenderer()
{
    return theRenderer;
}

ParticleSystem::ParticleSystem()
{
    mBlendMode = ADD;
    mTexture = -1;
    object_texture = -1;
    fire_texture = -1;
    smoke_texture = -1;
    piece_texture = -1;
    count = 0;
}

ParticleSystem::~ParticleSystem()
{
}

void ParticleSystem::set_delay_count(int count2)
{
    count += count2;
}

void ParticleSystem::init(int size)
{
    if (!theRenderer.initialized())
    {
        theRenderer.init("shaders/billboard.vs", "shaders/billboard.fs");
    }
    // createObject();
    createParticles(size);
}

void ParticleSystem::draw_object()
{
    theRenderer.begin(object_texture, mBlendMode);

    Particle particle = mParticles[0];
    theRenderer.quad(particle.pos, particle.color, particle.size);
}

void ParticleSystem::delete_object()
{
    theRenderer.begin(mTexture, mBlendMode);
    for (int i = 0; i < mParticles.size(); i++)
    {
        Particle particle = mParticles[i];
        theRenderer.quad(particle.pos, particle.color, particle.size);
    }
}

void ParticleSystem::draw_fire()
{
    theRenderer.begin(fire_texture, mBlendMode);
    for (int i = 0; i < mParticles.size(); i++)
    {
        Particle particle = mParticles[i];
        theRenderer.fire(particle.pos, particle.color, particle.size);
    }
}

void ParticleSystem::draw_smoke()
{
    theRenderer.begin(smoke_texture, mBlendMode);
    for (int i = 0; i < mParticles.size(); i++)
    {
        Particle particle = mParticles[i];
        theRenderer.quad(particle.pos, particle.color, particle.size);
    }
}

void ParticleSystem::draw_pieces()
{
    theRenderer.begin(piece_texture, mBlendMode);
    for (int i = 0; i < mParticles.size(); i++)
    {
        Particle particle = mParticles[i];
        theRenderer.quad(particle.pos, particle.color, particle.size);
    }
}

void ParticleSystem::draw()
{
    theRenderer.begin(mTexture, mBlendMode);
    Particle particle = mParticles[0];
    theRenderer.quad(particle.pos, particle.color, particle.size);

    for (int i = 0; i < mParticles.size(); i++)
    {
        Particle particle = mParticles[i];
        theRenderer.quad(particle.pos, particle.color, particle.size);
    }
}
