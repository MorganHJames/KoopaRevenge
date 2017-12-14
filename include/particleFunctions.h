#ifndef __PARTICLE_FUNCTIONS_H__
#define __PARTICLE_FUNCTIONS_H__

#include "gba_math.h"
#include "gba_mathUtility.h"


struct Emitter
{
	fixed x, y;
};


struct Particle
{
	fixed x, y;		//Position with 8 decimal bits
	fixed vx, vy;	//Velocity with 8 decimal bits
	u32 life;		//lifespan
};


void InitParticle(Particle& a_p, Emitter& a_e)
{
	a_p.x = 0; a_p.y = 0; a_p.vx = 0; a_p.vy = 0; a_p.life = 0x1FF;

}

void EmitParticle(Particle& a_p, Emitter& a_e)
{
	a_p.x = a_e.x; a_p.y = a_e.y;
	a_p.vx = IntegerToFixed(QuasiRandomRange(-5, 5)); a_p.vy = IntegerToFixed(20 + QuasiRandomRange(0, 5));
	a_p.life = 0;
}

void UpdateParticleContinuous(Particle& a_p, Emitter& a_e, fixed g_frameTime,fixed g_pixels2Meter, fixed g_gravity)
{
	a_p.x = FixedAddition(a_p.x, FixedMultiply(FixedMultiply(a_p.vx, g_frameTime), g_pixels2Meter));
	a_p.y = FixedAddition(a_p.y, FixedMultiply(FixedMultiply(a_p.vy, g_frameTime), g_pixels2Meter));
	a_p.vy -= FixedMultiply(g_gravity, g_frameTime);
	a_p.life += 16;

	if ((a_p.y - a_e.y) > (40 << 8))
	{
		EmitParticle(a_p, a_e);
	}
}

void UpdateParticleOneShot(Particle& a_p, Emitter& a_e, fixed g_frameTime, fixed g_pixels2Meter, fixed g_gravity)
{
	if ((a_p.y - a_e.y) < (40 << 8) )
	{
		a_p.x = FixedAddition(a_p.x, FixedMultiply(FixedMultiply(a_p.vx, g_frameTime), g_pixels2Meter));
		a_p.y = FixedAddition(a_p.y, FixedMultiply(FixedMultiply(a_p.vy, g_frameTime), g_pixels2Meter));
		a_p.vy -= FixedMultiply(g_gravity, g_frameTime);
	
		a_p.life += 16;

	}
	if ((a_p.y - a_e.y) > (40 << 8) )
	{
		a_p.life = 0;
	}

}

#endif//__PARTICLE_FUNCTIONS_H__