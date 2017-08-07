/* Module for particles including:
 *   Particle class
 *   Functions for interacting with particle class
 * Note that, for better or worse, all values are in SI (mks)
 *
 * Written by Ben Hokanson-Fasig for IceCube's Summer of C++ 2017
 */


// #define NDEBUG
#include <cassert>
#include "particle.hpp"


// Particle default setters
void Particle::set_invariants()
{
    kind_ = gettype(typeint_);
    restmass_ = getmass(typeint_);
    charge_ = getcharge(typeint_);
}

void Particle::set_default_pos()
{
    position_ = CartesianVector(0,0,0);
}

void Particle::set_default_mom()
{
    fourmomentum_ = FourVector(restmass_*c_0, 0,0,0);
}


// Particle constructors
Particle::Particle(const std::string& type)
{
    typeint_ = gettypeint(type);
    set_invariants();
    set_default_pos();
    set_default_mom();
}

Particle::Particle(const int typeint)
{
    typeint_ = typeint;
    set_invariants();
    set_default_pos();
    set_default_mom();
}


// Particle getter functions
const CartesianVector Particle::direction() const
{
    try
    {
        return UnitVector(fourmomentum_.x(),fourmomentum_.y(),fourmomentum_.z());
    }
    catch (std::domain_error& e)
    {
        // No viable direction
        return CartesianVector(0,0,0);
    }
}

const double Particle::energy() const
{
    return fourmomentum_[0]*c_0;
}

const double Particle::kinetic() const
{
    return energy() - restmass_*c_0*c_0;
}



// Particle setter functions
void Particle::set_position(const CartesianVector& pos)
{
    position_ = pos;
}

void Particle::set_position(const double x, const double y, const double z)
{
    position_ = CartesianVector(x,y,z);
}

void Particle::set_momentum(const FourVector& mom)
{
    // Ignore first component and simply set based on the 3-momentum
    set_momentum(CartesianVector(mom.x(),mom.y(),mom.z()));
}

void Particle::set_momentum(const CartesianVector& mom)
{
    fourmomentum_ = FourVector(0,mom.x(),mom.y(),mom.z());
    double p2 = -1*dot(fourmomentum_,fourmomentum_);
    assert(restmass_*restmass_*c_0*c_0 + p2 >= 0);
    fourmomentum_[0] = sqrt(restmass_*restmass_ * c_0*c_0 + p2);
}

void Particle::set_momentum(const double en, const UnitVector& dir)
{
    if (en*en < restmass_*restmass_*pow(c_0,4))
    {
        std::ostringstream oss;
        oss << "Energy (" << en << ") is less than the particle's rest energy";
        throw std::invalid_argument(oss.str());
    }
    assert(en*en/(c_0*c_0) - restmass_*restmass_*c_0*c_0 >= 0);
    double pmag = sqrt(en*en / (c_0*c_0) - restmass_*restmass_ * c_0*c_0);
    CartesianVector mom = pmag * dir;
    set_momentum(mom);
}

void Particle::set_direction(const UnitVector& dir)
{
    double en = energy();
    // If there is no momentum, the direction is meaningless
    // To avoid unexpected results, throw an error
    if (fourmomentum_.x()==0 && fourmomentum_.y()==0 && fourmomentum_.z()==0) {
        std::ostringstream oss;
        oss << "Particle direction cannot be set when it has zero momentum. "
        << "Try using set_momentum(energy, direction) instead";
        throw std::domain_error(oss.str());
    }
    set_momentum(en, dir);
}

void Particle::set_energy(const double en)
{
    CartesianVector dir = direction();
    // If there is no momentum, the direction is meaningless
    // And with no direction, energy alone cannot be set
    // To avoid unexpected results, throw an error
    if (fourmomentum_.x()==0 && fourmomentum_.y()==0 && fourmomentum_.z()==0) {
        std::ostringstream oss;
        oss << "Particle energy cannot be set when it has no direction. "
        << "Try using set_momentum(energy, direction) instead";
        throw std::domain_error(oss.str());
    }
    set_momentum(en, dir);
}

void Particle::set_kinetic(const double ke)
{
    CartesianVector dir = direction();
    double en = ke + restmass_*c_0*c_0;
    set_momentum(en, dir);
}


// Particle print function
std::ostream& operator<<(std::ostream& os, const Particle& p)
{
    return os << p.name() << " (" << p.id() << ")";
}


// Particle constructor helpers
int gettypeint(const std::string& type)
{
    // Bosons
    ParticleTypes retval;
    if      (type.compare("photon")==0
          || type.compare("gamma")==0)      {retval = ParticleTypes::photon;}
    else if (type.compare("W-")==0
          || type.compare("W_m")==0)        {retval = ParticleTypes::W_m;}
    else if (type.compare("W+")==0
          || type.compare("W_p")==0)        {retval = ParticleTypes::W_p;}
    else if (type.compare("Z")==0)          {retval = ParticleTypes::Z;}
    else if (type.compare("gluon")==0
          || type.compare("g")==0)          {retval = ParticleTypes::gluon;}
    else if (type.compare("higgs")==0
          || type.compare("h")==0)          {retval = ParticleTypes::higgs;}

    // Leptons
    else if (type.compare("electron")==0
          || type.compare("e-")==0
          || type.compare("e_m")==0)        {retval = ParticleTypes::e_m;}
    else if (type.compare("positron")==0
          || type.compare("e+")==0         
          || type.compare("e_p")==0)        {retval = ParticleTypes::e_p;}
    else if (type.compare("mu-")==0
          || type.compare("mu_m")==0)       {retval = ParticleTypes::mu_m;}
    else if (type.compare("mu+")==0
          || type.compare("mu_p")==0)       {retval = ParticleTypes::mu_p;}
    else if (type.compare("tau-")==0
          || type.compare("tau_m")==0)      {retval = ParticleTypes::tau_m;}
    else if (type.compare("tau+")==0
          || type.compare("tau_p")==0)      {retval = ParticleTypes::tau_p;}
    else if (type.compare("nuE")==0)        {retval = ParticleTypes::nuE;}
    else if (type.compare("nuEbar")==0)     {retval = ParticleTypes::nuEbar;}
    else if (type.compare("nuU")==0
          || type.compare("nuMu")==0)       {retval = ParticleTypes::nuU;}
    else if (type.compare("nuUbar")==0
          || type.compare("nuMubar")==0)    {retval = ParticleTypes::nuUbar;}
    else if (type.compare("nuT")==0
          || type.compare("nuTau")==0)      {retval = ParticleTypes::nuT;}
    else if (type.compare("nuTbar")==0
          || type.compare("nuTaubar")==0)   {retval = ParticleTypes::nuTbar;}

    // Quarks
    else if (type.compare("u")==0
          || type.compare("up")==0)             {retval = ParticleTypes::u;}
    else if (type.compare("ubar")==0
          || type.compare("anti-up")==0)        {retval = ParticleTypes::ubar;}
    else if (type.compare("d")==0
          || type.compare("down")==0)           {retval = ParticleTypes::d;}
    else if (type.compare("dbar")==0
          || type.compare("anti-down")==0)      {retval = ParticleTypes::dbar;}
    else if (type.compare("c")==0
          || type.compare("charm")==0)          {retval = ParticleTypes::c;}
    else if (type.compare("cbar")==0
          || type.compare("anti-charm")==0)     {retval = ParticleTypes::cbar;}
    else if (type.compare("s")==0
          || type.compare("strange")==0)        {retval = ParticleTypes::s;}
    else if (type.compare("sbar")==0
          || type.compare("anti-strange")==0)   {retval = ParticleTypes::sbar;}
    else if (type.compare("t")==0
          || type.compare("top")==0)            {retval = ParticleTypes::t;}
    else if (type.compare("tbar")==0
          || type.compare("anti-top")==0)       {retval = ParticleTypes::tbar;}
    else if (type.compare("b")==0
          || type.compare("bottom")==0)         {retval = ParticleTypes::b;}
    else if (type.compare("bbar")==0
          || type.compare("anti-bottom")==0)    {retval = ParticleTypes::bbar;}

    // Pseudoscalar Mesons
    else if (type.compare("pi-")==0
          || type.compare("pi_m")==0)       {retval = ParticleTypes::pi_m;}
    else if (type.compare("pi+")==0
          || type.compare("pi_p")==0)       {retval = ParticleTypes::pi_p;}
    else if (type.compare("pi0")==0
          || type.compare("pion")==0)       {retval = ParticleTypes::pi0;}
    else if (type.compare("eta")==0)        {retval = ParticleTypes::eta;}
    else if (type.compare("etaprime")==0)   {retval = ParticleTypes::etaprime;}
    else if (type.compare("etac")==0)       {retval = ParticleTypes::etac;}
    else if (type.compare("etab")==0)       {retval = ParticleTypes::etab;}
    else if (type.compare("K-")==0
          || type.compare("K_m")==0)        {retval = ParticleTypes::K_m;}
    else if (type.compare("K+")==0
          || type.compare("K_p")==0)        {retval = ParticleTypes::K_p;}
    else if (type.compare("K0")==0
          || type.compare("kaon")==0)       {retval = ParticleTypes::K0;}
    else if (type.compare("K0bar")==0
          || type.compare("anti-kaon")==0)  {retval = ParticleTypes::K0bar;}
    else if (type.compare("K0short")==0
          || type.compare("Kshort")==0)     {retval = ParticleTypes::K0short;}
    else if (type.compare("K0long")==0
          || type.compare("Klong")==0)      {retval = ParticleTypes::K0long;}
    else if (type.compare("D-")==0
          || type.compare("D_m")==0)        {retval = ParticleTypes::D_m;}
    else if (type.compare("D+")==0
          || type.compare("D_p")==0)        {retval = ParticleTypes::D_p;}
    else if (type.compare("D0")==0
          || type.compare("D")==0)          {retval = ParticleTypes::D0;}
    else if (type.compare("D0bar")==0
          || type.compare("anti-D")==0)     {retval = ParticleTypes::D0bar;}
    else if (type.compare("D-s")==0
          || type.compare("Ds-")==0
          || type.compare("D_ms")==0)       {retval = ParticleTypes::D_ms;}
    else if (type.compare("D+s")==0
          || type.compare("Ds+")==0
          || type.compare("D_ps")==0)       {retval = ParticleTypes::D_ps;}
    else if (type.compare("B-")==0
          || type.compare("B_m")==0)        {retval = ParticleTypes::B_m;}
    else if (type.compare("B+")==0
          || type.compare("B_p")==0)        {retval = ParticleTypes::B_p;}
    else if (type.compare("B0")==0
          || type.compare("B")==0)          {retval = ParticleTypes::B0;}
    else if (type.compare("B0bar")==0
          || type.compare("anti-B")==0)     {retval = ParticleTypes::B0bar;}
    else if (type.compare("B0s")==0
          || type.compare("Bs0")==0)        {retval = ParticleTypes::B0s;}
    else if (type.compare("B0sbar")==0
          || type.compare("Bs0bar")==0)     {retval = ParticleTypes::B0sbar;}
    else if (type.compare("B-c")==0
          || type.compare("Bc-")==0
          || type.compare("B_mc")==0)       {retval = ParticleTypes::B_mc;}
    else if (type.compare("B+c")==0
          || type.compare("Bc+")==0
          || type.compare("B_pc")==0)       {retval = ParticleTypes::B_pc;}

    // Vector Mesons
    else if (type.compare("rho-")==0
          || type.compare("rho_m")==0)      {retval = ParticleTypes::rho_m;}
    else if (type.compare("rho+")==0
          || type.compare("rho_p")==0)      {retval = ParticleTypes::rho_p;}
    else if (type.compare("rho0")==0
          || type.compare("rho")==0)        {retval = ParticleTypes::rho0;}
    else if (type.compare("omega")==0)      {retval = ParticleTypes::omega;}
    else if (type.compare("phi")==0)        {retval = ParticleTypes::phi;}
    else if (type.compare("J/psi")==0
          || type.compare("J")==0
          || type.compare("psi")==0
          || type.compare("Jpsi")==0)       {retval = ParticleTypes::Jpsi;}
    else if (type.compare("upsilon")==0)    {retval = ParticleTypes::upsilon;}
    else if (type.compare("vK-")==0
          || type.compare("vK_m")==0)       {retval = ParticleTypes::vK_m;}
    else if (type.compare("vK+")==0
          || type.compare("vK_p")==0)       {retval = ParticleTypes::vK_p;}
    else if (type.compare("vK0")==0
          || type.compare("vK")==0)         {retval = ParticleTypes::vK0;}
    else if (type.compare("vK0bar")==0
          || type.compare("vKbar")==0)      {retval = ParticleTypes::vK0bar;}
    else if (type.compare("vD-")==0
          || type.compare("vD_m")==0)       {retval = ParticleTypes::vD_m;}
    else if (type.compare("vD+")==0
          || type.compare("vD_p")==0)       {retval = ParticleTypes::vD_p;}
    else if (type.compare("vD0")==0
          || type.compare("vD")==0)         {retval = ParticleTypes::vD0;}
    else if (type.compare("vD0bar")==0
          || type.compare("vDbar")==0)      {retval = ParticleTypes::vD0bar;}
    else if (type.compare("vD-s")==0
          || type.compare("vDs-")==0
          || type.compare("vD_ms")==0)      {retval = ParticleTypes::vD_ms;}
    else if (type.compare("vD+s")==0
          || type.compare("vDs+")==0
          || type.compare("vD_ps")==0)      {retval = ParticleTypes::vD_ps;}
    else if (type.compare("vB-")==0
          || type.compare("vB_m")==0)       {retval = ParticleTypes::vB_m;}
    else if (type.compare("vB+")==0
          || type.compare("vB_p")==0)       {retval = ParticleTypes::vB_p;}
    else if (type.compare("vB0")==0
          || type.compare("vB")==0)         {retval = ParticleTypes::vB0;}
    else if (type.compare("vB0bar")==0
          || type.compare("vBbar")==0)      {retval = ParticleTypes::vB0bar;}
    else if (type.compare("vB0s")==0
          || type.compare("vBs0")==0
          || type.compare("vBs")==0)        {retval = ParticleTypes::vB0s;}
    else if (type.compare("vB0sbar")==0
          || type.compare("vBs0bar")==0
          || type.compare("vBsbar")==0)     {retval = ParticleTypes::vB0sbar;}
    else if (type.compare("vB-c")==0
          || type.compare("vBc-")==0
          || type.compare("vB_mc")==0)      {retval = ParticleTypes::vB_mc;}
    else if (type.compare("vB+c")==0
          || type.compare("vBc+")==0
          || type.compare("vB_pc")==0)      {retval = ParticleTypes::vB_pc;}

    // J = +/- 1/2 Baryons
    else if (type.compare("proton")==0
          || type.compare("p+")==0)             {retval = ParticleTypes::proton;}
    else if (type.compare("neutron")==0
          || type.compare("n")==0
          || type.compare("n0")==0)             {retval = ParticleTypes::neutron;}
    else if (type.compare("lambda")==0)         {retval = ParticleTypes::lambda;}
    else if (type.compare("lambdac")==0)        {retval = ParticleTypes::lambdac;}
    else if (type.compare("lambdab")==0)        {retval = ParticleTypes::lambdab;}
    else if (type.compare("sigma+")==0
          || type.compare("sigma_p")==0)        {retval = ParticleTypes::sigma_p;}
    else if (type.compare("sigma0")==0
          || type.compare("sigma")==0)          {retval = ParticleTypes::sigma0;}
    else if (type.compare("sigma-")==0
          || type.compare("sigma_m")==0)        {retval = ParticleTypes::sigma_m;}
    else if (type.compare("sigma++c")==0
          || type.compare("sigmac++")==0
          || type.compare("sigma_ppc")==0)      {retval = ParticleTypes::sigma_ppc;}
    else if (type.compare("sigma+c")==0
          || type.compare("sigmac+")==0
          || type.compare("sigma_pc")==0)       {retval = ParticleTypes::sigma_pc;}
    else if (type.compare("sigma0c")==0
          || type.compare("sigmac0")==0
          || type.compare("sigmac")==0)         {retval = ParticleTypes::sigma0c;}
    else if (type.compare("sigma+b")==0
          || type.compare("sigmab+")==0
          || type.compare("sigma_pb")==0)       {retval = ParticleTypes::sigma_pb;}
    else if (type.compare("sigma0b")==0
          || type.compare("sigmab0")==0
          || type.compare("sigmab")==0)         {retval = ParticleTypes::sigma0b;}
    else if (type.compare("sigma-b")==0
          || type.compare("sigmab-")==0
          || type.compare("sigma_mb")==0)       {retval = ParticleTypes::sigma_mb;}
    else if (type.compare("xi0")==0
          || type.compare("xi")==0)             {retval = ParticleTypes::xi0;}
    else if (type.compare("xi-")==0
          || type.compare("xi_m")==0)           {retval = ParticleTypes::xi_m;}
    else if (type.compare("xi+c")==0
          || type.compare("xic+")==0
          || type.compare("xi_pc")==0)          {retval = ParticleTypes::xi_pc;}
    else if (type.compare("xi0c")==0
          || type.compare("xic0")==0
          || type.compare("xic")==0)            {retval = ParticleTypes::xi0c;}
    else if (type.compare("xi+cprime")==0
          || type.compare("xic+prime")==0
          || type.compare("xi_pcprime")==0)     {retval = ParticleTypes::xi_pcprime;}
    else if (type.compare("xi0cprime")==0
          || type.compare("xic0prime")==0
          || type.compare("xicprime")==0)       {retval = ParticleTypes::xi0cprime;}
    else if (type.compare("xi++cc")==0
          || type.compare("xicc++")==0
          || type.compare("xi_ppcc")==0)        {retval = ParticleTypes::xi_ppcc;}
    else if (type.compare("xi+cc")==0
          || type.compare("xicc+")==0
          || type.compare("xi_pcc")==0)         {retval = ParticleTypes::xi_pcc;}
    else if (type.compare("xi0b")==0
          || type.compare("xib0")==0
          || type.compare("xib")==0)            {retval = ParticleTypes::xi0b;}
    else if (type.compare("xi-b")==0
          || type.compare("xib-")==0
          || type.compare("xi_mb")==0)          {retval = ParticleTypes::xi_mb;}
    else if (type.compare("xi0bprime")==0
          || type.compare("xib0prime")==0
          || type.compare("xibprime")==0)       {retval = ParticleTypes::xi0bprime;}
    else if (type.compare("xi-bprime")==0
          || type.compare("xib-prime")==0
          || type.compare("xi_mbprime")==0)     {retval = ParticleTypes::xi_mbprime;}
    else if (type.compare("xi0bb")==0
          || type.compare("xibb0")==0
          || type.compare("xibb")==0)           {retval = ParticleTypes::xi0bb;}
    else if (type.compare("xi-bb")==0
          || type.compare("xibb-")==0
          || type.compare("xi_mbb")==0)         {retval = ParticleTypes::xi_mbb;}
    else if (type.compare("xi+cb")==0
          || type.compare("xicb+")==0
          || type.compare("xi_pcb")==0)         {retval = ParticleTypes::xi_pcb;}
    else if (type.compare("xi0cb")==0
          || type.compare("xicb0")==0
          || type.compare("xicb")==0)           {retval = ParticleTypes::xi0cb;}
    else if (type.compare("xi+cbprime")==0
          || type.compare("xicb+prime")==0
          || type.compare("xi_pcbprime")==0)    {retval = ParticleTypes::xi_pcbprime;}
    else if (type.compare("xi0cbprime")==0
          || type.compare("xicb0prime")==0
          || type.compare("xicbprime")==0)      {retval = ParticleTypes::xi0cbprime;}
    else if (type.compare("omega0c")==0
          || type.compare("omegac")==0)         {retval = ParticleTypes::omega0c;}
    else if (type.compare("omega-b")==0
          || type.compare("omegab-")==0
          || type.compare("omega_mb")==0)       {retval = ParticleTypes::omega_mb;}
    else if (type.compare("omega+cc")==0
          || type.compare("omegacc+")==0
          || type.compare("omega_pcc")==0)      {retval = ParticleTypes::omega_pcc;}
    else if (type.compare("omega0cb")==0
          || type.compare("omegacb0")==0
          || type.compare("omegacb")==0)        {retval = ParticleTypes::omega0cb;}
    else if (type.compare("omega0cbprime")==0
          || type.compare("omegacb0prime")==0
          || type.compare("omegacbprime")==0)   {retval = ParticleTypes::omega0cbprime;}
    else if (type.compare("omega-bb")==0
          || type.compare("omegabb-")==0
          || type.compare("omega_mbb")==0)      {retval = ParticleTypes::omega_mbb;}
    else if (type.compare("omega+ccb")==0
          || type.compare("omegaccb+")==0
          || type.compare("omega_pccb")==0)     {retval = ParticleTypes::omega_pccb;}
    else if (type.compare("omega0cbb")==0
          || type.compare("omegacbb0")==0
          || type.compare("omegacbb")==0)       {retval = ParticleTypes::omega0cbb;}

    // J = +/- 3/2 Baryons
    else if (type.compare("delta++")==0
          || type.compare("delta_pp")==0)       {retval = ParticleTypes::delta_pp;}
    else if (type.compare("delta+")==0
          || type.compare("delta_p")==0)        {retval = ParticleTypes::delta_p;}
    else if (type.compare("delta0")==0
          || type.compare("delta")==0)          {retval = ParticleTypes::delta0;}
    else if (type.compare("delta-")==0
          || type.compare("delta_m")==0)        {retval = ParticleTypes::delta_m;}
    else if (type.compare("sigma3+")==0
          || type.compare("sigma3_p")==0)       {retval = ParticleTypes::sigma3_p;}
    else if (type.compare("sigma30")==0
          || type.compare("sigma3")==0)         {retval = ParticleTypes::sigma30;}
    else if (type.compare("sigma3-")==0
          || type.compare("sigma3_m")==0)       {retval = ParticleTypes::sigma3_m;}
    else if (type.compare("sigma3++c")==0
          || type.compare("sigma3c++")==0
          || type.compare("sigma3_ppc")==0)     {retval = ParticleTypes::sigma3_ppc;}
    else if (type.compare("sigma3+c")==0
          || type.compare("sigma3c+")==0
          || type.compare("sigma3_pc")==0)      {retval = ParticleTypes::sigma3_pc;}
    else if (type.compare("sigma30c")==0
          || type.compare("sigma3c0")==0
          || type.compare("sigma3c")==0)        {retval = ParticleTypes::sigma30c;}
    else if (type.compare("sigma3+b")==0
          || type.compare("sigma3b+")==0
          || type.compare("sigma3_pb")==0)      {retval = ParticleTypes::sigma3_pb;}
    else if (type.compare("sigma30b")==0
          || type.compare("sigma3b0")==0
          || type.compare("sigma3b")==0)        {retval = ParticleTypes::sigma30b;}
    else if (type.compare("sigma3-b")==0
          || type.compare("sigma3b-")==0
          || type.compare("sigma3_mb")==0)      {retval = ParticleTypes::sigma3_mb;}
    else if (type.compare("xi30")==0
          || type.compare("xi3")==0)            {retval = ParticleTypes::xi30;}
    else if (type.compare("xi3-")==0
          || type.compare("xi3_m")==0)          {retval = ParticleTypes::xi3_m;}
    else if (type.compare("xi3+c")==0
          || type.compare("xi3c+")==0
          || type.compare("xi3_pc")==0)         {retval = ParticleTypes::xi3_pc;}
    else if (type.compare("xi30c")==0
          || type.compare("xi3c0")==0
          || type.compare("xi3c")==0)           {retval = ParticleTypes::xi30c;}
    else if (type.compare("xi3++cc")==0
          || type.compare("xi3cc++")==0
          || type.compare("xi3_ppcc")==0)       {retval = ParticleTypes::xi3_ppcc;}
    else if (type.compare("xi3+cc")==0
          || type.compare("xi3cc+")==0
          || type.compare("xi3_pcc")==0)        {retval = ParticleTypes::xi3_pcc;}
    else if (type.compare("xi30b")==0
          || type.compare("xi3b0")==0
          || type.compare("xi3b")==0)           {retval = ParticleTypes::xi30b;}
    else if (type.compare("xi3-b")==0
          || type.compare("xi3b-")==0
          || type.compare("xi3_mb")==0)         {retval = ParticleTypes::xi3_mb;}
    else if (type.compare("xi30bb")==0
          || type.compare("xi3bb0")==0
          || type.compare("xi3bb")==0)          {retval = ParticleTypes::xi30bb;}
    else if (type.compare("xi3-bb")==0
          || type.compare("xi3bb-")==0
          || type.compare("xi3_mbb")==0)        {retval = ParticleTypes::xi3_mbb;}
    else if (type.compare("xi3+cb")==0
          || type.compare("xi3cb+")==0
          || type.compare("xi3_pcb")==0)        {retval = ParticleTypes::xi3_pcb;}
    else if (type.compare("xi30cb")==0
          || type.compare("xi3cb0")==0
          || type.compare("xi3cb")==0)          {retval = ParticleTypes::xi30cb;}
    else if (type.compare("omega-")==0
          || type.compare("omega_m")==0)        {retval = ParticleTypes::omega_m;}
    else if (type.compare("omega30c")==0
          || type.compare("omega3c0")==0
          || type.compare("omega3c")==0)        {retval = ParticleTypes::omega30c;}
    else if (type.compare("omega3-b")==0
          || type.compare("omega3b-")==0
          || type.compare("omega3_mb")==0)      {retval = ParticleTypes::omega3_mb;}
    else if (type.compare("omega3+cc")==0
          || type.compare("omega3cc+")==0
          || type.compare("omega3_pcc")==0)     {retval = ParticleTypes::omega3_pcc;}
    else if (type.compare("omega30cb")==0
          || type.compare("omega3cb0")==0
          || type.compare("omega3cb")==0)       {retval = ParticleTypes::omega30cb;}
    else if (type.compare("omega3-bb")==0
          || type.compare("omega3bb-")==0
          || type.compare("omega3_mbb")==0)     {retval = ParticleTypes::omega3_mbb;}
    else if (type.compare("omega++ccc")==0
          || type.compare("omegaccc++")==0
          || type.compare("omega_ppccc")==0)    {retval = ParticleTypes::omega_ppccc;}
    else if (type.compare("omega3+ccb")==0
          || type.compare("omega3ccb+")==0
          || type.compare("omega3_pccb")==0)    {retval = ParticleTypes::omega3_pccb;}
    else if (type.compare("omega30cbb")==0
          || type.compare("omega3cbb0")==0
          || type.compare("omega3cbb")==0)      {retval = ParticleTypes::omega30cbb;}
    else if (type.compare("omega-bbb")==0
          || type.compare("omegabbb-")==0
          || type.compare("omega_mbbb")==0)     {retval = ParticleTypes::omega_mbb;}

    // Nuclei
    else if (type.compare("h1n")==0
          || type.compare("h1nuc")==0)          {retval = ParticleTypes::h1n;}
    else if (type.compare("h2n")==0
          || type.compare("h2nuc")==0)          {retval = ParticleTypes::h2n;}
    else if (type.compare("h3n")==0
          || type.compare("h3nuc")==0)          {retval = ParticleTypes::h3n;}
    else if (type.compare("he3n")==0
          || type.compare("he3nuc")==0)         {retval = ParticleTypes::he3n;}
    else if (type.compare("he4n")==0
          || type.compare("he4nuc")==0)         {retval = ParticleTypes::he4n;}
    else if (type.compare("li6n")==0
          || type.compare("li6nuc")==0)         {retval = ParticleTypes::li6n;}
    else if (type.compare("li7n")==0
          || type.compare("li7nuc")==0)         {retval = ParticleTypes::li7n;}
    else if (type.compare("be9n")==0
          || type.compare("be9nuc")==0)         {retval = ParticleTypes::be9n;}
    else if (type.compare("b10n")==0
          || type.compare("b10nuc")==0)         {retval = ParticleTypes::b10n;}
    else if (type.compare("b11n")==0
          || type.compare("b11nuc")==0)         {retval = ParticleTypes::b11n;}
    else if (type.compare("c12n")==0
          || type.compare("c12nuc")==0)         {retval = ParticleTypes::c12n;}
    else if (type.compare("c13n")==0
          || type.compare("c13nuc")==0)         {retval = ParticleTypes::c13n;}
    else if (type.compare("c14n")==0
          || type.compare("c14nuc")==0)         {retval = ParticleTypes::c14n;}
    else if (type.compare("n14n")==0
          || type.compare("n14nuc")==0)         {retval = ParticleTypes::n14n;}
    else if (type.compare("n15n")==0
          || type.compare("n15nuc")==0)         {retval = ParticleTypes::n15n;}
    else if (type.compare("o16n")==0
          || type.compare("o16nuc")==0)         {retval = ParticleTypes::o16n;}
    else if (type.compare("o17n")==0
          || type.compare("o17nuc")==0)         {retval = ParticleTypes::o17n;}
    else if (type.compare("o18n")==0
          || type.compare("o18nuc")==0)         {retval = ParticleTypes::o18n;}
    else if (type.compare("f19n")==0
          || type.compare("f19nuc")==0)         {retval = ParticleTypes::f19n;}
    else if (type.compare("ne20n")==0
          || type.compare("ne20nuc")==0)        {retval = ParticleTypes::ne20n;}
    else if (type.compare("ne21n")==0
          || type.compare("ne21nuc")==0)        {retval = ParticleTypes::ne21n;}
    else if (type.compare("ne22n")==0
          || type.compare("ne22nuc")==0)        {retval = ParticleTypes::ne22n;}
    else if (type.compare("na23n")==0
          || type.compare("na23nuc")==0)        {retval = ParticleTypes::na23n;}
    else if (type.compare("mg24n")==0
          || type.compare("mg24nuc")==0)        {retval = ParticleTypes::mg24n;}
    else if (type.compare("mg25n")==0
          || type.compare("mg25nuc")==0)        {retval = ParticleTypes::mg25n;}
    else if (type.compare("mg26n")==0
          || type.compare("mg26nuc")==0)        {retval = ParticleTypes::mg26n;}
    else if (type.compare("al27n")==0
          || type.compare("al27nuc")==0)        {retval = ParticleTypes::al27n;}
    else if (type.compare("si28n")==0
          || type.compare("si28nuc")==0)        {retval = ParticleTypes::si28n;}
    else if (type.compare("si29n")==0
          || type.compare("si29nuc")==0)        {retval = ParticleTypes::si29n;}
    else if (type.compare("si30n")==0
          || type.compare("si30nuc")==0)        {retval = ParticleTypes::si30n;}
    else if (type.compare("p31n")==0
          || type.compare("p31nuc")==0)         {retval = ParticleTypes::p31n;}
    else if (type.compare("s32n")==0
          || type.compare("s32nuc")==0)         {retval = ParticleTypes::s32n;}
    else if (type.compare("s33n")==0
          || type.compare("s33nuc")==0)         {retval = ParticleTypes::s33n;}
    else if (type.compare("s34n")==0
          || type.compare("s34nuc")==0)         {retval = ParticleTypes::s34n;}
    else if (type.compare("s36n")==0
          || type.compare("s36nuc")==0)         {retval = ParticleTypes::s36n;}
    else if (type.compare("cl35n")==0
          || type.compare("cl35nuc")==0)        {retval = ParticleTypes::cl35n;}
    else if (type.compare("cl37n")==0
          || type.compare("cl37nuc")==0)        {retval = ParticleTypes::cl37n;}
    else if (type.compare("ar36n")==0
          || type.compare("ar36nuc")==0)        {retval = ParticleTypes::ar36n;}
    else if (type.compare("ar38n")==0
          || type.compare("ar38nuc")==0)        {retval = ParticleTypes::ar38n;}
    else if (type.compare("ar40n")==0
          || type.compare("ar40nuc")==0)        {retval = ParticleTypes::ar40n;}
    else if (type.compare("k39n")==0
          || type.compare("k39nuc")==0)         {retval = ParticleTypes::k39n;}
    else if (type.compare("k40n")==0
          || type.compare("k40nuc")==0)         {retval = ParticleTypes::k40n;}
    else if (type.compare("k41n")==0
          || type.compare("k41nuc")==0)         {retval = ParticleTypes::k41n;}
    else if (type.compare("ca40n")==0
          || type.compare("ca40nuc")==0)        {retval = ParticleTypes::ca40n;}
    else if (type.compare("ca42n")==0
          || type.compare("ca42nuc")==0)        {retval = ParticleTypes::ca42n;}
    else if (type.compare("ca43n")==0
          || type.compare("ca43nuc")==0)        {retval = ParticleTypes::ca43n;}
    else if (type.compare("ca44n")==0
          || type.compare("ca44nuc")==0)        {retval = ParticleTypes::ca44n;}
    else if (type.compare("ca46n")==0
          || type.compare("ca46nuc")==0)        {retval = ParticleTypes::ca46n;}
    else if (type.compare("ca48n")==0
          || type.compare("ca48nuc")==0)        {retval = ParticleTypes::ca48n;}
    else if (type.compare("sc45n")==0
          || type.compare("sc45nuc")==0)        {retval = ParticleTypes::sc45n;}
    else if (type.compare("ti46n")==0
          || type.compare("ti46nuc")==0)        {retval = ParticleTypes::ti46n;}
    else if (type.compare("ti47n")==0
          || type.compare("ti47nuc")==0)        {retval = ParticleTypes::ti47n;}
    else if (type.compare("ti48n")==0
          || type.compare("ti48nuc")==0)        {retval = ParticleTypes::ti48n;}
    else if (type.compare("ti49n")==0
          || type.compare("ti49nuc")==0)        {retval = ParticleTypes::ti49n;}
    else if (type.compare("ti50n")==0
          || type.compare("ti50nuc")==0)        {retval = ParticleTypes::ti50n;}
    else if (type.compare("v50n")==0
          || type.compare("v50nuc")==0)         {retval = ParticleTypes::v50n;}
    else if (type.compare("v51n")==0
          || type.compare("v51nuc")==0)         {retval = ParticleTypes::v51n;}
    else if (type.compare("cr50n")==0
          || type.compare("cr50nuc")==0)        {retval = ParticleTypes::cr50n;}
    else if (type.compare("cr52n")==0
          || type.compare("cr52nuc")==0)        {retval = ParticleTypes::cr52n;}
    else if (type.compare("cr53n")==0
          || type.compare("cr53nuc")==0)        {retval = ParticleTypes::cr53n;}
    else if (type.compare("cr54n")==0
          || type.compare("cr54nuc")==0)        {retval = ParticleTypes::cr54n;}
    else if (type.compare("mn55n")==0
          || type.compare("mn55nuc")==0)        {retval = ParticleTypes::mn55n;}
    else if (type.compare("fe54n")==0
          || type.compare("fe54nuc")==0)        {retval = ParticleTypes::fe54n;}
    else if (type.compare("fe56n")==0
          || type.compare("fe56nuc")==0)        {retval = ParticleTypes::fe56n;}
    else if (type.compare("fe57n")==0
          || type.compare("fe57nuc")==0)        {retval = ParticleTypes::fe57n;}
    else if (type.compare("fe58n")==0
          || type.compare("fe58nuc")==0)        {retval = ParticleTypes::fe58n;}

    // Catch bad input
    else
    {
        throw std::invalid_argument("'"+type+"' is not a recognized particle type");
    }

    return static_cast<int>(retval);
}

std::string gettype(const int typeint)
{
    switch(static_cast<ParticleTypes>(typeint))
    {
        // Bosons
        case ParticleTypes::photon      : return "photon";
        case ParticleTypes::W_m         : return "W-";
        case ParticleTypes::W_p         : return "W+";
        case ParticleTypes::Z           : return "Z";
        case ParticleTypes::gluon       : return "gluon";
        case ParticleTypes::higgs       : return "higgs";

        // Leptons
        case ParticleTypes::e_m         : return "e-";
        case ParticleTypes::e_p         : return "e+";
        case ParticleTypes::mu_m        : return "mu-";
        case ParticleTypes::mu_p        : return "mu+";
        case ParticleTypes::tau_m       : return "tau-";
        case ParticleTypes::tau_p       : return "tau+";
        case ParticleTypes::nuE         : return "nuE";
        case ParticleTypes::nuEbar      : return "nuEbar";
        case ParticleTypes::nuU         : return "nuU";
        case ParticleTypes::nuUbar      : return "nuUbar";
        case ParticleTypes::nuT         : return "nuT";
        case ParticleTypes::nuTbar      : return "nuTbar";

        // Quarks
        case ParticleTypes::u           : return "u";
        case ParticleTypes::ubar        : return "ubar";
        case ParticleTypes::d           : return "d";
        case ParticleTypes::dbar        : return "dbar";
        case ParticleTypes::c           : return "c";
        case ParticleTypes::cbar        : return "cbar";
        case ParticleTypes::s           : return "s";
        case ParticleTypes::sbar        : return "sbar";
        case ParticleTypes::t           : return "t";
        case ParticleTypes::tbar        : return "tbar";
        case ParticleTypes::b           : return "b";
        case ParticleTypes::bbar        : return "bbar";

        // Pseudoscalar Mesons
        case ParticleTypes::pi_m        : return "pi-";
        case ParticleTypes::pi_p        : return "pi+";
        case ParticleTypes::pi0         : return "pi0";
        case ParticleTypes::eta         : return "eta";
        case ParticleTypes::etaprime    : return "etaprime";
        case ParticleTypes::etac        : return "etac";
        case ParticleTypes::etab        : return "etab";
        case ParticleTypes::K_m         : return "K-";
        case ParticleTypes::K_p         : return "K+";
        case ParticleTypes::K0          : return "K0";
        case ParticleTypes::K0bar       : return "K0bar";
        case ParticleTypes::K0short     : return "K0short";
        case ParticleTypes::K0long      : return "K0long";
        case ParticleTypes::D_m         : return "D-";
        case ParticleTypes::D_p         : return "D+";
        case ParticleTypes::D0          : return "D0";
        case ParticleTypes::D0bar       : return "D0bar";
        case ParticleTypes::D_ms        : return "D-s";
        case ParticleTypes::D_ps        : return "D+s";
        case ParticleTypes::B_m         : return "B-";
        case ParticleTypes::B_p         : return "B+";
        case ParticleTypes::B0          : return "B0";
        case ParticleTypes::B0bar       : return "B0bar";
        case ParticleTypes::B0s         : return "B0s";
        case ParticleTypes::B0sbar      : return "B0sbar";
        case ParticleTypes::B_mc        : return "B-c";
        case ParticleTypes::B_pc        : return "B+c";

        // Vector Mesons
        case ParticleTypes::rho_m       : return "rho-";
        case ParticleTypes::rho_p       : return "rho+";
        case ParticleTypes::rho0        : return "rho0";
        case ParticleTypes::omega       : return "omega";
        case ParticleTypes::phi         : return "phi";
        case ParticleTypes::Jpsi        : return "J/psi";
        case ParticleTypes::upsilon     : return "upsilon";
        case ParticleTypes::vK_m        : return "vK-";
        case ParticleTypes::vK_p        : return "vK+";
        case ParticleTypes::vK0         : return "vK0";
        case ParticleTypes::vK0bar      : return "vK0bar";
        case ParticleTypes::vD_m        : return "vD-";
        case ParticleTypes::vD_p        : return "vD+";
        case ParticleTypes::vD0         : return "vD0";
        case ParticleTypes::vD0bar      : return "vD0bar";
        case ParticleTypes::vD_ms       : return "vD-s";
        case ParticleTypes::vD_ps       : return "vD+s";
        case ParticleTypes::vB_m        : return "vB-";
        case ParticleTypes::vB_p        : return "vB+";
        case ParticleTypes::vB0         : return "vB0";
        case ParticleTypes::vB0bar      : return "vB0bar";
        case ParticleTypes::vB0s        : return "vB0s";
        case ParticleTypes::vB0sbar     : return "vB0sbar";
        case ParticleTypes::vB_mc       : return "vB-c";
        case ParticleTypes::vB_pc       : return "vB+c";

        // J = +/- 1/2 Baryons
        case ParticleTypes::proton          : return "p+";
        case ParticleTypes::neutron         : return "n0";
        case ParticleTypes::lambda          : return "lambda";
        case ParticleTypes::lambdac         : return "lambdac";
        case ParticleTypes::lambdab         : return "lambdab";
        case ParticleTypes::sigma_p         : return "sigma+";
        case ParticleTypes::sigma0          : return "sigma0";
        case ParticleTypes::sigma_m         : return "sigma-";
        case ParticleTypes::sigma_ppc       : return "sigma++c";
        case ParticleTypes::sigma_pc        : return "sigma+c";
        case ParticleTypes::sigma0c         : return "sigma0c";
        case ParticleTypes::sigma_pb        : return "sigma+b";
        case ParticleTypes::sigma0b         : return "sigma0b";
        case ParticleTypes::sigma_mb        : return "sigma-b";
        case ParticleTypes::xi0             : return "xi0";
        case ParticleTypes::xi_m            : return "xi-";
        case ParticleTypes::xi_pc           : return "xi+c";
        case ParticleTypes::xi0c            : return "xi0c";
        case ParticleTypes::xi_pcprime      : return "xi+cprime";
        case ParticleTypes::xi0cprime       : return "xi0cprime";
        case ParticleTypes::xi_ppcc         : return "xi++cc";
        case ParticleTypes::xi_pcc          : return "xi+cc";
        case ParticleTypes::xi0b            : return "xi0b";
        case ParticleTypes::xi_mb           : return "xi-b";
        case ParticleTypes::xi0bprime       : return "xi0bprime";
        case ParticleTypes::xi_mbprime      : return "xi-bprime";
        case ParticleTypes::xi0bb           : return "xi0bb";
        case ParticleTypes::xi_mbb          : return "xi-bb";
        case ParticleTypes::xi_pcb          : return "xi+cb";
        case ParticleTypes::xi0cb           : return "xi0cb";
        case ParticleTypes::xi_pcbprime     : return "xi+cbprime";
        case ParticleTypes::xi0cbprime      : return "xi0cbprime";
        case ParticleTypes::omega0c         : return "omega0c";
        case ParticleTypes::omega_mb        : return "omega-b";
        case ParticleTypes::omega_pcc       : return "omega+cc";
        case ParticleTypes::omega0cb        : return "omega0cb";
        case ParticleTypes::omega0cbprime   : return "omega0cbprime";
        case ParticleTypes::omega_mbb       : return "omega-bb";
        case ParticleTypes::omega_pccb      : return "omega+ccb";
        case ParticleTypes::omega0cbb       : return "omega0cbb";

        // J = +/- 3/2 Baryons
        case ParticleTypes::delta_pp        : return "delta++";
        case ParticleTypes::delta_p         : return "delta+";
        case ParticleTypes::delta0          : return "delta0";
        case ParticleTypes::delta_m         : return "delta-";
        case ParticleTypes::sigma3_p        : return "sigma3+";
        case ParticleTypes::sigma30         : return "sigma30";
        case ParticleTypes::sigma3_m        : return "sigma3-";
        case ParticleTypes::sigma3_ppc      : return "sigma3++c";
        case ParticleTypes::sigma3_pc       : return "sigma3+c";
        case ParticleTypes::sigma30c        : return "sigma30c";
        case ParticleTypes::sigma3_pb       : return "sigma3+b";
        case ParticleTypes::sigma30b        : return "sigma30b";
        case ParticleTypes::sigma3_mb       : return "sigma3-b";
        case ParticleTypes::xi30            : return "xi30";
        case ParticleTypes::xi3_m           : return "xi3-";
        case ParticleTypes::xi3_pc          : return "xi3+c";
        case ParticleTypes::xi30c           : return "xi30c";
        case ParticleTypes::xi3_ppcc        : return "xi3++cc";
        case ParticleTypes::xi3_pcc         : return "xi3+cc";
        case ParticleTypes::xi30b           : return "xi30b";
        case ParticleTypes::xi3_mb          : return "xi3-b";
        case ParticleTypes::xi30bb          : return "xi30bb";
        case ParticleTypes::xi3_mbb         : return "xi3-bb";
        case ParticleTypes::xi3_pcb         : return "xi3+cb";
        case ParticleTypes::xi30cb          : return "xi30cb";
        case ParticleTypes::omega_m         : return "omega-";
        case ParticleTypes::omega30c        : return "omega30c";
        case ParticleTypes::omega3_mb       : return "omega3-b";
        case ParticleTypes::omega3_pcc      : return "omega3+cc";
        case ParticleTypes::omega30cb       : return "omega30cb";
        case ParticleTypes::omega3_mbb      : return "omega3-bb";
        case ParticleTypes::omega_ppccc     : return "omega++ccc";
        case ParticleTypes::omega3_pccb     : return "omega+ccb";
        case ParticleTypes::omega30cbb      : return "omega30cbb";
        case ParticleTypes::omega_mbbb      : return "omega-bbb";

        // Nuclei
        case ParticleTypes::h1n     : return "h1nuc";
        case ParticleTypes::h2n     : return "h2nuc";
        case ParticleTypes::h3n     : return "h3nuc";
        case ParticleTypes::he3n    : return "he3nuc";
        case ParticleTypes::he4n    : return "he4nuc";
        case ParticleTypes::li6n    : return "li6nuc";
        case ParticleTypes::li7n    : return "li7nuc";
        case ParticleTypes::be9n    : return "be9nuc";
        case ParticleTypes::b10n    : return "b10nuc";
        case ParticleTypes::b11n    : return "b11nuc";
        case ParticleTypes::c12n    : return "c12nuc";
        case ParticleTypes::c13n    : return "c13nuc";
        case ParticleTypes::c14n    : return "c14nuc";
        case ParticleTypes::n14n    : return "n14nuc";
        case ParticleTypes::n15n    : return "n15nuc";
        case ParticleTypes::o16n    : return "o16nuc";
        case ParticleTypes::o17n    : return "o17nuc";
        case ParticleTypes::o18n    : return "o18nuc";
        case ParticleTypes::f19n    : return "f19nuc";
        case ParticleTypes::ne20n   : return "ne20nuc";
        case ParticleTypes::ne21n   : return "ne21nuc";
        case ParticleTypes::ne22n   : return "ne22nuc";
        case ParticleTypes::na23n   : return "na23nuc";
        case ParticleTypes::mg24n   : return "mg24nuc";
        case ParticleTypes::mg25n   : return "mg25nuc";
        case ParticleTypes::mg26n   : return "mg26nuc";
        case ParticleTypes::al27n   : return "al27nuc";
        case ParticleTypes::si28n   : return "si28nuc";
        case ParticleTypes::si29n   : return "si29nuc";
        case ParticleTypes::si30n   : return "si30nuc";
        case ParticleTypes::p31n    : return "p31nuc";
        case ParticleTypes::s32n    : return "s32nuc";
        case ParticleTypes::s33n    : return "s33nuc";
        case ParticleTypes::s34n    : return "s34nuc";
        case ParticleTypes::s36n    : return "s36nuc";
        case ParticleTypes::cl35n   : return "cl35nuc";
        case ParticleTypes::cl37n   : return "cl37nuc";
        case ParticleTypes::ar36n   : return "ar36nuc";
        case ParticleTypes::ar38n   : return "ar38nuc";
        case ParticleTypes::ar40n   : return "ar40nuc";
        case ParticleTypes::k39n    : return "k39nuc";
        case ParticleTypes::k40n    : return "k40nuc";
        case ParticleTypes::k41n    : return "k41nuc";
        case ParticleTypes::ca40n   : return "ca40nuc";
        case ParticleTypes::ca42n   : return "ca42nuc";
        case ParticleTypes::ca43n   : return "ca43nuc";
        case ParticleTypes::ca44n   : return "ca44nuc";
        case ParticleTypes::ca46n   : return "ca46nuc";
        case ParticleTypes::ca48n   : return "ca48nuc";
        case ParticleTypes::sc45n   : return "sc45nuc";
        case ParticleTypes::ti46n   : return "ti46nuc";
        case ParticleTypes::ti47n   : return "ti47nuc";
        case ParticleTypes::ti48n   : return "ti48nuc";
        case ParticleTypes::ti49n   : return "ti49nuc";
        case ParticleTypes::ti50n   : return "ti50nuc";
        case ParticleTypes::v50n    : return "v50nuc";
        case ParticleTypes::v51n    : return "v51nuc";
        case ParticleTypes::cr50n   : return "cr50nuc";
        case ParticleTypes::cr52n   : return "cr52nuc";
        case ParticleTypes::cr53n   : return "cr53nuc";
        case ParticleTypes::cr54n   : return "cr54nuc";
        case ParticleTypes::mn55n   : return "mn55nuc";
        case ParticleTypes::fe54n   : return "fe54nuc";
        case ParticleTypes::fe56n   : return "fe56nuc";
        case ParticleTypes::fe57n   : return "fe57nuc";
        case ParticleTypes::fe58n   : return "fe58nuc";
    }
    // Catch bad input
    std::ostringstream oss;
    oss << typeint << " does not correlate to a known particle type";
    throw std::invalid_argument(oss.str());
}

double getmass(const int typeint)
{
    double mevmass = -1;
    double amumass = -1;
    switch(static_cast<ParticleTypes>(typeint))
    {
        // Bosons
        case ParticleTypes::photon      : mevmass = 0; break;
        case ParticleTypes::W_m         : mevmass = 80385; break;
        case ParticleTypes::W_p         : mevmass = 80385; break;
        case ParticleTypes::Z           : mevmass = 91187.5; break;
        case ParticleTypes::gluon       : mevmass = 0; break;
        case ParticleTypes::higgs       : mevmass = 125090; break;

        // Leptons
        case ParticleTypes::e_m         : mevmass = 0.511; break;
        case ParticleTypes::e_p         : mevmass = 0.511; break;
        case ParticleTypes::mu_m        : mevmass = 105.7; break;
        case ParticleTypes::mu_p        : mevmass = 105.7; break;
        case ParticleTypes::tau_m       : mevmass = 1776.86; break;
        case ParticleTypes::tau_p       : mevmass = 1776.86; break;
        case ParticleTypes::nuE         : mevmass = 0; break;
        case ParticleTypes::nuEbar      : mevmass = 0; break;
        case ParticleTypes::nuU         : mevmass = 0; break;
        case ParticleTypes::nuUbar      : mevmass = 0; break;
        case ParticleTypes::nuT         : mevmass = 0; break;
        case ParticleTypes::nuTbar      : mevmass = 0; break;

        // Quarks
        case ParticleTypes::u           : mevmass = 2.2; break;
        case ParticleTypes::ubar        : mevmass = 2.2; break;
        case ParticleTypes::d           : mevmass = 4.6; break;
        case ParticleTypes::dbar        : mevmass = 4.6; break;
        case ParticleTypes::c           : mevmass = 1280; break;
        case ParticleTypes::cbar        : mevmass = 1280; break;
        case ParticleTypes::s           : mevmass = 96; break;
        case ParticleTypes::sbar        : mevmass = 96; break;
        case ParticleTypes::t           : mevmass = 173100; break;
        case ParticleTypes::tbar        : mevmass = 173100; break;
        case ParticleTypes::b           : mevmass = 4180; break;
        case ParticleTypes::bbar        : mevmass = 4180; break;

        // Pseudoscalar Mesons
        case ParticleTypes::pi_m        : mevmass = 139.57018; break;
        case ParticleTypes::pi_p        : mevmass = 139.57018; break;
        case ParticleTypes::pi0         : mevmass = 134.9766; break;
        case ParticleTypes::eta         : mevmass = 547.862; break;
        case ParticleTypes::etaprime    : mevmass = 957.78; break;
        case ParticleTypes::etac        : mevmass = 2983.6; break;
        case ParticleTypes::etab        : mevmass = 9398.0; break;
        case ParticleTypes::K_m         : mevmass = 493.677; break;
        case ParticleTypes::K_p         : mevmass = 493.677; break;
        case ParticleTypes::K0          : mevmass = 497.614; break;
        case ParticleTypes::K0bar       : mevmass = 497.614; break;
        case ParticleTypes::K0short     : mevmass = 497.614; break;
        case ParticleTypes::K0long      : mevmass = 497.614; break;
        case ParticleTypes::D_m         : mevmass = 1869.61; break;
        case ParticleTypes::D_p         : mevmass = 1869.61; break;
        case ParticleTypes::D0          : mevmass = 1864.84; break;
        case ParticleTypes::D0bar       : mevmass = 1864.84; break;
        case ParticleTypes::D_ms        : mevmass = 1968.30; break;
        case ParticleTypes::D_ps        : mevmass = 1968.30; break;
        case ParticleTypes::B_m         : mevmass = 5279.26; break;
        case ParticleTypes::B_p         : mevmass = 5279.26; break;
        case ParticleTypes::B0          : mevmass = 5279.58; break;
        case ParticleTypes::B0bar       : mevmass = 5279.58; break;
        case ParticleTypes::B0s         : mevmass = 5366.77; break;
        case ParticleTypes::B0sbar      : mevmass = 5366.77; break;
        case ParticleTypes::B_mc        : mevmass = 6275.6; break;
        case ParticleTypes::B_pc        : mevmass = 6275.6; break;

        // Vector Mesons
        case ParticleTypes::rho_m       : mevmass = 775.11; break;
        case ParticleTypes::rho_p       : mevmass = 775.11; break;
        case ParticleTypes::rho0        : mevmass = 775.26; break;
        case ParticleTypes::omega       : mevmass = 782.65; break;
        case ParticleTypes::phi         : mevmass = 1019.461; break;
        case ParticleTypes::Jpsi        : mevmass = 3096.916; break;
        case ParticleTypes::upsilon     : mevmass = 9460.30; break;
        case ParticleTypes::vK_m        : mevmass = 891.66; break;
        case ParticleTypes::vK_p        : mevmass = 891.66; break;
        case ParticleTypes::vK0         : mevmass = 895.81; break;
        case ParticleTypes::vK0bar      : mevmass = 895.81; break;
        case ParticleTypes::vD_m        : mevmass = 2010.26; break;
        case ParticleTypes::vD_p        : mevmass = 2010.26; break;
        case ParticleTypes::vD0         : mevmass = 2006.96; break;
        case ParticleTypes::vD0bar      : mevmass = 2006.96; break;
        case ParticleTypes::vD_ms       : mevmass = 2112.1; break;
        case ParticleTypes::vD_ps       : mevmass = 2112.1; break;
        case ParticleTypes::vB_m        : mevmass = 5325.2; break;
        case ParticleTypes::vB_p        : mevmass = 5325.2; break;
        case ParticleTypes::vB0         : mevmass = 5325.2; break;
        case ParticleTypes::vB0bar      : mevmass = 5325.2; break;
        case ParticleTypes::vB0s        : mevmass = 5415.4; break;
        case ParticleTypes::vB0sbar     : mevmass = 5415.4; break;
        case ParticleTypes::vB_mc       : mevmass = -1; break;
        case ParticleTypes::vB_pc       : mevmass = -1; break;

        // J = +/- 1/2 Baryons
        case ParticleTypes::proton          : mevmass = 938.272046; break;
        case ParticleTypes::neutron         : mevmass = 939.565379; break;
        case ParticleTypes::lambda          : mevmass = 1115.683; break;
        case ParticleTypes::lambdac         : mevmass = 2286.46; break;
        case ParticleTypes::lambdab         : mevmass = 5619.4; break;
        case ParticleTypes::sigma_p         : mevmass = 1189.37; break;
        case ParticleTypes::sigma0          : mevmass = 1192.642; break;
        case ParticleTypes::sigma_m         : mevmass = 1197.449; break;
        case ParticleTypes::sigma_ppc       : mevmass = 2453.98; break;
        case ParticleTypes::sigma_pc        : mevmass = 2452.9; break;
        case ParticleTypes::sigma0c         : mevmass = 2453.74; break;
        case ParticleTypes::sigma_pb        : mevmass = 5811.3; break;
        case ParticleTypes::sigma0b         : mevmass = -1; break;
        case ParticleTypes::sigma_mb        : mevmass = 5815.5; break;
        case ParticleTypes::xi0             : mevmass = 1314.86; break;
        case ParticleTypes::xi_m            : mevmass = 1321.71; break;
        case ParticleTypes::xi_pc           : mevmass = 2467.8; break;
        case ParticleTypes::xi0c            : mevmass = 2470.88; break;
        case ParticleTypes::xi_pcprime      : mevmass = 2575.6; break;
        case ParticleTypes::xi0cprime       : mevmass = 2577.9; break;
        case ParticleTypes::xi_ppcc         : mevmass = 3621.4; break;
        case ParticleTypes::xi_pcc          : mevmass = -1; break;
        case ParticleTypes::xi0b            : mevmass = 5787.8; break;
        case ParticleTypes::xi_mb           : mevmass = 5791.1; break;
        case ParticleTypes::xi0bprime       : mevmass = -1; break;
        case ParticleTypes::xi_mbprime      : mevmass = -1; break;
        case ParticleTypes::xi0bb           : mevmass = -1; break;
        case ParticleTypes::xi_mbb          : mevmass = -1; break;
        case ParticleTypes::xi_pcb          : mevmass = -1; break;
        case ParticleTypes::xi0cb           : mevmass = -1; break;
        case ParticleTypes::xi_pcbprime     : mevmass = -1; break;
        case ParticleTypes::xi0cbprime      : mevmass = -1; break;
        case ParticleTypes::omega0c         : mevmass = 2695.2; break;
        case ParticleTypes::omega_mb        : mevmass = 6071; break;
        case ParticleTypes::omega_pcc       : mevmass = -1; break;
        case ParticleTypes::omega0cb        : mevmass = -1; break;
        case ParticleTypes::omega0cbprime   : mevmass = -1; break;
        case ParticleTypes::omega_mbb       : mevmass = -1; break;
        case ParticleTypes::omega_pccb      : mevmass = -1; break;
        case ParticleTypes::omega0cbb       : mevmass = -1; break;

        // J = +/- 3/2 Baryons
        case ParticleTypes::delta_pp        : mevmass = 1232; break;
        case ParticleTypes::delta_p         : mevmass = 1232; break;
        case ParticleTypes::delta0          : mevmass = 1232; break;
        case ParticleTypes::delta_m         : mevmass = 1232; break;
        case ParticleTypes::sigma3_p        : mevmass = 1382.8; break;
        case ParticleTypes::sigma30         : mevmass = 1383.7; break;
        case ParticleTypes::sigma3_m        : mevmass = 1387.2; break;
        case ParticleTypes::sigma3_ppc      : mevmass = 2517.9; break;
        case ParticleTypes::sigma3_pc       : mevmass = 2517.5; break;
        case ParticleTypes::sigma30c        : mevmass = 2518.8; break;
        case ParticleTypes::sigma3_pb       : mevmass = 5832.1; break;
        case ParticleTypes::sigma30b        : mevmass = -1; break;
        case ParticleTypes::sigma3_mb       : mevmass = 5835.1; break;
        case ParticleTypes::xi30            : mevmass = 1531.8; break;
        case ParticleTypes::xi3_m           : mevmass = 1535.0; break;
        case ParticleTypes::xi3_pc          : mevmass = 2645.9; break;
        case ParticleTypes::xi30c           : mevmass = 1645.9; break;
        case ParticleTypes::xi3_ppcc        : mevmass = -1; break;
        case ParticleTypes::xi3_pcc         : mevmass = -1; break;
        case ParticleTypes::xi30b           : mevmass = 5945.5; break;
        case ParticleTypes::xi3_mb          : mevmass = -1; break;
        case ParticleTypes::xi30bb          : mevmass = -1; break;
        case ParticleTypes::xi3_mbb         : mevmass = -1; break;
        case ParticleTypes::xi3_pcb         : mevmass = -1; break;
        case ParticleTypes::xi30cb          : mevmass = -1; break;
        case ParticleTypes::omega_m         : mevmass = 1672.45; break;
        case ParticleTypes::omega30c        : mevmass = 2765.9; break;
        case ParticleTypes::omega3_mb       : mevmass = -1; break;
        case ParticleTypes::omega3_pcc      : mevmass = -1; break;
        case ParticleTypes::omega30cb       : mevmass = -1; break;
        case ParticleTypes::omega3_mbb      : mevmass = -1; break;
        case ParticleTypes::omega_ppccc     : mevmass = -1; break;
        case ParticleTypes::omega3_pccb     : mevmass = -1; break;
        case ParticleTypes::omega30cbb      : mevmass = -1; break;
        case ParticleTypes::omega_mbbb      : mevmass = -1; break;

        // Nuclei
        case ParticleTypes::h1n     : amumass = 1.007825; break;
        case ParticleTypes::h2n     : amumass = 2.014102; break;
        case ParticleTypes::h3n     : amumass = 3.016049; break;
        case ParticleTypes::he3n    : amumass = 3.016029; break;
        case ParticleTypes::he4n    : amumass = 4.002603; break;
        case ParticleTypes::li6n    : amumass = 6.015122; break;
        case ParticleTypes::li7n    : amumass = 7.016004; break;
        case ParticleTypes::be9n    : amumass = 9.012182; break;
        case ParticleTypes::b10n    : amumass = 10.012937; break;
        case ParticleTypes::b11n    : amumass = 11.009305; break;
        case ParticleTypes::c12n    : amumass = 12.0; break;
        case ParticleTypes::c13n    : amumass = 13.003355; break;
        case ParticleTypes::c14n    : amumass = 14.003242; break;
        case ParticleTypes::n14n    : amumass = 14.003074; break;
        case ParticleTypes::n15n    : amumass = 15.000109; break;
        case ParticleTypes::o16n    : amumass = 15.994915; break;
        case ParticleTypes::o17n    : amumass = 16.999132; break;
        case ParticleTypes::o18n    : amumass = 17.999160; break;
        case ParticleTypes::f19n    : amumass = 18.998403; break;
        case ParticleTypes::ne20n   : amumass = 19.992440; break;
        case ParticleTypes::ne21n   : amumass = 20.993847; break;
        case ParticleTypes::ne22n   : amumass = 21.991386; break;
        case ParticleTypes::na23n   : amumass = 22.989770; break;
        case ParticleTypes::mg24n   : amumass = 23.985042; break;
        case ParticleTypes::mg25n   : amumass = 24.985837; break;
        case ParticleTypes::mg26n   : amumass = 25.982593; break;
        case ParticleTypes::al27n   : amumass = 26.981538; break;
        case ParticleTypes::si28n   : amumass = 27.976927; break;
        case ParticleTypes::si29n   : amumass = 28.976495; break;
        case ParticleTypes::si30n   : amumass = 29.973770; break;
        case ParticleTypes::p31n    : amumass = 30.973762; break;
        case ParticleTypes::s32n    : amumass = 31.972071; break;
        case ParticleTypes::s33n    : amumass = 32.971458; break;
        case ParticleTypes::s34n    : amumass = 33.967867; break;
        case ParticleTypes::s36n    : amumass = 35.967081; break;
        case ParticleTypes::cl35n   : amumass = 34.968853; break;
        case ParticleTypes::cl37n   : amumass = 36.965903; break;
        case ParticleTypes::ar36n   : amumass = 35.967546; break;
        case ParticleTypes::ar38n   : amumass = 37.962732; break;
        case ParticleTypes::ar40n   : amumass = 39.962383; break;
        case ParticleTypes::k39n    : amumass = 38.963707; break;
        case ParticleTypes::k40n    : amumass = 39.963999; break;
        case ParticleTypes::k41n    : amumass = 40.961826; break;
        case ParticleTypes::ca40n   : amumass = 39.962591; break;
        case ParticleTypes::ca42n   : amumass = 41.958618; break;
        case ParticleTypes::ca43n   : amumass = 42.958767; break;
        case ParticleTypes::ca44n   : amumass = 43.955481; break;
        case ParticleTypes::ca46n   : amumass = 45.953693; break;
        case ParticleTypes::ca48n   : amumass = 47.952534; break;
        case ParticleTypes::sc45n   : amumass = 44.955910; break;
        case ParticleTypes::ti46n   : amumass = 45.952629; break;
        case ParticleTypes::ti47n   : amumass = 46.951764; break;
        case ParticleTypes::ti48n   : amumass = 47.947947; break;
        case ParticleTypes::ti49n   : amumass = 48.947871; break;
        case ParticleTypes::ti50n   : amumass = 49.944792; break;
        case ParticleTypes::v50n    : amumass = 49.947163; break;
        case ParticleTypes::v51n    : amumass = 50.943964; break;
        case ParticleTypes::cr50n   : amumass = 49.946050; break;
        case ParticleTypes::cr52n   : amumass = 51.940512; break;
        case ParticleTypes::cr53n   : amumass = 52.940654; break;
        case ParticleTypes::cr54n   : amumass = 53.938885; break;
        case ParticleTypes::mn55n   : amumass = 54.938050; break;
        case ParticleTypes::fe54n   : amumass = 53.939615; break;
        case ParticleTypes::fe56n   : amumass = 55.934942; break;
        case ParticleTypes::fe57n   : amumass = 56.935399; break;
        case ParticleTypes::fe58n   : amumass = 57.933280; break;
    }

    // Convert to kg
    if      (mevmass>0) {return mevmass * 1.7826619e-30;}
    else if (amumass>0) {return amumass * 1.660539e-27;}
    // Catch bad input
    else
    {
        std::ostringstream oss;
        oss << typeint << " does not correlate to a known particle type";
        throw std::invalid_argument(oss.str());
    }
}

double getcharge(const int typeint)
{
    double chargefactor = 1000;
    switch(static_cast<ParticleTypes>(typeint))
    {
        // Bosons
        case ParticleTypes::photon      : chargefactor = 0; break;
        case ParticleTypes::W_m         : chargefactor = -1; break;
        case ParticleTypes::W_p         : chargefactor = 1; break;
        case ParticleTypes::Z           : chargefactor = 0; break;
        case ParticleTypes::gluon       : chargefactor = 0; break;
        case ParticleTypes::higgs       : chargefactor = 0; break;

        // Leptons
        case ParticleTypes::e_m         : chargefactor = -1; break;
        case ParticleTypes::e_p         : chargefactor = 1; break;
        case ParticleTypes::mu_m        : chargefactor = -1; break;
        case ParticleTypes::mu_p        : chargefactor = 1; break;
        case ParticleTypes::tau_m       : chargefactor = -1; break;
        case ParticleTypes::tau_p       : chargefactor = 1; break;
        case ParticleTypes::nuE         : chargefactor = 0; break;
        case ParticleTypes::nuEbar      : chargefactor = 0; break;
        case ParticleTypes::nuU         : chargefactor = 0; break;
        case ParticleTypes::nuUbar      : chargefactor = 0; break;
        case ParticleTypes::nuT         : chargefactor = 0; break;
        case ParticleTypes::nuTbar      : chargefactor = 0; break;

        // Quarks
        case ParticleTypes::u           : chargefactor = 2/3; break;
        case ParticleTypes::ubar        : chargefactor = -2/3; break;
        case ParticleTypes::d           : chargefactor = -1/3; break;
        case ParticleTypes::dbar        : chargefactor = 1/3; break;
        case ParticleTypes::c           : chargefactor = 2/3; break;
        case ParticleTypes::cbar        : chargefactor = -2/3; break;
        case ParticleTypes::s           : chargefactor = -1/3; break;
        case ParticleTypes::sbar        : chargefactor = 1/3; break;
        case ParticleTypes::t           : chargefactor = 2/3; break;
        case ParticleTypes::tbar        : chargefactor = -2/3; break;
        case ParticleTypes::b           : chargefactor = -1/3; break;
        case ParticleTypes::bbar        : chargefactor = 1/3; break;

        // Pseudoscalar Mesons
        case ParticleTypes::pi_m        : chargefactor = -1; break;
        case ParticleTypes::pi_p        : chargefactor = 1; break;
        case ParticleTypes::pi0         : chargefactor = 0; break;
        case ParticleTypes::eta         : chargefactor = 0; break;
        case ParticleTypes::etaprime    : chargefactor = 0; break;
        case ParticleTypes::etac        : chargefactor = 0; break;
        case ParticleTypes::etab        : chargefactor = 0; break;
        case ParticleTypes::K_m         : chargefactor = -1; break;
        case ParticleTypes::K_p         : chargefactor = 1; break;
        case ParticleTypes::K0          : chargefactor = 0; break;
        case ParticleTypes::K0bar       : chargefactor = 0; break;
        case ParticleTypes::K0short     : chargefactor = 0; break;
        case ParticleTypes::K0long      : chargefactor = 0; break;
        case ParticleTypes::D_m         : chargefactor = -1; break;
        case ParticleTypes::D_p         : chargefactor = 1; break;
        case ParticleTypes::D0          : chargefactor = 0; break;
        case ParticleTypes::D0bar       : chargefactor = 0; break;
        case ParticleTypes::D_ms        : chargefactor = -1; break;
        case ParticleTypes::D_ps        : chargefactor = 1; break;
        case ParticleTypes::B_m         : chargefactor = -1; break;
        case ParticleTypes::B_p         : chargefactor = 1; break;
        case ParticleTypes::B0          : chargefactor = 0; break;
        case ParticleTypes::B0bar       : chargefactor = 0; break;
        case ParticleTypes::B0s         : chargefactor = 0; break;
        case ParticleTypes::B0sbar      : chargefactor = 0; break;
        case ParticleTypes::B_mc        : chargefactor = -1; break;
        case ParticleTypes::B_pc        : chargefactor = 1; break;

        // Vector Mesons
        case ParticleTypes::rho_m       : chargefactor = -1; break;
        case ParticleTypes::rho_p       : chargefactor = 1; break;
        case ParticleTypes::rho0        : chargefactor = 0; break;
        case ParticleTypes::omega       : chargefactor = 0; break;
        case ParticleTypes::phi         : chargefactor = 0; break;
        case ParticleTypes::Jpsi        : chargefactor = 0; break;
        case ParticleTypes::upsilon     : chargefactor = 0; break;
        case ParticleTypes::vK_m        : chargefactor = -1; break;
        case ParticleTypes::vK_p        : chargefactor = 1; break;
        case ParticleTypes::vK0         : chargefactor = 0; break;
        case ParticleTypes::vK0bar      : chargefactor = 0; break;
        case ParticleTypes::vD_m        : chargefactor = -1; break;
        case ParticleTypes::vD_p        : chargefactor = 1; break;
        case ParticleTypes::vD0         : chargefactor = 0; break;
        case ParticleTypes::vD0bar      : chargefactor = 0; break;
        case ParticleTypes::vD_ms       : chargefactor = -1; break;
        case ParticleTypes::vD_ps       : chargefactor = 1; break;
        case ParticleTypes::vB_m        : chargefactor = -1; break;
        case ParticleTypes::vB_p        : chargefactor = 1; break;
        case ParticleTypes::vB0         : chargefactor = 0; break;
        case ParticleTypes::vB0bar      : chargefactor = 0; break;
        case ParticleTypes::vB0s        : chargefactor = 0; break;
        case ParticleTypes::vB0sbar     : chargefactor = 0; break;
        case ParticleTypes::vB_mc       : chargefactor = -1; break;
        case ParticleTypes::vB_pc       : chargefactor = 1; break;

        // J = +/- 1/2 Baryons
        case ParticleTypes::proton          : chargefactor = 1; break;
        case ParticleTypes::neutron         : chargefactor = 0; break;
        case ParticleTypes::lambda          : chargefactor = 0; break;
        case ParticleTypes::lambdac         : chargefactor = 1; break;
        case ParticleTypes::lambdab         : chargefactor = 0; break;
        case ParticleTypes::sigma_p         : chargefactor = 1; break;
        case ParticleTypes::sigma0          : chargefactor = 0; break;
        case ParticleTypes::sigma_m         : chargefactor = -1; break;
        case ParticleTypes::sigma_ppc       : chargefactor = 2; break;
        case ParticleTypes::sigma_pc        : chargefactor = 1; break;
        case ParticleTypes::sigma0c         : chargefactor = 0; break;
        case ParticleTypes::sigma_pb        : chargefactor = 1; break;
        case ParticleTypes::sigma0b         : chargefactor = 0; break;
        case ParticleTypes::sigma_mb        : chargefactor = -1; break;
        case ParticleTypes::xi0             : chargefactor = 0; break;
        case ParticleTypes::xi_m            : chargefactor = -1; break;
        case ParticleTypes::xi_pc           : chargefactor = 1; break;
        case ParticleTypes::xi0c            : chargefactor = 0; break;
        case ParticleTypes::xi_pcprime      : chargefactor = 1; break;
        case ParticleTypes::xi0cprime       : chargefactor = 0; break;
        case ParticleTypes::xi_ppcc         : chargefactor = 2; break;
        case ParticleTypes::xi_pcc          : chargefactor = 1; break;
        case ParticleTypes::xi0b            : chargefactor = 0; break;
        case ParticleTypes::xi_mb           : chargefactor = -1; break;
        case ParticleTypes::xi0bprime       : chargefactor = 0; break;
        case ParticleTypes::xi_mbprime      : chargefactor = -1; break;
        case ParticleTypes::xi0bb           : chargefactor = 0; break;
        case ParticleTypes::xi_mbb          : chargefactor = -1; break;
        case ParticleTypes::xi_pcb          : chargefactor = 1; break;
        case ParticleTypes::xi0cb           : chargefactor = 0; break;
        case ParticleTypes::xi_pcbprime     : chargefactor = 1; break;
        case ParticleTypes::xi0cbprime      : chargefactor = 0; break;
        case ParticleTypes::omega0c         : chargefactor = 0; break;
        case ParticleTypes::omega_mb        : chargefactor = -1; break;
        case ParticleTypes::omega_pcc       : chargefactor = 1; break;
        case ParticleTypes::omega0cb        : chargefactor = 0; break;
        case ParticleTypes::omega0cbprime   : chargefactor = 0; break;
        case ParticleTypes::omega_mbb       : chargefactor = -1; break;
        case ParticleTypes::omega_pccb      : chargefactor = 1; break;
        case ParticleTypes::omega0cbb       : chargefactor = 0; break;

        // J = +/- 3/2 Baryons
        case ParticleTypes::delta_pp        : chargefactor = 2; break;
        case ParticleTypes::delta_p         : chargefactor = 1; break;
        case ParticleTypes::delta0          : chargefactor = 0; break;
        case ParticleTypes::delta_m         : chargefactor = -1; break;
        case ParticleTypes::sigma3_p        : chargefactor = 1; break;
        case ParticleTypes::sigma30         : chargefactor = 0; break;
        case ParticleTypes::sigma3_m        : chargefactor = -1; break;
        case ParticleTypes::sigma3_ppc      : chargefactor = 2; break;
        case ParticleTypes::sigma3_pc       : chargefactor = 1; break;
        case ParticleTypes::sigma30c        : chargefactor = 0; break;
        case ParticleTypes::sigma3_pb       : chargefactor = 1; break;
        case ParticleTypes::sigma30b        : chargefactor = 0; break;
        case ParticleTypes::sigma3_mb       : chargefactor = -1; break;
        case ParticleTypes::xi30            : chargefactor = 0; break;
        case ParticleTypes::xi3_m           : chargefactor = -1; break;
        case ParticleTypes::xi3_pc          : chargefactor = 1; break;
        case ParticleTypes::xi30c           : chargefactor = 0; break;
        case ParticleTypes::xi3_ppcc        : chargefactor = 2; break;
        case ParticleTypes::xi3_pcc         : chargefactor = 1; break;
        case ParticleTypes::xi30b           : chargefactor = 0; break;
        case ParticleTypes::xi3_mb          : chargefactor = -1; break;
        case ParticleTypes::xi30bb          : chargefactor = 0; break;
        case ParticleTypes::xi3_mbb         : chargefactor = -1; break;
        case ParticleTypes::xi3_pcb         : chargefactor = 1; break;
        case ParticleTypes::xi30cb          : chargefactor = 0; break;
        case ParticleTypes::omega_m         : chargefactor = -1; break;
        case ParticleTypes::omega30c        : chargefactor = 0; break;
        case ParticleTypes::omega3_mb       : chargefactor = -1; break;
        case ParticleTypes::omega3_pcc      : chargefactor = 1; break;
        case ParticleTypes::omega30cb       : chargefactor = 0; break;
        case ParticleTypes::omega3_mbb      : chargefactor = -1; break;
        case ParticleTypes::omega_ppccc     : chargefactor = 2; break;
        case ParticleTypes::omega3_pccb     : chargefactor = 1; break;
        case ParticleTypes::omega30cbb      : chargefactor = 0; break;
        case ParticleTypes::omega_mbbb      : chargefactor = -1; break;

        // Nuclei
        case ParticleTypes::h1n     : chargefactor = 1; break;
        case ParticleTypes::h2n     : chargefactor = 1; break;
        case ParticleTypes::h3n     : chargefactor = 1; break;
        case ParticleTypes::he3n    : chargefactor = 2; break;
        case ParticleTypes::he4n    : chargefactor = 2; break;
        case ParticleTypes::li6n    : chargefactor = 3; break;
        case ParticleTypes::li7n    : chargefactor = 3; break;
        case ParticleTypes::be9n    : chargefactor = 4; break;
        case ParticleTypes::b10n    : chargefactor = 5; break;
        case ParticleTypes::b11n    : chargefactor = 5; break;
        case ParticleTypes::c12n    : chargefactor = 6; break;
        case ParticleTypes::c13n    : chargefactor = 6; break;
        case ParticleTypes::c14n    : chargefactor = 6; break;
        case ParticleTypes::n14n    : chargefactor = 7; break;
        case ParticleTypes::n15n    : chargefactor = 7; break;
        case ParticleTypes::o16n    : chargefactor = 8; break;
        case ParticleTypes::o17n    : chargefactor = 8; break;
        case ParticleTypes::o18n    : chargefactor = 8; break;
        case ParticleTypes::f19n    : chargefactor = 9; break;
        case ParticleTypes::ne20n   : chargefactor = 10; break;
        case ParticleTypes::ne21n   : chargefactor = 10; break;
        case ParticleTypes::ne22n   : chargefactor = 10; break;
        case ParticleTypes::na23n   : chargefactor = 11; break;
        case ParticleTypes::mg24n   : chargefactor = 12; break;
        case ParticleTypes::mg25n   : chargefactor = 12; break;
        case ParticleTypes::mg26n   : chargefactor = 12; break;
        case ParticleTypes::al27n   : chargefactor = 13; break;
        case ParticleTypes::si28n   : chargefactor = 14; break;
        case ParticleTypes::si29n   : chargefactor = 14; break;
        case ParticleTypes::si30n   : chargefactor = 14; break;
        case ParticleTypes::p31n    : chargefactor = 15; break;
        case ParticleTypes::s32n    : chargefactor = 16; break;
        case ParticleTypes::s33n    : chargefactor = 16; break;
        case ParticleTypes::s34n    : chargefactor = 16; break;
        case ParticleTypes::s36n    : chargefactor = 16; break;
        case ParticleTypes::cl35n   : chargefactor = 17; break;
        case ParticleTypes::cl37n   : chargefactor = 17; break;
        case ParticleTypes::ar36n   : chargefactor = 18; break;
        case ParticleTypes::ar38n   : chargefactor = 18; break;
        case ParticleTypes::ar40n   : chargefactor = 18; break;
        case ParticleTypes::k39n    : chargefactor = 19; break;
        case ParticleTypes::k40n    : chargefactor = 19; break;
        case ParticleTypes::k41n    : chargefactor = 19; break;
        case ParticleTypes::ca40n   : chargefactor = 20; break;
        case ParticleTypes::ca42n   : chargefactor = 20; break;
        case ParticleTypes::ca43n   : chargefactor = 20; break;
        case ParticleTypes::ca44n   : chargefactor = 20; break;
        case ParticleTypes::ca46n   : chargefactor = 20; break;
        case ParticleTypes::ca48n   : chargefactor = 20; break;
        case ParticleTypes::sc45n   : chargefactor = 21; break;
        case ParticleTypes::ti46n   : chargefactor = 22; break;
        case ParticleTypes::ti47n   : chargefactor = 22; break;
        case ParticleTypes::ti48n   : chargefactor = 22; break;
        case ParticleTypes::ti49n   : chargefactor = 22; break;
        case ParticleTypes::ti50n   : chargefactor = 22; break;
        case ParticleTypes::v50n    : chargefactor = 23; break;
        case ParticleTypes::v51n    : chargefactor = 23; break;
        case ParticleTypes::cr50n   : chargefactor = 24; break;
        case ParticleTypes::cr52n   : chargefactor = 24; break;
        case ParticleTypes::cr53n   : chargefactor = 24; break;
        case ParticleTypes::cr54n   : chargefactor = 24; break;
        case ParticleTypes::mn55n   : chargefactor = 25; break;
        case ParticleTypes::fe54n   : chargefactor = 26; break;
        case ParticleTypes::fe56n   : chargefactor = 26; break;
        case ParticleTypes::fe57n   : chargefactor = 26; break;
        case ParticleTypes::fe58n   : chargefactor = 26; break;
    }

    // Convert to coulombs
    if (chargefactor!=1000) {return chargefactor * qe;}
    // Catch bad input
    else
    {
        std::ostringstream oss;
        oss << typeint << " does not correlate to a known particle type";
        throw std::invalid_argument(oss.str());
    }
}
