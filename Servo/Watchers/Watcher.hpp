//
//  Watcher.hpp
//  Protocol Bernardo
//
//  Created by Valentin Dufois on 2019-12-07.
//

#ifndef Watcher_h
#define Watcher_h

#include <cstdlib>
#include <ctime>

#include "../main.hpp"
#include "Event.hpp"

struct Message;
class Machine;

namespace pb {
class Arena;
}

/// A watcher looks for specific behaviour/elements in a given Machine.
///
/// The watch method will effectively look over the given machine but will not tell you if it found an event. You need to call `Watcher::hasFoundEvent()` after to get the result. The result is influenced by the triggerLuck property given to the watcher on creation
class Watcher {
public:
	/// @param behaviour The behaviour to trigger when an event is found
	/// @param triggerLuck The luck percentage to prevent watchers from triggering too much.
	Watcher(Machine * aMachine, const talkers::BehaviourID behaviour, const double &triggerLuck):
		_machine(aMachine),
		_behaviour(behaviour),
		_triggerLuck(triggerLuck) {};

	/// Execute a swipe on the watched machine
	virtual void watch() = 0;

	/// Tell if the watcher found an event on its last swipe
	virtual bool hasFoundEvent() const {
		float randRes = (float)rand() / (float)RAND_MAX;
		return _foundEvent ? randRes < _triggerLuck : false;
	}

	/// Gives the event found by the watcher on its last swipe. Behaviour is up to
	/// the implementation if called when no event has been found
	virtual Event getEvent() = 0;

protected:

	/// The machine we are watching
	Machine * _machine;

	/// The behaviour to trigger when an event is found
	const talkers::BehaviourID _behaviour;

	bool _foundEvent = false;

	const double _triggerLuck = 1.0;
};

#endif /* Watcher_h */
