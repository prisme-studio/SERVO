//
//  Machine.hpp
//  pb-common (shared)
//
//  Created by Valentin Dufois on 2019-11-28.
//

#ifndef Machine_hpp
#define Machine_hpp

#include <functional>
#include <array>
#include <deque>

#include <pb-common/messages.hpp>
#include <pb-common/utils/Arena.hpp>

#include "../Watchers/Event.hpp"
#include "Tree.hpp"

struct Message;
class Behaviour;
class MachineDelegate;
class Watcher;

class Machine {
public:

	Machine(pb::Arena arena, const pb::maths::vec2 &position);

	std::string label;

	MachineDelegate * delegate = nullptr;

	// MARK: - In
	Message * onMessage(Message * message);

	/// Called when the other machine says something. does nothing excepts adding the caption to the reception history
	void storeCaption(const std::string &caption);

	// MARK: - Out

	/// Print something on the screen like this machine said something without triggering a behaviour on the other machine and retaining he focus on the current machine.
	/// If a delay is added, it will block the current thread for the specified time.
	///Printed messages are added to the other machine reception history as a way to be coherant when giving information about past exchanges
	///
	/// @param caption The message to print on the screen
	/// @param delay Delay before printing (in seconds)
	void saySomething(const std::string &caption, const double &delay = 0);

	// MARK: - Data access

	inline Tree * getTree() const {
		return _tree;
	}

	inline pb::Arena * arena() {
		return &_arena;
	}

	inline const std::vector<std::string> & receptionHistory() const {
		return _receptionHistory;
	}

	inline std::deque<Event> & eventsHistory() {
		return _events;
	}

	inline std::set<pb::bodyUID> getAllBodyUID() const {
		return _bodyUIDHistory;
	}

	::messages::Talkers * getOutputMessage();

	// MARK: - Watchers

	/// Execute all the watchers on the machine.
	///
	/// @returns True if any of the watchers found an event
	bool executeWatchers();

private:

	// MARK: - Properties

	/// The current tree this machine is in, might be null if no conversation are taking place
	Tree * _tree = nullptr;

	/// Escape road in case of an error
	void onError(const std::string &desc);

	/// The arena this machine is watching
	pb::Arena _arena;

	/// All the captions received from the other machine
	std::vector<std::string> _receptionHistory;

	/// All the event ever catched, max ~100
	std::deque<Event> _events;

	/// History of all the UID tracked by this machine.
	std::set<pb::bodyUID> _bodyUIDHistory;

	// MARK: - Watchers

	/// All the watchers
	std::array<Watcher *, 10> _watchers;
};

#endif /* Machine_hpp */
