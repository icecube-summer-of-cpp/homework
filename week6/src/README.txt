Excercise
---------
Write a particle base class and a sim_particle and reco_particle derived classes. 
Along the way you'll probably want to implement direction and position classes. 
The unique_id class will likely come in handy as well.

Class design
------------

                    PARTICLE                    FOUR_VECTOR          UNIQUE_ID
                    --------                    -----------          ---------
                    + time / position           + x0, x1, x2, x3     + id    incremental number
                    + energy / momentum         - setter / getter    + process (PID)
                    + unique_id                 - ostream            + time  ns since epoch
                    + type                      - comparison         * comparison
                    - mass                      - addition           * ostream
                    - charge                    - substraction
                                                * scalar multip.
                                                * scalar prod.
            
    SIM_PARTICLE            RECO_PARTICLE
    ------------            -------------
    Parent                  Status     
    Children                GOF
    IsPrimary               shape
    Generator               vertex
                            trigger info
                            in / out going
