Excercise
---------
Write a particle base class and a sim_particle and reco_particle derived classes. 
Along the way you'll probably want to implement direction and position classes. 
The unique_id class will likely come in handy as well.

Class design
------------

constructor, assignment, move, destructor, comparison, getter, setters, tests, comments, printing, functionallity

FOUR_VECTOR


                    PARTICLE                    DIRECTION               POSITION                    UNIQUE_ID
                    --------                    ---------               --------                    ---------
                    + direction                 + zenith                + x, y, z                   + process (PID)
                    + position                  + azimuth               + relative to               + host (IP/hostname/MAC)
                    
                    + unique_id                 - setter                * distance to (position)    + time  ns since epoch
                    + energy                    - getter                                            + id    incremental number
                    + momentum                  - getter other formats
                    + mass                      - setter other formats
                    + type                      * addition
                    + charge                    * substraction
                    + quantum numbers
                
            
    SIM_PARTICLE            RECO_PARTICLE
    ------------            -------------
    Parent                  Status     
    Children                GOF
    IsPrimary               shape
    Generator               vertex
                            trigger info
                            in / out going
