/* Module for particles including:
 *   Particle class
 *   Functions for interacting with particle class
 * Note that, for better or worse, all values are in SI (mks)
 *
 * Written by Ben Hokanson-Fasig for IceCube's Summer of C++ 2017
 */



//Include guard
#ifndef __PARTICLE_HPP_INCLUDED__
#define __PARTICLE_HPP_INCLUDED__

#include <string>
#include <iostream>
#include <sstream>
#include <cmath>
#include "uniqueid.hpp"
#include "vectors.hpp"

const double c_0 = 299792458;
const double qe = 1.60217662e-19;


class Particle
{
    public:
        // Constructors
        explicit Particle(const std::string& type);
        explicit Particle(const int typeint);

        // Getter functions
        const UniqueID id() const {return id_;}
        const std::string name() const {return kind_;}
        const int type() const {return typeint_;}
        const double restmass() const {return restmass_;}
        const double charge() const {return charge_;}
        const CartesianVector position() const {return position_;}
        const FourVector momentum() const {return fourmomentum_;}
        const UnitVector direction() const;
        const double energy() const;
        const double kinetic() const;

        // Setter functions
        void set_position(const CartesianVector& pos);
        void set_position(const double x, const double y, const double z);
        void set_momentum(const FourVector& mom);
        void set_momentum(const CartesianVector& mom);
        void set_momentum(const double en, const UnitVector& dir);
        void set_direction(const UnitVector& dir);
        void set_energy(const double en);
        void set_kinetic(const double ke);


    private:
        const UniqueID id_;
        std::string kind_;
        int typeint_;
        double restmass_;
        double charge_;
        CartesianVector position_;
        FourVector fourmomentum_;

        void set_invariants();
        void set_default_pos();
        void set_default_mom();
};


// Particle print function
std::ostream& operator<<(std::ostream& os, const Particle& p);


// Particle constructor helpers
int gettypeint(const std::string& type);
std::string gettype(const int typeint);
double getmass(const int typeint);
double getcharge(const int typeint);

enum class ParticleTypes
{
    /* Numbers given with five digits. Ex: 10101
     * Patterns:
     *   Elementary particle - 00xxx
     *     Bosons - 000xx
     *     Leptons - 001xx
     *     Quarks - 002xx
     *   Composite particle - 01xxx
     *     Mesons - 012xx
     *     Baryons - 013xx
     *   Atomic Nuclei - 1xxxx
     *     Digits 2 & 3 give atomic number Z
     *     Digits 4 & 5 give number of nucleons N
     *   Atoms - 2xxxx
     *     Digits 2 & 3 give atomic number Z
     *   Molecules - 3xxxx
     */
    
    // Bosons
    photon = 1,
    W_m     = 2,
    W_p    = 3,
    Z      = 4,
    gluon  = 5,
    higgs  = 6,
    // Leptons
    e_m    = 101,
    e_p    = 102,
    mu_m   = 103,
    mu_p   = 104,
    tau_m  = 105,
    tau_p  = 106,
    nuE    = 111,
    nuEbar = 112,
    nuU    = 113,
    nuUbar = 114,
    nuT    = 115,
    nuTbar = 116,
    // Quarks
    u    = 201,
    ubar = 202,
    d    = 203,
    dbar = 204,
    c    = 205,
    cbar = 206,
    s    = 207,
    sbar = 208,
    t    = 209,
    tbar = 210,
    b    = 211,
    bbar = 212,
    // Pseudoscalar Mesons
    pi_m     = 1201,
    pi_p     = 1202,
    pi0      = 1203,
    eta      = 1204,
    etaprime = 1205,
    etac     = 1206,
    etab     = 1207,
    K_m      = 1208,
    K_p      = 1209,
    K0       = 1210,
    K0bar    = 1211,
    K0short  = 1212,
    K0long   = 1213,
    D_m      = 1214,
    D_p      = 1215,
    D0       = 1216,
    D0bar    = 1217,
    D_ms     = 1218,
    D_ps     = 1219,
    B_m      = 1220,
    B_p      = 1221,
    B0       = 1222,
    B0bar    = 1223,
    B0s      = 1224,
    B0sbar   = 1225,
    B_mc     = 1226,
    B_pc     = 1227,
    // Vector Mesons
    rho_m   = 1251,
    rho_p   = 1252,
    rho0    = 1253,
    omega   = 1254,
    phi     = 1255,
    Jpsi    = 1256,
    upsilon = 1257,
    vK_m    = 1258,
    vK_p    = 1259,
    vK0     = 1260,
    vK0bar  = 1261,
    vD_m    = 1262,
    vD_p    = 1263,
    vD0     = 1264,
    vD0bar  = 1265,
    vD_ms   = 1266,
    vD_ps   = 1267,
    vB_m    = 1268,
    vB_p    = 1269,
    vB0     = 1270,
    vB0bar  = 1271,
    vB0s    = 1272,
    vB0sbar = 1273,
    vB_mc   = 1274,
    vB_pc   = 1275,
    // J = +/- 1/2 Baryons
    proton        = 1301,
    neutron       = 1302,
    lambda        = 1303,
    lambdac       = 1304,
    lambdab       = 1305,
    sigma_p       = 1306,
    sigma0        = 1307,
    sigma_m       = 1308,
    sigma_ppc     = 1309,
    sigma_pc      = 1310,
    sigma0c       = 1311,
    sigma_pb      = 1312,
    sigma0b       = 1313,
    sigma_mb      = 1314,
    xi0           = 1315,
    xi_m          = 1316,
    xi_pc         = 1317,
    xi0c          = 1318,
    xi_pcprime    = 1319,
    xi0cprime     = 1320,
    xi_ppcc       = 1321,
    xi_pcc        = 1322,
    xi0b          = 1323,
    xi_mb         = 1324,
    xi0bprime     = 1325,
    xi_mbprime    = 1326,
    xi0bb         = 1327,
    xi_mbb        = 1328,
    xi_pcb        = 1329,
    xi0cb         = 1330,
    xi_pcbprime   = 1331,
    xi0cbprime    = 1332,
    omega0c       = 1333,
    omega_mb      = 1334,
    omega_pcc     = 1335,
    omega0cb      = 1336,
    omega0cbprime = 1337,
    omega_mbb     = 1338,
    omega_pccb    = 1339,
    omega0cbb     = 1340,
    // J = +/- 3/2 Baryons
    delta_pp    = 1350,
    delta_p     = 1351,
    delta0      = 1352,
    delta_m     = 1353,
    sigma3_p    = 1354,
    sigma30     = 1355,
    sigma3_m    = 1356,
    sigma3_ppc  = 1357,
    sigma3_pc   = 1358,
    sigma30c    = 1359,
    sigma3_pb   = 1360,
    sigma30b    = 1361,
    sigma3_mb   = 1362,
    xi30        = 1363,
    xi3_m       = 1364,
    xi3_pc      = 1365,
    xi30c       = 1366,
    xi3_ppcc    = 1367,
    xi3_pcc     = 1368,
    xi30b       = 1369,
    xi3_mb      = 1370,
    xi30bb      = 1371,
    xi3_mbb     = 1372,
    xi3_pcb     = 1373,
    xi30cb      = 1374,
    omega_m     = 1375,
    omega30c    = 1376,
    omega3_mb   = 1377,
    omega3_pcc  = 1378,
    omega30cb   = 1379,
    omega3_mbb  = 1380,
    omega_ppccc = 1381,
    omega3_pccb = 1382,
    omega30cbb  = 1383,
    omega_mbbb  = 1384,
    // Nuclei
    h1n     = 10101,
    h2n     = 10102,
    h3n     = 10103,
    he3n    = 10203,
    he4n    = 10204,
    li6n    = 10306,
    li7n    = 10307,
    be9n    = 10409,
    b10n    = 10510,
    b11n    = 10511,
    c12n    = 10612,
    c13n    = 10613,
    c14n    = 10614,
    n14n    = 10714,
    n15n    = 10715,
    o16n    = 10816,
    o17n    = 10817,
    o18n    = 10818,
    f19n    = 10919,
    ne20n   = 11020,
    ne21n   = 11021,
    ne22n   = 11022,
    na23n   = 11123,
    mg24n   = 11224,
    mg25n   = 11225,
    mg26n   = 11226,
    al27n   = 11327,
    si28n   = 11428,
    si29n   = 11429,
    si30n   = 11430,
    p31n    = 11531,
    s32n    = 11632,
    s33n    = 11633,
    s34n    = 11634,
    s36n    = 11636,
    cl35n   = 11735,
    cl37n   = 11737,
    ar36n   = 11836,
    ar38n   = 11838,
    ar40n   = 11840,
    k39n    = 11939,
    k40n    = 11940,
    k41n    = 11941,
    ca40n   = 12040,
    ca42n   = 12042,
    ca43n   = 12043,
    ca44n   = 12044,
    ca46n   = 12046,
    ca48n   = 12048,
    sc45n   = 12145,
    ti46n   = 12246,
    ti47n   = 12247,
    ti48n   = 12248,
    ti49n   = 12249,
    ti50n   = 12250,
    v50n    = 12350,
    v51n    = 12351,
    cr50n   = 12450,
    cr52n   = 12452,
    cr53n   = 12453,
    cr54n   = 12454,
    mn55n   = 12555,
    fe54n   = 12654,
    fe56n   = 12656,
    fe57n   = 12657,
    fe58n   = 12658,
};

#endif
