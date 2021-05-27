#ifndef MyParticleSystem_H_
#define MyParticleSystem_H_

#include "particlesystem.h"

namespace agl {

   class MyParticleSystem : public ParticleSystem {
   public:
      virtual void createParticles(int size) override;


      virtual void update(float dt) override;

      void setOffset(glm::vec3 needed_offset);
      void setColor(glm::vec3 needed_color);
      void explodeParticles(int size);
      void removeTrail();


   public:
       glm::vec3 offset;
       glm::vec3 fw_color;
   };
}
#endif