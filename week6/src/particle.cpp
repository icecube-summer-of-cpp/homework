#include "particle.hpp"

// test particle

/* constructor, assignment, move, destructor, comparison, getter, setters, tests, comments, printing, functionallity
 * 
 * PARTICLE
 * --------
 * + position 
 * + time
 * + energy
 * + momentum
 * + unique_id
 * + quantum numbers
 * - direction
 * - mass
 * - type
 * - charge
 * 
 */
 
enum class fit_status {ok, failed, partial};
enum class sim_particle {primary, cascade_segment, dark};
enum class reco_particle {inice, };
