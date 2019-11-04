
/******************************************************************************
 *                                                                            *
 * This file is part of the simulation tool PROPOSAL.                         *
 *                                                                            *
 * Copyright (C) 2017 TU Dortmund University, Department of Physics,          *
 *                    Chair Experimental Physics 5b                           *
 *                                                                            *
 * This software may be modified and distributed under the terms of a         *
 * modified GNU Lesser General Public Licence version 3 (LGPL),               *
 * copied verbatim in the file "LICENSE".                                     *
 *                                                                            *
 * Modifcations to the LGPL License:                                          *
 *                                                                            *
 *      1. The user shall acknowledge the use of PROPOSAL by citing the       *
 *         following reference:                                               *
 *                                                                            *
 *         J.H. Koehne et al.  Comput.Phys.Commun. 184 (2013) 2070-2090 DOI:  *
 *         10.1016/j.cpc.2013.04.001                                          *
 *                                                                            *
 *      2. The user should report any bugs/errors or improvments to the       *
 *         current maintainer of PROPOSAL or open an issue on the             *
 *         GitHub webpage                                                     *
 *                                                                            *
 *         "https://github.com/tudo-astroparticlephysics/PROPOSAL"            *
 *                                                                            *
 ******************************************************************************/


#pragma once
#include <utility>
#include <memory>

namespace PROPOSAL {

class Particle;
class Utility;
class Vector3D;

class Scattering
{
public:
    Scattering(Particle&);
    Scattering(const Scattering&);
    virtual ~Scattering();

    bool operator==(const Scattering& scattering) const;
    bool operator!=(const Scattering& scattering) const;

    virtual Scattering* clone() const                          = 0; // virtual constructor idiom (used for deep copies)
    virtual Scattering* clone(Particle&, const Utility&) const = 0; // virtual constructor idiom (used for deep copies)

    std::shared_ptr<std::pair<Vector3D, Vector3D>> Scatter(double dr, double ei, double ef);

    const Particle& GetParticle() const { return particle_; }

protected:
    Scattering& operator=(const Scattering&); // Undefined & not allowed

    // Implemented in child classes to be able to use equality operator
    virtual bool compare(const Scattering&) const = 0;

    struct RandomAngles
    {
        double sx, sy, tx, ty;
    };

    virtual RandomAngles CalculateRandomAngle(double dr, double ei, double ef) = 0;

    Particle& particle_;
};

} // namespace PROPOSAL
