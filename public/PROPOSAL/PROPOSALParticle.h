/*! \file   PROPOSALParticle.h
*   \brief  Header file for the Particle routines.
*
*   For more details see the class documentation.
*
*   \date   2013.03.14
*   \author Jan-Hendrik Köhne
*/


#ifndef Particle_H
#define Particle_H
#include "vector"
#include <string>

/**
  * \brief This class provides the main particle properties and functions.
  *
  * All coordinates, angles and physical values are stored in this class.
  */


class PROPOSALParticle
{

public:

    // ----------------------------------------------------------------------------
    /// @brief Particle enums
    // ----------------------------------------------------------------------------
    enum ParticleType { // NB: These match the PDG codes. Keep it that way!
        unknown = 0,
        Gamma = 22,

        EPlus = -11,
        EMinus = 11,
        MuPlus = -13,
        MuMinus = 13,
        TauPlus = -15,
        TauMinus = 15,
        NuE = 12,
        NuEBar = -12,
        NuMu = 14,
        NuMuBar = -14,
        NuTau = 16,
        NuTauBar = -16,

        // TODO: Ist das Kunst, oder kann das weg?
        // Pi0 = 111,
        // PiPlus = 211,
        // PiMinus = -211,
        // K0_Long = 130,
        // KPlus = 321,
        // KMinus = -321,
        // Neutron = 2112,
        // PPlus = 2212,
        // PMinus = -2212,
        // K0_Short = 310,
        // Eta = 221,
        // Lambda = 3122,
        // SigmaPlus = 3222,
        // Sigma0 = 3212,
        // SigmaMinus = 3112,
        // Xi0 = 3322,
        // XiMinus = 3312,
        // OmegaMinus = 3334,
        // NeutronBar = -2112,
        // LambdaBar = -3122,
        // SigmaMinusBar = -3222,
        // Sigma0Bar = -3212,
        // SigmaPlusBar = -3112,
        // Xi0Bar = -3322,
        // XiPlusBar = -3312,
        // OmegaPlusBar = -3334,
        // DPlus = 411,
        // DMinus = -411,
        // D0 = 421,
        // D0Bar = -421,
        // DsPlus = 431,
        // DsMinusBar = -431,
        // LambdacPlus = 4122,
        // WPlus = 24,
        // WMinus = -24,
        // Z0 = 23,

        Brems = -1001,
        DeltaE = -1002,
        EPair = -1003,
        NuclInt = -1004,
        MuPair = -1005,
        Hadrons = -1006,
        ContinuousEnergyLoss = -1111,
        Monopol = -41,
        STauPlus = -9131,
        StauMinus = -9132
    };

private:

    double propagated_distance_; //!< propagation distance [cm]
    double x_;                   //!< x-coordinate [cm]
    double y_;                   //!< y-coordinate [cm]
    double z_;                   //!< z-coordinate [cm]
    double t_;                   //!< age [sec]
    double theta_;               //!< zenith of the momentum in [deg]
    double phi_;                 //!< azimuth of the momentum in [deg]

    long double costh_;          //!< cos(theta)
    long double sinth_;          //!< sin(theta)
    long double cosph_;          //!< cos(phi)
    long double sinph_;          //!< sin(phi)

    double momentum_;            //!< momentum [MeV]
    double square_momentum_;     //!< momentum square [MeV]
    double energy_;              //!< energy [MeV]
    double mass_;                //!< mass [MeV]
    double lifetime_;            //!< lifetime [sec]
    double charge_;              //!< charge

    std::string name_;           //!< name of the particle - Presetted to "mu"
    double low_;                 //!< energy below which the particle is lost [MeV]
    ParticleType type_;          //!< particle type: 1 for muon, 2 for tau, 3 for electron

    int parent_particle_id_;        //!< parent particle id
    double parent_particle_energy_; //!< energy of the parent particle
    int particle_id_;               //!< particle id

    double xi_;                  //!< x-coordinate entry Point [cm]
    double yi_;                  //!< y-coordinate entry Point [cm]
    double zi_;                  //!< z-coordinate entry Point [cm]
    double ti_;                  //!< t-coordinate entry Point [sec]
    double ei_;                  //!< energy at entry point [MeV]

    double xf_;                  //!< x-coordinate exit Point [cm]
    double yf_;                  //!< y-coordinate exit Point [cm]
    double zf_;                  //!< z-coordinate exit Point [cm]
    double tf_;                  //!< t-coordinate exit Point [sec]
    double ef_;                  //!< energy at exit point [MeV]

    double xc_;                  //!< x-coordinate at point of closest approach [cm]
    double yc_;                  //!< y-coordinate at point of closest approach [cm]
    double zc_;                  //!< z-coordinate at point of closest approach [cm]
    double tc_;                  //!< t-coordinate at point of closest approach [sec]
    double ec_;                  //!< energy at at point of closest approach [MeV]

    double elost_;               //!< energy lost in the detector volume [MeV]


//----------------------------------------------------------------------------//

public:

    /**
     * \brief Default Constructor
     *
     * Constructor which sets "default" settings.
     */
    PROPOSALParticle();

//----------------------------------------------------------------------------//

    PROPOSALParticle(const PROPOSALParticle&);
    PROPOSALParticle& operator=(const PROPOSALParticle&);
    bool operator==(const PROPOSALParticle &particle) const;
    bool operator!=(const PROPOSALParticle &particle) const;
    friend std::ostream& operator<<(std::ostream& os, PROPOSALParticle const& particle);

//----------------------------------------------------------------------------//

    /*!
     * \brief Create particle from another particle.
     *
     * This function ist mostly used to store particle information.
     *
     * \param parent_particle_id      parent particle id
     * \param particle_id             particle id
     * \param name                    particle name
     * \param x                       x-coordinate
     * \param y                       y-coordinate
     * \param z                       z-coordinate
     * \param theta                   theta angle
     * \param phi                     phi angle
     * \param energy                  particle energy
     * \param t                       particle time
     * \param prop_dist               flight distance
     * \param *p                      source particle
     */

    PROPOSALParticle(int parent_particle_id,
             int particle_id,
             ParticleType type,
             double x,
             double y,
             double z,
             double theta,
             double phi,
             double energy,
             double t,
             double prop_dist,
             PROPOSALParticle *p);

//----------------------------------------------------------------------------//
    /*!
     * \brief Create particle with properties
     *
     * This function ist mostly used to store particle information.
     *
     * \param parent_particle_id      parent particle id
     * \param particle_id             particle id
     * \param name                    particle name
     * \param x                       x-coordinate
     * \param y                       y-coordinate
     * \param z                       z-coordinate
     * \param theta                   theta angle
     * \param phi                     phi angle
     * \param energy                  particle energy
     * \param t                       particle time
     * \param prop_dist               flight distance
     */
    PROPOSALParticle(int parent_particle_id,
             int particle_id,
             ParticleType type,
             double x,
             double y,
             double z,
             double theta,
             double phi,
             double energy,
             double t,
             double prop_dist,
             double prim_energy = 0);

//----------------------------------------------------------------------------//
    /*!
     * \brief Create particle with properties
     *
     * This function ist mostly used to store particle information.
     *
     * \param aname     particle name
     * \param x         x-coordinate
     * \param y         y-coordinate
     * \param z         z-coordinate
     * \param theta     theta angle
     * \param phi       phi angle
     * \param energy    particle energy
     * \param t         particle time
     */
    PROPOSALParticle(
            ParticleType type,
            double x,
            double y,
            double z,
            double theta,
            double phi,
            double energy,
            double t);

//----------------------------------------------------------------------------//
    /*!
     * \brief Create particle with properties
     *
     * This constructor is used to create a Particle only by name.
     * For example whne a ProcessCollection is created no other informations as
     * mass, lifetime etc. are needed and no infos about energy or location are necessary
     *
     * \param name     particle name
     */
    PROPOSALParticle(ParticleType type);

//----------------------------------------------------------------------------//
    /*!
     * initialize particle by its name
     *
     * \param name      particle type
     */

    // void InitByName(ParticleType type);
    void InitParticle(ParticleType type);


//----------------------------------------------------------------------------//
    // Memberfunctions

    /*!
     * initialize the location and direction of the particle,\n
     * time in sec, x, y, z in cm, theta and phi in deg
     *
     * \param time      particle time
     * \param x         x-coordinate
     * \param y         y-coordinate
     * \param z         z-coordinate
     * \param theta     theta angle
     * \param phi       phi angle
     */

    void Location(double time,
                  double x,
                  double y,
                  double z,
                  double theta,
                  double phi);

//----------------------------------------------------------------------------//

    void swap(PROPOSALParticle &particle);

//----------------------------------------------------------------------------//

    //Setter
    void SetProperties( int parent_particle_id = 0,  int particle_id = 0,    double energy = 0, double t=0,
                        double x = 0,   double y = 0,   double z = 0,   double theta = 0,   double phi = 0,
                        double xi = 0,  double yi= 0,   double zi= 0,   double ti = 0   ,   double Ei = 0,
                        double xf = 0,  double yf= 0,   double zf= 0,   double tf = 0   ,   double Ef = 0,
                        double xc = 0,  double yc= 0,   double zc= 0,   double tc = 0   ,   double Ec = 0);
    void SetEnergy(double e);
    void SetPropagatedDistance(double prop_dist);
    void SetX(double x);
    void SetY(double y);
    void SetZ(double z);
    void SetT(double t);
    void SetTheta(double theta);
    void SetPhi(double phi);
    void SetMomentum(double momentum);
    void SetMass(double mass);
    void SetLifetime(double lifetime);
    void SetCharge(double charge);
    void SetName(std::string name);
    void SetLow(double low);
    void SetType(ParticleType type);
    void SetParentParticleId(int parent_particle_id);
    void SetParentParticleEnergy(double parent_particle_energy);
    void SetParticleId(int particle_id);
    void SetXi(double xi);
    void SetYi(double yi);
    void SetZi(double zi);
    void SetTi(double ti);
    void SetEi(double ei);

    void SetXf(double xf);
    void SetYf(double yf);
    void SetZf(double zf);
    void SetTf(double tf);
    void SetEf(double ef);

    void SetXc(double xc);
    void SetYc(double yc);
    void SetZc(double zc);
    void SetTc(double tc);
    void SetEc(double ec);

    void SetElost(double elost);


//----------------------------------------------------------------------------//
    // Getter

    double GetEnergy() const{return energy_;}
//----------------------------------------------------------------------------//
    double GetPropagatedDistance() const{return propagated_distance_;}
//----------------------------------------------------------------------------//
    double GetX() const{return x_;}
//----------------------------------------------------------------------------//
    double GetY() const{return y_;}
//----------------------------------------------------------------------------//
    double GetZ() const{return z_;}
//----------------------------------------------------------------------------//
    double GetT() const{return t_;}
//----------------------------------------------------------------------------//
    double GetTheta() const{return theta_;}
//----------------------------------------------------------------------------//
    double GetPhi() const{return phi_;}
//----------------------------------------------------------------------------//
    double GetSinTheta() const{return sinth_;}
//----------------------------------------------------------------------------//
    double GetSinPhi() const{return sinph_;}
//----------------------------------------------------------------------------//
    double GetCosTheta() const{return costh_;}
//----------------------------------------------------------------------------//
    double GetCosPhi() const{return cosph_;}
//----------------------------------------------------------------------------//
    double GetMomentum() const{return momentum_;}
//----------------------------------------------------------------------------//
    double GetMass() const{return mass_;}
//----------------------------------------------------------------------------//
    double GetLifetime() const{return lifetime_;}
//----------------------------------------------------------------------------//
    double GetCharge() const{return charge_;}
//----------------------------------------------------------------------------//
    std::string GetName() const{return name_;}
//----------------------------------------------------------------------------//
    double GetLow() const{return low_;}
//----------------------------------------------------------------------------//
    ParticleType GetType() const{return type_;}
//----------------------------------------------------------------------------//
    int GetParentParticleId() const{return parent_particle_id_;}
//----------------------------------------------------------------------------//
    double GetParentParticleEnergy() const{return parent_particle_energy_;}
//----------------------------------------------------------------------------//
    int GetParticleId() const{return particle_id_;}
//----------------------------------------------------------------------------//
    double GetXi() const{return xi_;}
//----------------------------------------------------------------------------//
    double GetYi() const{return yi_;}
//----------------------------------------------------------------------------//
    double GetZi() const{return zi_;}
//----------------------------------------------------------------------------//
    double GetTi() const{return ti_;}
//----------------------------------------------------------------------------//
    double GetEi() const{return ei_;}
//----------------------------------------------------------------------------//
    double GetXf() const{return xf_;}
//----------------------------------------------------------------------------//
    double GetYf() const{return yf_;}
//----------------------------------------------------------------------------//
    double GetZf() const{return zf_;}
//----------------------------------------------------------------------------//
    double GetTf() const{return tf_;}
//----------------------------------------------------------------------------//
    double GetEf() const{return ef_;}
//----------------------------------------------------------------------------//
    double GetXc() const{return xc_;}
//----------------------------------------------------------------------------//
    double GetYc() const{return yc_;}
//----------------------------------------------------------------------------//
    double GetZc() const{return zc_;}
//----------------------------------------------------------------------------//
    double GetTc() const{return tc_;}
//----------------------------------------------------------------------------//
    double GetEc() const{return ec_;}
//----------------------------------------------------------------------------//
    double GetElost() const{return elost_;}

//----------------------------------------------------------------------------//
    // destructors
    ~PROPOSALParticle() {}


};



#endif //PARTICLE_H