#ifndef ParticleSystem_H_
#define ParticleSystem_H_

#include "AGL.h"
#include "image.h"
#include "renderer.h"
#include <vector>

namespace agl {

   struct Particle {
      glm::vec3 pos;
      glm::vec3 vel;
      glm::vec4 color;
      float size;
      float mass;
   };


   class ParticleSystem {
   public:
      ParticleSystem();
      virtual ~ParticleSystem();

      void init(int size);
      virtual void update(float dt) = 0;
      virtual void draw();
      virtual void draw_fire();
      virtual void draw_smoke();
      virtual void draw_pieces();

      virtual void draw_object();
      virtual void delete_object();
      virtual void set_delay_count(int count2);
      static Renderer& GetRenderer();
      int count;


   protected:
      virtual void createParticles(int size) = 0;
   protected:

      std::vector<Particle> mParticles;
      //int delay_count;
      GLuint mTexture;
      GLuint object_texture;
      GLuint fire_texture;
      GLuint smoke_texture;
      GLuint piece_texture;
      BlendMode mBlendMode;
      static Renderer theRenderer;
   };
}
#endif