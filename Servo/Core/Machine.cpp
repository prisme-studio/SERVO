//
//  Machine.cpp
//  pb-common (shared)
//
//  Created by Valentin Dufois on 2019-11-28.
//

#include <thread>
#include <iostream>
#include <cstdlib>

#include "Machine.hpp"
#include "MachineDelegate.hpp"

// Watchers
#include "../Watchers/ClosePeopleWatcher.hpp"
#include "../Watchers/NewBodyWatcher.hpp"
#include "../Watchers/ProximityWatcher.hpp"
#include "../Watchers/NoMovementsWatcher.hpp"
#include "../Watchers/RandomWatcher.hpp"
#include "../Watchers/SuddenMoveWatcher.hpp"

#include <pb-common/messages.hpp>

#include "../Behaviours/Output.hpp"
#include "../Behaviours/Behaviour.hpp"
#include "../Behaviours/Message.hpp"

Machine::Machine(pb::Arena arena, const pb::maths::vec2 &position):
	_arena(arena),
	_watchers({
		new NoMovementsWatcher(this, 1, 100, 0.01),				// T-01
		new ClosePeopleWatcher(this, 11, 8000, 0.1),				// T-02
		new SuddenMoveWatcher(this, 18, 5000, 0.1),				// T-03
		new NewBodyWatcher(this, 22, 0.1),						// T-04
		new RandomWatcher(this, 50, 0.01),						// T-05
		new RandomWatcher(this, 99, 0.01),						// T-06
		new ProximityWatcher(this, 128, position, 1000, 0.01),		// T-07
		new RandomWatcher(this, 139, 0.01),						// T-09
		new RandomWatcher(this, 158, 0.01),						// T-11
		new ClosePeopleWatcher(this, 177, 8000, 0.01),				// T-13
	}) {}

// MARK: - Inputs

Message * Machine::onMessage(Message * message) {
	if(message == nullptr)
		return nullptr;

	// Remember the message
	storeCaption(message->caption);

	if(message->isTreeEnd && _tree != nullptr) {
		delete _tree;
		_tree = nullptr;
	}

	// Check behaviour value
	if(message->behaviour == -1) {
		delegate->machineDidUpdate(this);
		return nullptr;
	}

	// Get the message behaviour
	Behaviour * behaviour = Behaviour::get(message->behaviour);

	// Do we have a valid behaviour ?
	if(behaviour == nullptr) {
		onError("Invalid behaviour ID : " + std::to_string(message->behaviour));
		return nullptr;
	}

	// Ar we changing tree ?
	if(_tree != nullptr && behaviour->forceStart) {
		delete _tree;
		_tree = new Tree(behaviour->treeID);
	} else if(_tree == nullptr) {
		_tree = new Tree(behaviour->treeID);
	}

	if(_tree->id != behaviour->treeID) {
		onError("Routing error on tree #" + std::to_string(_tree->id) + " and behaviour #" + std::to_string(behaviour->id));
		delete behaviour;
		delete _tree;
		_tree = nullptr;
		return nullptr;
	}

	if(!behaviour->importMessage(message)) {
		onError("Error while importing message on behaviour " + std::to_string(behaviour->id));
		delete behaviour;
		return nullptr;
	}

	if(!behaviour->execute(this)) {
		onError("Error while executing behaviour " + std::to_string(behaviour->id));
		delete behaviour;
		return nullptr;
	}

	// Get the behaviour results
	Output * output = behaviour->getOutput();

	if(output == nullptr) {
		// No output, end here
		return nullptr;
	}
	
	Message * outMessage = output->getMessage();

	if(output->isTreeEnd) {
		delete _tree;
		_tree = nullptr;
	}

	// Send the message and pause the thread as needed
	saySomething(outMessage->caption, output->getDelay());

	delete output;

	// Return the message so it can be sent to the other machine
	return outMessage;
}

void Machine::storeCaption(const std::string &caption) {
	_receptionHistory.push_back(caption);
}

void Machine::saySomething(const std::string &caption, const double &aDelay) {
	// Pause the thread if needed
	std::chrono::duration<double, std::ratio<1>> delay(aDelay);
	std::this_thread::sleep_for(delay);

	std::cout << "[" << label << "] " << caption << std::endl;

	delegate->machineSaysSomething(this, caption);
}

messages::Talkers * Machine::getOutputMessage() {
	messages::Talkers * message = new messages::Talkers();

	// Set label
	message->set_label(this->label);

	// Add the machine state
	message->set_bodycount((int)_arena.count());
	message->set_averageactivity(_arena.averageMoveSpeed());
	message->set_maximumactivity(std::get<1>(_arena.mostActiveBody()));
	message->set_tree(_tree != nullptr);

	return message;
}

// MARK: - Watchers

bool Machine::executeWatchers() {
	// Store UIDS
	for(pb::Body * body: arena()->getSubset()) {
		_bodyUIDHistory.insert(body->uid);
	}

	delegate->machineDidUpdate(this);

	// Execute each watchers
	for(Watcher * watcher: _watchers) {
		watcher->watch();

		if(!watcher->hasFoundEvent())
			continue;

		Event event = watcher->getEvent();
		_events.push_back(event);

		// Keep only the last 100 events
		if(_events.size() > 100)
			_events.pop_front();

		if(_tree == nullptr) {
			// Dispatch
			delegate->machineExecuteEvent(this, event);
			return true;
		}
	}

	return false;
}

// MARK: - Properties

void Machine::onError(const std::string &desc) {
	std::cout << "[" << label << "] " << "*** Error";
	std::cout << "[" << label << "] " << desc;
	std::cout << "[" << label << "] " << "*********";
}
