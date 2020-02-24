//
//  RandomWatcher.hpp
//  Talkers
//
//  Created by Valentin Dufois on 2019-12-08.
//

#ifndef RandomWatcher_h
#define RandomWatcher_h

#include "Watcher.hpp"

class RandomWatcher: public Watcher {
public:
	RandomWatcher( Machine * aMachine,
				  const talkers::BehaviourID &behaviour,
				  const double &triggerLuck):
	Watcher(aMachine, behaviour, triggerLuck) {
		_foundEvent = true;
	}

	virtual void watch() override {
		return;
	}

	virtual Event getEvent() override {
		Event event;
		event.name = "RANDOM_EVENT";
		event.behaviour = _behaviour;

		return event;
	}

private:

};

#endif /* RandomWatcher_h */
