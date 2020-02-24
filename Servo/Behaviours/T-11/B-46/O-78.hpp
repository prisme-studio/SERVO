//
//  O-78.hpp
//  Talkers
//
//  Created by Valentin Dufois on 2020-02-01.
//

#ifndef O_78_hpp
#define O_78_hpp

#include "../../Output.hpp"

class O78: public Output {
public:

    O78(): Output(78,	            // Output ID
        true,	                    // Is tree end ?
        -1,	                        // Next Behaviour ID
        DELAY_DEFAULT,	            // Is delayed
        DELAY_VALUE_DEFAULT,		// Delay value (seconds)
        DELAY_VARIANCE_DEFAULT,		// Delay variance (seconds)
        {		                    // Output values
            "BODY_COUNT",
        },
        {		                    // Captions
            "",
        }) {}

    virtual bool isConditionValid(State &behaviourState) override {
        /*
        Condition: 
        */


    AKay
    };
};

#endif /* O_78_hpp */
