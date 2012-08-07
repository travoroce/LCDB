/////////////////////////////////////////////////////////////////////////////////
//
// Thor C++ Library
// Copyright (c) 2011-2012 Jan Haller
// 
// This software is provided 'as-is', without any express or implied
// warranty. In no event will the authors be held liable for any damages
// arising from the use of this software.
// 
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it
// freely, subject to the following restrictions:
// 
// 1. The origin of this software must not be misrepresented; you must not
//    claim that you wrote the original software. If you use this software
//    in a product, an acknowledgment in the product documentation would be
//    appreciated but is not required.
// 
// 2. Altered source versions must be plainly marked as such, and must not be
//    misrepresented as being the original software.
// 
// 3. This notice may not be removed or altered from any source distribution.
//
/////////////////////////////////////////////////////////////////////////////////

#include <cassert>


namespace thor
{

template <class Animated, typename Id>
Animator<Animated, Id>::Animator()
: mAnimationMap()
, mPlayingAnimation(nullptr)
, mDefaultAnimation()
, mProgress(0.f)
, mLoop(false)
{
}

template <class Animated, typename Id>
void Animator<Animated, Id>::addAnimation(const Id& id, const AnimationFunction& animation, sf::Time duration)
{
	assert(mAnimationMap.find(id) == mAnimationMap.end());
	mAnimationMap.insert( std::make_pair(id, ScaledAnimation(animation, duration)) );
}

template <class Animated, typename Id>
void Animator<Animated, Id>::playAnimation(const Id& id, bool loop)
{
	typename AnimationMap::iterator itr = mAnimationMap.find(id);
	assert(itr != mAnimationMap.end());

	playAnimation(itr->second, loop);
}

template <class Animated, typename Id>
void Animator<Animated, Id>::stopAnimation()
{
	// Animations stopped: Play default animation if available
	if (mDefaultAnimation.first)
		playAnimation(mDefaultAnimation, true);
	else
		mPlayingAnimation = nullptr;
}

template <class Animated, typename Id>
bool Animator<Animated, Id>::isPlayingAnimation() const
{
	return mPlayingAnimation != nullptr
		&& mPlayingAnimation != &mDefaultAnimation;
}

template <class Animated, typename Id>
void Animator<Animated, Id>::update(sf::Time dt)
{
	// No animation playing (no default animation available): Do nothing
	if (!mPlayingAnimation)
		return;

	// Update progress, scale dt with 1 / current animation duration
	mProgress += dt.asSeconds() / mPlayingAnimation->second.asSeconds();

	// If animation is expired, stop or restart animation at loops
	if (mProgress > 1.f)
	{
		if (mLoop)
			mProgress -= 1.f;
		else
			stopAnimation();
	}
}

template <class Animated, typename Id>
void Animator<Animated, Id>::animate(Animated& animated) const
{
	// If animation is playing, apply it (includes default animation, if others are stopped)
	if (mPlayingAnimation)
		mPlayingAnimation->first(animated, mProgress);
}

template <class Animated, typename Id>
void Animator<Animated, Id>::playAnimation(ScaledAnimation& animation, bool loop)
{
	mPlayingAnimation = &animation;
	mProgress = 0.f;
	mLoop = loop;
}

template <class Animated, typename Id>
void Animator<Animated, Id>::setDefaultAnimation(const AnimationFunction& animation, sf::Time duration)
{
	// Invalidate old playing animation, if it refers to default animation (which might be destroyed)
	if (mPlayingAnimation == &mDefaultAnimation)
		mPlayingAnimation = nullptr;

	// Assign animation and duration
	mDefaultAnimation.first = animation;
	mDefaultAnimation.second = duration;

	// If no other animation is active, play default animation
	if (!mPlayingAnimation)
		stopAnimation();
}

} // namespace thor
