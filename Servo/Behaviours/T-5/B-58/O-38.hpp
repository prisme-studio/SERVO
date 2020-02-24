//
//  O-38.hpp
//  Talkers
//
//  Created by Valentin Dufois on 2020-02-24.
//

#ifndef O_38_hpp
#define O_38_hpp

#include "../../Output.hpp"

class O38: public Output {
public:

    O38(): Output(38,	            // Output ID
        false,	                    // Is tree end ?
        60,	                        // Next Behaviour ID
        true,	            // Is delayed
        10,		// Delay value (seconds)
        2,		// Delay variance (seconds)
        {		                    // Output values
        },
        {		                    // Captions
            "Did you get an answer?",
        }) {}

    virtual bool isConditionValid(State &behaviourState) override {
        /*
        Condition: 
        */

        return true;
    }
};

#endif /* O_38_hpp */
