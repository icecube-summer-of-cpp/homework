Excercise
---------
Write a particle base class and a sim_particle and reco_particle derived classes. 
Along the way you'll probably want to implement direction and position classes. 
The unique_id class will likely come in handy as well.

Class design
------------

                    PARTICLE                    FOUR_VECTOR          UNIQUE_ID
                    --------                    -----------          ---------
                    + direction                 + x0, x1, x2, x3     + id    incremental number
                    + position                  - setter             + process (PID)
                    + unique_id                 - getter             + time  ns since epoch
                    + energy                    - +=                 * ==
                    + momentum                  - -=                 * !=
                    + mass                      - *=                 * <<
                    + type                      * <<
                    + charge                    * +
                    + quantum numbers		    * -
						                        * *
                                                * ==
                                                * !=
            
    SIM_PARTICLE            RECO_PARTICLE
    ------------            -------------
    Parent                  Status     
    Children                GOF
    IsPrimary               shape
    Generator               vertex
                            trigger info
                            in / out going
