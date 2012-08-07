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

/// @file
/// @brief Class template thor::Animator

#ifndef THOR_ANIMATOR_HPP
#define THOR_ANIMATOR_HPP

#include <Thor/Config.hpp>

#include <SFML/System/Time.hpp>

#include <map>
#include <functional>


namespace thor
{

/// @addtogroup Animation
/// @{

/// @brief Class that stores the progress of an object's animation.
/// @details The Animator class takes care of multiple animations which are registered by a ID. The animations can be played
///  at any time. Animator updates their progress and applies it to animated objects.
template <class Animated, typename Id>
class Animator
{
	// ---------------------------------------------------------------------------------------------------------------------------
	// Public types
	public:
		/// @brief Functor to animate the objects.
		/// @details Signature: <b>void (Animated& animated, float progress)</b>
		///  @arg @a animated is the object being animated.
		///  @arg @a progress is a number in [0,1] determining the animation state.
		typedef std::function<void(Animated&, float)>	AnimationFunction;

		
	// ---------------------------------------------------------------------------------------------------------------------------
	// Public member functions
	public:
		/// @brief Default constructor
		/// 
									Animator();

		/// @brief Registers an animation with a given name.
		/// @param id Value that identifies the animation (must not be registered yet).
		/// @param animation Animation to add to the animator.
		/// @param duration Duration of the animation.
		void						addAnimation(const Id& id, const AnimationFunction& animation, sf::Time duration);

		/// @brief Plays the animation with the given name.
		/// @param id Value that identifies the animation (must already be registered).
		/// @param loop True if the animation is played repeatedly.
		void						playAnimation(const Id& id, bool loop = false);

		/// @brief Interrupts the animation that is currently active.
		/// @details If a default animation has been specified, it is shown. Otherwise, the last visible frame of the stopped
		///  animation is shown.
		void						stopAnimation();

		/// @brief Checks whether an animation is currently playing.
		/// @details Returns true after an animation has been started with playAnimation(), as long as it has not ended. 
		///  If none or the default animation is playing, false is returned.
		bool						isPlayingAnimation() const;

		/// @brief Updates the animator's progress. You should call this method each frame.
		/// @param dt Frame time.
		void						update(sf::Time dt);

		/// @brief Applies the stored animations to an object.
		/// @param animated Object which is animated by the current animation. If no animation is active, the default animation
		///  is applied (if specified), otherwise the object is left unchanged.
		void						animate(Animated& animated) const;

		/// @brief Sets an animation that is active when all others are stopped.
		/// @param animation Default animation to set. Will be played in a loop if no other animation is currently active.
		///  @a animation can be empty to reset the default animation. In this case, the object is not affected when
		///  no animation is playing.
		/// @param duration Duration of the animation.
		void						setDefaultAnimation(const AnimationFunction& animation, sf::Time duration);


	// ---------------------------------------------------------------------------------------------------------------------------
	// Private types
	private:
		typedef std::pair<AnimationFunction, sf::Time>		ScaledAnimation;
		typedef std::map<Id, ScaledAnimation>				AnimationMap;


	// ---------------------------------------------------------------------------------------------------------------------------
	// Private member functions
	private:
		void						playAnimation(ScaledAnimation& animation, bool loop);

			
	// ---------------------------------------------------------------------------------------------------------------------------
	// Private variables
	private:
		AnimationMap				mAnimationMap;
		const ScaledAnimation*		mPlayingAnimation;
		ScaledAnimation				mDefaultAnimation;
		float						mProgress;
		bool						mLoop;
};

/// @}

} // namespace thor

#include <Thor/Animation/Detail/Animator.inl>
#endif // THOR_ANIMATOR_HPP
