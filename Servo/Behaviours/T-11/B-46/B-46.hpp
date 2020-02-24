//
//  B-46.hpp
//  Talkers
//
//  Created by Valentin Dufois on 2020-02-01.
//

#ifndef B_46_hpp
#define B_46_hpp

#include "../../Behaviour.hpp"

class B46: public Behaviour {
public:
    B46(): Behaviour(46,	// ID
        11,		            // Tree ID
        1,	                // Is tree start ?
        0,	                // Force start ?
        {		            // Expected inputs
            "BODY_COUNT",
        },
        {		            // Expected outputs
            78,
    }) {}

    virtual bool execute(Machine * machine) override {
        /*
        Action: 
        */

                    yo
            }
};


#endif /* B_46_hpp */
