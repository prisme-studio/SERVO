//
//  NewBodyWatcher.hpp
//  Protocol Bernardo
//
//  Created by Valentin Dufois on 2020-02-03.
//

#ifndef NewBodyWatcher_h
#define NewBodyWatcher_h

#include "../Core/Machine.hpp"
#include "Watcher.hpp"

class NewBodyWatcher: public Watcher {
public:
	NewBodyWatcher( Machine * aMachine,
				   const talkers::BehaviourID &behaviour,
				   const double &triggerLuck):
	Watcher(aMachine, behaviour, triggerLuck) {}

	virtual void watch() override {
		size_t bodyCount = _machine->receptionHistory().size();

		_foundEvent = bodyCount > _lastCount;

		_lastCount = bodyCount;
	}

	virtual Event getEvent() override {
		Event event;
		event.name = "NEW_BODY";
		event.behaviour = _behaviour;

		return event;
	}

private:

	size_t _lastCount = 0;
};

#endif /* NewBodyWatcher_h */
