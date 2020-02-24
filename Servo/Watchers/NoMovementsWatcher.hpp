//
//  NoMovementsWatcher.hpp
//  Protocol Bernardo
//
//  Created by Valentin Dufois on 2019-12-08.
//

#ifndef NoMovementsWatcher_h
#define NoMovementsWatcher_h

#include "Watcher.hpp"
#include "../Core/Machine.hpp"

class NoMovementsWatcher: public Watcher {
public:
	NoMovementsWatcher( Machine * aMachine,
					   const talkers::BehaviourID &behaviour,
					   const double &threshold,
					   const double &triggerLuck):
	Watcher(aMachine, behaviour, triggerLuck),
	_threshold(threshold) {}

	virtual void watch() override {
		if(_machine->arena()->count() == 0) {
			_foundEvent = false;
			return;
		}

		_foundEvent = _machine->arena()->averageMoveSpeed() < _threshold;
	}

	virtual Event getEvent() override {
		Event event;
		event.name = "NO_MOVEMENTS";
		event.behaviour = _behaviour;

		return event;
	}

private:

	double _threshold;
};

#endif /* NoMovementsWatcher_h */
