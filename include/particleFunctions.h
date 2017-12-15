//\===========================================================================================
//\ File: particleFunctions.h
//\ Author: Morgan James
//\ Date Created: 30/11/2017
//\ Brief: A header containing structures and functions for the use of particle creation.
//\===========================================================================================

#ifndef __PARTICLE_FUNCTIONS_H__
#define __PARTICLE_FUNCTIONS_H__

#include "gba_math.h"
#include "gba_mathUtility.h"

struct Emitter
{
	fixed fX, fY;
};

struct Particle
{
	fixed fX, fY;					//Position with 8 decimal bits
	fixed fXVelocity, fYVelocity;	//Velocity with 8 decimal bits
	u32 u32Lifespan;				//lifespan
};

void ParticleInitialization(Particle& a_rParticle, Emitter& a_rEmitter)
{
	a_rParticle.fX = 0; a_rParticle.fY = 160; a_rParticle.fXVelocity = 0; a_rParticle.fYVelocity = 0; a_rParticle.u32Lifespan = 0x1FF;
}

void JumpParticleEmit(Particle& a_rParticle, Emitter& a_rEmitter)
{
	a_rParticle.fX = a_rEmitter.fX; a_rParticle.fY = a_rEmitter.fY;
	a_rParticle.fXVelocity = IntegerToFixed(QuasiRandomRange(-5, 5)); 
	a_rParticle.fYVelocity = IntegerToFixed(20 + QuasiRandomRange(0, 5));
	a_rParticle.u32Lifespan = 0;
}
void UpdateParticleContinuous(Particle& a_rParticle, Emitter& a_rEmitter, fixed fFrameTime, fixed fPixelsToMeter, fixed fGravity)
{
	a_rParticle.fX = FixedAddition(a_rParticle.fX, FixedMultiply(FixedMultiply(a_rParticle.fXVelocity, fFrameTime), fPixelsToMeter));
	a_rParticle.fY = FixedAddition(a_rParticle.fY, FixedMultiply(FixedMultiply(a_rParticle.fYVelocity, fFrameTime), fPixelsToMeter));
	a_rParticle.fYVelocity -= FixedMultiply(fGravity, fFrameTime);
	a_rParticle.u32Lifespan += 16;

	if ((a_rParticle.fY - a_rEmitter.fY) > (40 << 8))
	{
		JumpParticleEmit(a_rParticle, a_rEmitter);
	}
}

void UpdateJumpParticleOneShot(Particle& a_rParticle, Emitter& a_rEmitter, fixed fFrameTime, fixed fPixelsToMeter, fixed fGravity)
{
	if ((a_rParticle.fY - a_rEmitter.fY) < (40 << 8) )
	{
		a_rParticle.fX = FixedAddition(a_rParticle.fX, FixedMultiply(FixedMultiply(a_rParticle.fXVelocity, fFrameTime), fPixelsToMeter));
		a_rParticle.fY = FixedAddition(a_rParticle.fY, FixedMultiply(FixedMultiply(a_rParticle.fYVelocity, fFrameTime), fPixelsToMeter));
		a_rParticle.fYVelocity -= FixedMultiply(fGravity, fFrameTime);
		a_rParticle.u32Lifespan += 16;
	}
	if ((a_rParticle.fY - a_rEmitter.fY) > (40 << 8) )
	{
		a_rParticle.u32Lifespan = 0;
	}
}

void UpdateCoinParticleOneShot(Particle& a_rParticle, Emitter& a_rEmitter, fixed fFrameTime, fixed fPixelsToMeter, fixed fGravity)
{
	if ((a_rEmitter.fY - a_rParticle.fY) < (40 << 8))
	{
		a_rParticle.fX = FixedAddition(a_rParticle.fX, FixedMultiply(FixedMultiply(a_rParticle.fXVelocity, fFrameTime), fPixelsToMeter));
		a_rParticle.fY = FixedAddition(a_rParticle.fY, FixedMultiply(FixedMultiply(a_rParticle.fYVelocity, fFrameTime), fPixelsToMeter));
		a_rParticle.fYVelocity -= FixedMultiply(fGravity, fFrameTime);
		a_rParticle.u32Lifespan += 32;
	}

	if ((a_rEmitter.fY - a_rParticle.fY) > (40 << 8))
	{
		a_rParticle.u32Lifespan = 0;
	}
	if ((a_rParticle.fY - a_rEmitter.fY) > (40 << 8))
	{
		a_rParticle.u32Lifespan = 0;
	}
}

void CoinParticleEmit(Particle& a_rParticle, Emitter& a_rEmitter)
{
	a_rParticle.fX = a_rEmitter.fX; a_rParticle.fY = a_rEmitter.fY;
	a_rParticle.fXVelocity = 0; a_rParticle.fYVelocity = IntegerToFixed(-20 + QuasiRandomRange(-0, -5));
	a_rParticle.u32Lifespan = 0;
}

#endif//__PARTICLE_FUNCTIONS_H__