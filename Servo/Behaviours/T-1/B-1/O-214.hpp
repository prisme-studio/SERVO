//
//  O-214.hpp
//  Talkers
//
//  Created by Valentin Dufois on 2020-02-24.
//

#ifndef O_214_hpp
#define O_214_hpp

#include "../../Output.hpp"

class O214: public Output {
public:

    O214(): Output(214,	            // Output ID
        false,	                    // Is tree end ?
        3,	                        // Next Behaviour ID
        DELAY_DEFAULT,	            // Is delayed
        DELAY_VALUE_DEFAULT,		// Delay value (seconds)
        DELAY_VARIANCE_DEFAULT,		// Delay variance (seconds)
        {		                    // Output values
        },
        {		                    // Captions
            "Although I detect {BODY_COUNT} people, I do not detect motion.",
        }) {}

    virtual bool isConditionValid(State &behaviourState) override {
        /*
        Condition: 
        */

        _state["BODY_COUNT"] = std::to_string(std::get<int>(behaviourState["BODY_COUNT_INT"]));
		return std::get<int>(behaviourState["BODY_COUNT_INT"]) > 1;
    }
};

#endif /* O_214_hpp */
