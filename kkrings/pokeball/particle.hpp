#ifndef POKEBALL_PARTICLE_HPP
#define POKEBALL_PARTICLE_HPP

#include <array>

#include "unique_id.hpp"

/**
 * @brief Particle properties
 *
 * Define the properties of new particle types; supports non-integer
 * charges for defining BSM particles.
 */
struct properties
{
    double mass; /**< Particle mass in units of eV */
    double charge; /**< Particle charge in units of e */
    unsigned int spin; /**< Particle spin times 2 */
};

enum class particle_type {
    unknown,
    photon,
    electron,
    muon,
    tau,
    nue,
    numu,
    nutau
};

/**
 * @brief Particle properties access
 *
 * This class gives access to the properties of a particle object of a
 * certain type.
 */
class particle_properties
{
    public:
        /**
         * Construct properties of particle of a certain type.
         * @param type Particle type
         */
        particle_properties(particle_type type);

        /**
         * Construct properties of particle of type unknown.
         */
        particle_properties() : particle_properties(particle_type::unknown) {}

        particle_properties(const particle_properties&) = default;
        particle_properties(particle_properties&&) = default;

        ~particle_properties() = default;

        particle_properties& operator=(const particle_properties&) = default;
        particle_properties& operator=(particle_properties&&) = default;

        /**
         * @return Particle type
         */
        particle_type type() const {return type_;}

        /**
         * @return Particle mass in units of eV
         */
        double mass() const {return properties_.mass;}

        /**
         * @return Particle charge in units of e
         */
        int charge() const {return properties_.charge;}

        /**
         * @return Particle spin
         */
        double spin() const {return 0.5 * properties_.spin;}

    private:
        particle_type type_;
        properties properties_;
};

/**
 * @brief Particle class
 *
 * This class represents a free particle, holding its four-momentum and
 * four-position vectors, and its properties (type, mass, charge, spin).
 */
class particle
{
    using vector4 = std::array<double, 4>;

    public:
        /**
         * Construct a particle of a certain type.
         * @param type Particle type
         */
        explicit particle(particle_type type) : properties_(type) {}

        particle() = default;
        particle(const particle&) = default;
        particle(particle&&) = default;

        virtual ~particle() = default;

        particle& operator=(const particle&) = default;
        particle& operator=(particle&&) = default;

        /**
         * A particle object only compares equally to copies of itsself.
         */
        bool operator==(const particle& other) const
        {
            return other.id() == id_;
        }

        bool operator!=(const particle& other) const
        {
            return other.id() != id_;
        }

        /**
         * @return Particle's ID
         */
        unique_id id() const {return id_;}

        /**
         * @return Particle's properties: type, mass, ...
         */
        const particle_properties& properties() const {return properties_;}

        /**
         * @return Particle's four-momentum vector
         */
        vector4 get_momentum() const {return momentum_;}

        /**
         * @return Particle's four-position vector
         */
        vector4 get_position() const {return position_;}

        void set_momentum(vector4);
        void set_position(vector4);

    private:
        unique_id id_;
        vector4 momentum_;
        vector4 position_;
        particle_properties properties_;
};

#endif
