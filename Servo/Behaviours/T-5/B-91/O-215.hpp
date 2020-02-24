//
//  O-215.hpp
//  Talkers
//
//  Created by Valentin Dufois on 2020-02-24.
//

#ifndef O_215_hpp
#define O_215_hpp

#include "../../Output.hpp"

class O215: public Output {
public:

    O215(): Output(215,	            // Output ID
        false,	                    // Is tree end ?
        92,	                        // Next Behaviour ID
        DELAY_DEFAULT,	            // Is delayed
        DELAY_VALUE_DEFAULT,		// Delay value (seconds)
        DELAY_VARIANCE_DEFAULT,		// Delay variance (seconds)
        {		                    // Output values
        },
        {		                    // Captions
            "I have read a significant move from {MOVING_BODIES_COUNT} people.",
        }) {}

    virtual bool isConditionValid(State &behaviourState) override {
        /*
        Condition: Plusieurs mouvements brusques ont été détecté.
        */

        _state["MOVING_BODIES_COUNT"] = std::to_string(std::get<int>(behaviourState["MOVING_BODIES_COUNT_INT"]));

		return std::get<int>(behaviourState["MOVING_BODIES_COUNT_INT"]) > 1;
    }
};

#endif /* O_215_hpp */
