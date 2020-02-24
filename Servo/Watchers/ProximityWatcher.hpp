//
//  ProximityWatcher.hpp
//  Protocol Bernardo
//
//  Created by Valentin Dufois on 2019-12-08.
//

#ifndef ProximityWatcher_h
#define ProximityWatcher_h

#include "../Core/Machine.hpp"
#include <pb-common/Utils/maths.hpp>
#include <pb-common/Structs/Body.hpp>

#include "Watcher.hpp"

/// This watchers looks for people close to each others. The triggering distance is specified in the constructor
class ProximityWatcher: public Watcher {
public:
	ProximityWatcher( Machine * aMachine,
					 const talkers::BehaviourID &behaviour,
					 const pb::maths::vec2 &point,
					 const double &threshold,
					 const double &triggerLuck):
	Watcher(aMachine, behaviour, triggerLuck),
	_point(point),
	_threshold(threshold) {}

	virtual void watch() override {
		auto [body, distance] = _machine->arena()->closestTo(_point.x, _point.y);

		if(body == nullptr || distance > _threshold) {
			_foundEvent = false;
			return;
		}

		_foundEvent = true;
		_uid = body->uid;
		_distance = distance;
	}

	/// Build and give the intels corresponding to the detected event
	virtual Event getEvent() override {
		Event event;
		event.name = "PROXIMITY_ALERT";
		event.behaviour = _behaviour;
		event.values["BODY_ID"] = _uid;
		event.values["DISTANCE"] = _distance;

		return event;
	}

private:

	const pb::maths::vec2 _point;

	/// If two people are closer than this distance (in cm) then this watcher should trigger
	const double _threshold;

	pb::bodyUID _uid;
	double _distance;
};

#endif /* ClosePeopleWatcher_h */
