/** $Id: SimplePropagator.h 150208 2016-09-21 11:32:47Z tfuchs $
 * @file
 * @author Jakob van Santen <vansanten@wisc.edu>
 *
 * $Revision: 150208 $
 * $Date: 2016-09-21 13:32:47 +0200 (Mi, 21. Sep 2016) $
 */

#ifndef PROPOSAL_SIMPLEPROPAGATOR_H_INCLUDED
#define PROPOSAL_SIMPLEPROPAGATOR_H_INCLUDED

#include <boost/shared_ptr.hpp>

#include "icetray/I3Units.h"
#include "dataclasses/physics/I3Particle.h"
#include "phys-services/I3RandomService.h"

#include "PROPOSAL/PROPOSAL.h"

/**
 * @brief A simple muon energy-loss calculator
 *
 * This hides the nasty details of PROPOSAL (a C++ translation of MMC)
 */
class SimplePropagator {
public:
  /**
   * @param[in] medium The Type of the medium, e.g. MediumType::Ice
   * @param[in] type   The Type of particles to propagate e.g.
   * I3Particle::MuMinus
   * @param[in] ecut   Absolute energy above which an energy
   *                   loss is considered stochastic @f$ [MeV] @f$
   * @param[in] vcut   Proportion of the current muon energy above
   *                   which an energy loss is considered stochastic
   * @param[in] rho    Density adjustment factor for the medium
   */
  SimplePropagator(I3Particle::ParticleType type = I3Particle::MuMinus,
                   const std::string& med = "ice", double ecut = -1, double vcut = -1,
                   double rho = 1.0);
  ~SimplePropagator();
  /**
   * @param[in] p        Muon to propagate
   * @param[in] distance Maximum distance to propagate
   * @returns an I3Particle representing the muon at the end
   *          of propagation. If the muon stopped before the
   *          given distance, the energy will be set to zero.
   *          The length of the output I3Particle is the
   *          distance traveled to reach its current position
   *          from the position given as input.
   */
  I3Particle propagate(const I3Particle &p, double distance,
                       boost::shared_ptr<std::vector<I3Particle>> losses =
                           boost::shared_ptr<std::vector<I3Particle>>());

  /**
   * Set the (global) state of the random number generator used
   * in the implementation.
   */
  void SetSeed(int seed);

  /**
   * Use a specific random number generator for this instance
   */
  void SetRandomNumberGenerator(I3RandomServicePtr rng);
  /**
   * Get the internal MMC name associated with a particle type
   */
  static I3Particle to_I3Particle(const PROPOSAL::DynamicData &);
  // static ParticleType::Enum GeneratePROPOSALType(const I3Particle &p);
  static I3Particle::ParticleType GenerateI3Type(const PROPOSAL::DynamicData &);

  PROPOSAL::Propagator *GetImplementation() { return propagator_; };

private:
  PROPOSAL::Propagator *propagator_;
};

#endif // PROPOSAL_SIMPLEPROPAGATOR_H_INCLUDED
