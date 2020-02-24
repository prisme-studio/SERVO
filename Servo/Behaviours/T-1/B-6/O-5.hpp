//
//  O-5.hpp
//  Talkers
//
//  Created by Valentin Dufois on 2020-02-24.
//

#ifndef O_5_hpp
#define O_5_hpp

#include "../../Output.hpp"

class O5: public Output {
public:

    O5(): Output(5,	            // Output ID
        false,	                    // Is tree end ?
        7,	                        // Next Behaviour ID
        DELAY_DEFAULT,	            // Is delayed
        DELAY_VALUE_DEFAULT,		// Delay value (seconds)
        DELAY_VARIANCE_DEFAULT,		// Delay variance (seconds)
        {		                    // Output values
        },
        {		                    // Captions
            "If they did, what was the purpose?",
        }) {}

    virtual bool isConditionValid(State &behaviourState) override {
        /*
        Condition: 
        */

        return true;
    }
};

#endif /* O_5_hpp */
