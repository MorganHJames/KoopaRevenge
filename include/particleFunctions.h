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

struct Emitter//A structure for an emitter of which particles will emit from.
{
	fixed fX, fY;//The x and y position for the emitter.
};

struct Particle//A structure for a particle of which will be emitted from an emitter.
{
	fixed fX, fY;//Position for the particle.
	fixed fXVelocity, fYVelocity;//Velocity for the particle.
	u32 u32Lifespan;//The lifespan of the particle.
};

void ParticleInitialization(Particle& a_rParticle, Emitter& a_rEmitter)//Initializes a particle.
{
	a_rParticle.fX = 0; a_rParticle.fY = 160; a_rParticle.fXVelocity = 0; a_rParticle.fYVelocity = 0; a_rParticle.u32Lifespan = 0x1FF;//Sets all the values of the particle.
}

void JumpParticleEmit(Particle& a_rParticle, Emitter& a_rEmitter)//The emit function for the jump particle effect.
{
	a_rParticle.fX = a_rEmitter.fX;//Sets the x position of the particle to be equal to that of the emitters.
	a_rParticle.fY = a_rEmitter.fY;//Sets the y position of the particle to be equal to that of the emitters.
	a_rParticle.fXVelocity = IntegerToFixed(QuasiRandomRange(-5, 5));//Sets the velocity in the horizontal direction to be that of a random variable.
	a_rParticle.fYVelocity = IntegerToFixed(20 + QuasiRandomRange(0, 5));//Sets the velocity in the vertical direction to be that of a random positive variable.
	a_rParticle.u32Lifespan = 0;//Sets the lifespan of the particle to be equal to 0.
}

void CoinParticleEmit(Particle& a_rParticle, Emitter& a_rEmitter)//The emit function for the coin particle effect.
{
	a_rParticle.fX = a_rEmitter.fX;//Sets the x position of the particle to be equal to that of the emitters. 
	a_rParticle.fY = a_rEmitter.fY;//Sets the y position of the particle to be equal to that of the emitters.
	a_rParticle.fXVelocity = 0;//Sets the horizontal velocity to be 0.
	a_rParticle.fYVelocity = IntegerToFixed(-20 + QuasiRandomRange(0, -5));//Sets the velocity in the vertical direction to be that of a random negative variable.
	a_rParticle.u32Lifespan = 0;//Sets the lifespan of the particle to be equal to 0.
}

void UpdateJumpParticleContinuous(Particle& a_rParticle, Emitter& a_rEmitter, fixed fFrameTime, fixed fPixelsToMeter, fixed fGravity)//A function to have a continuous particle emitting after the player jumped if i so wanted to use it.
{
	a_rParticle.fX = FixedAddition(a_rParticle.fX, FixedMultiply(FixedMultiply(a_rParticle.fXVelocity, fFrameTime), fPixelsToMeter));//Sets the x position of the particle to be that of the horizontal velocity multiplied by distance.
	a_rParticle.fY = FixedAddition(a_rParticle.fY, FixedMultiply(FixedMultiply(a_rParticle.fYVelocity, fFrameTime), fPixelsToMeter));//Sets the y position of the particle to be that of the vertical velocity multiplied by distance.
	a_rParticle.fYVelocity -= FixedMultiply(fGravity, fFrameTime);//Decreases the vertical velocity so that it starts fast then diminishes.
	a_rParticle.u32Lifespan += 16;//Increases the lifespan of the particle.

	if ((a_rParticle.fY - a_rEmitter.fY) > (40 << 8))//If the particle has traveled 40 pixels.
	{
		JumpParticleEmit(a_rParticle, a_rEmitter);//Emit the particle again.
	}
}

void UpdateJumpParticleOneShot(Particle& a_rParticle, Emitter& a_rEmitter, fixed fFrameTime, fixed fPixelsToMeter, fixed fGravity)//A function to have a particle emit after the player jumps.
{
	if ((a_rParticle.fY - a_rEmitter.fY) < (40 << 8) )//If the particle hasn't traveled 40 pixels.
	{
		a_rParticle.fX = FixedAddition(a_rParticle.fX, FixedMultiply(FixedMultiply(a_rParticle.fXVelocity, fFrameTime), fPixelsToMeter));//Sets the x position of the particle to be that of the horizontal velocity multiplied by distance.
		a_rParticle.fY = FixedAddition(a_rParticle.fY, FixedMultiply(FixedMultiply(a_rParticle.fYVelocity, fFrameTime), fPixelsToMeter));//Sets the y position of the particle to be that of the vertical velocity multiplied by distance.
		a_rParticle.fYVelocity -= FixedMultiply(fGravity, fFrameTime);//Decreases the vertical velocity so that it starts fast then diminishes.
		a_rParticle.u32Lifespan += 16;//Increases the lifespan of the particle.
	}
	if ((a_rParticle.fY - a_rEmitter.fY) > (40 << 8) )//If the particle has traveled 40 pixels.
	{
		a_rParticle.u32Lifespan = 0;//Set the lifespan of the particle to 0.
	}
}

void UpdateCoinParticleOneShot(Particle& a_rParticle, Emitter& a_rEmitter, fixed fFrameTime, fixed fPixelsToMeter, fixed fGravity)//A function to have a particle emit after the player lands on a enemy.
{
	if ((a_rEmitter.fY - a_rParticle.fY) < (40 << 8))//If the particle hasn't traveled 40 pixels.
	{
		a_rParticle.fX = FixedAddition(a_rParticle.fX, FixedMultiply(FixedMultiply(a_rParticle.fXVelocity, fFrameTime), fPixelsToMeter));
		a_rParticle.fY = FixedAddition(a_rParticle.fY, FixedMultiply(FixedMultiply(a_rParticle.fYVelocity, fFrameTime), fPixelsToMeter));
		a_rParticle.fYVelocity -= FixedMultiply(fGravity, fFrameTime);//Decreases the vertical velocity so that it starts fast then diminishes.
		a_rParticle.u32Lifespan += 32;//Increases the lifespan of the particle.
	}

	if ((a_rEmitter.fY - a_rParticle.fY) > (40 << 8))//If the particle has traveled 40 pixels.
	{
		a_rParticle.u32Lifespan = 0;//Set the lifespan of the particle to 0.
	}
	if ((a_rParticle.fY - a_rEmitter.fY) > (40 << 8))//If the particle has traveled 40 pixels.
	{
		a_rParticle.u32Lifespan = 0;//Set the lifespan of the particle to 0.
	}
}

#endif//__PARTICLE_FUNCTIONS_H__