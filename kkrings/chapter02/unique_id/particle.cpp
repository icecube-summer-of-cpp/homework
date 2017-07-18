#include <cassert>
#include <cmath>
#include <map>

#include "particle.hpp"

namespace
{
    std::map<particle_type, properties> properties_map = {
        {particle_type::unknown, {0., 0., 0}},
        {particle_type::photon, {0., 0., 2}},
        {particle_type::electron, {511e3, -1., 1}},
        {particle_type::muon, {105e6, -1., 1}},
        {particle_type::tau, {1776e6, -1., 1}},
        {particle_type::nue, {0., 0., 1}},
        {particle_type::numu, {0., 0., 1}},
        {particle_type::nutau, {0., 0., 1}}
    };
};

particle_properties::particle_properties(particle_type type)
    : type_(type), properties_(properties_map.at(type))
{}

void particle::set_momentum(particle::vector4 v)
{
    double norm = v[1]*v[1] + v[2]*v[2] + v[3]*v[3] - v[0]*v[0];
    double mass = properties_.mass();
    assert(!(std::abs(mass*mass - norm) > 0.));
    momentum_ = v;
}

void particle::set_position(particle::vector4 v)
{
    if (!(properties_.mass() > 0.))
    {
        double norm = v[1]*v[1] + v[2]*v[2] + v[3]*v[3] - v[0]*v[0];
        assert(std::abs(norm) > 0.);
    }

    position_ = v;
}
