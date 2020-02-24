//
//  O-99.hpp
//  Talkers
//
//  Created by Valentin Dufois on 2020-02-24.
//

#ifndef O_99_hpp
#define O_99_hpp

#include "../../Output.hpp"

class O99: public Output {
public:

    O99(): Output(99,	            // Output ID
        false,	                    // Is tree end ?
        116,	                        // Next Behaviour ID
        DELAY_DEFAULT,	            // Is delayed
        DELAY_VALUE_DEFAULT,		// Delay value (seconds)
        DELAY_VARIANCE_DEFAULT,		// Delay variance (seconds)
        {		                    // Output values
        },
        {		                    // Captions
            "Indeed.",
        }) {}

    virtual bool isConditionValid(State &behaviourState) override {
        /*
        Condition: 
        */

        return true;
    }
};

#endif /* O_99_hpp */
