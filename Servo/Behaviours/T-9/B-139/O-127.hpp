//
//  O-127.hpp
//  Talkers
//
//  Created by Valentin Dufois on 2020-02-24.
//

#ifndef O_127_hpp
#define O_127_hpp

#include "../../Output.hpp"

class O127: public Output {
public:

    O127(): Output(127,	            // Output ID
        false,	                    // Is tree end ?
        141,	                        // Next Behaviour ID
        DELAY_DEFAULT,	            // Is delayed
        DELAY_VALUE_DEFAULT,		// Delay value (seconds)
        DELAY_VARIANCE_DEFAULT,		// Delay variance (seconds)
        {		                    // Output values
            "TOTAL_BODIES_COUNT",
        },
        {		                    // Captions
            "Until now, I have counted just one person in the entire room.",
        }) {}

    virtual bool isConditionValid(State &behaviourState) override {
        /*
        Condition: Une seule personne détecté
        */

        _state["TOTAL_BODIES_COUNT"] = behaviourState["TOTAL_BODIES_COUNT_INT"];
		_state["TOTAL_BODIES_COUNT_STR"] = std::to_string(std::get<int>(behaviourState["TOTAL_BODIES_COUNT_INT"]));
		return std::get<int>(behaviourState["TOTAL_BODIES_COUNT_INT"]) <= 1;
    }
};

#endif /* O_127_hpp */
