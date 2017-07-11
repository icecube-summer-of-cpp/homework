#include <iostream>
#include <math.h>
#include "vectors.hpp"
#include "particle.hpp"


void print_info(const Particle& p)
{
    std::cout << "Particle: " << p << std::endl;
    std::cout << "  Rest mass: " << p.restmass() << " kg" << std::endl;
    std::cout << "  Charge:    " << p.charge() << " C" << std::endl;
    std::cout << "  Position:  " << p.position() << " m" << std::endl;
    std::cout << "  Distance:  " << mag(p.position()) << " m" << std::endl;
    std::cout << "  Momentum:  " << p.momentum() << " kg m/s" << std::endl;
    std::cout << "  Energy:    " << p.energy() << " J" << std::endl;
    std::cout << "  Kinetic:   " << p.kinetic() << " J" << std::endl;
    std::cout << "  Direction: " << p.direction() << std::endl << std::endl;
}

int main()
{
    std::cout << "========== Testing Cartesian Vectors ==========" << std::endl;
    UnitVector v_i(1,0,0), v_j(0,1,0), v_k(0,0,1);
    std::cout << "i = " << v_i << std::endl;
    std::cout << "j = " << v_j << std::endl;
    std::cout << "k = " << v_k << std::endl;
    std::cout << "i x j = " << cross(v_i,v_j) << std::endl;
    std::cout << "j x k = " << cross(v_j,v_k) << std::endl;
    std::cout << "k x i = " << cross(v_k,v_i) << std::endl;

    CartesianVector a(5,5,5);
    std::cout << "a = " << a << std::endl;
    std::cout << "a • i = " << dot(a,v_i) << std::endl;
    std::cout << "a • j = " << dot(a,v_j) << std::endl;
    std::cout << "a • k = " << dot(a,v_k) << std::endl;
    std::cout << "a x i = " << cross(a,v_i) << std::endl;
    std::cout << "a x j = " << cross(a,v_j) << std::endl;
    std::cout << "a x k = " << cross(a,v_k) << std::endl;
    CartesianVector b(1,2,3);
    std::cout << "b = " << b << std::endl;
    std::cout << "a + b = " << a+b << std::endl;
    std::cout << "a - b = " << a-b << std::endl;
    std::cout << "2a = " << a*2 << " = " << 2*a << std::endl;


    std::cout << "\n========== Testing Four-Vectors ==========" << std::endl;
    FourVector p;
    std::cout << "p = " << p << std::endl;
    for (int i=0; i<4; ++i) {p[i]=i+1;}
    std::cout << "p = " << p << std::endl;
    FourVector q(0,1,2,3);
    std::cout << "q = " << q << std::endl;
    std::cout << "p + q = " << p+q << std::endl;
    std::cout << "p - q = " << p-q << std::endl;
    std::cout << "2p = " << p*2 << " = " << 2*p << std::endl;


    std::cout << "\n========== Testing Particles ==========" << std::endl;
    Particle electron("electron");
    print_info(electron);

    Particle electron2(electron.name());
    electron2.set_position(10,10,10);
    print_info(electron2);

    Particle electron3(electron.type());
    UnitVector vec(1,1,0);
    electron3.set_position(vec);
    print_info(electron3);

    Particle proton("proton");
    CartesianVector momentum(0,0,1e-18);
    proton.set_momentum(momentum);
    print_info(proton);
    std::cout << "  Rest mass: " <<
    sqrt(dot(proton.momentum(),proton.momentum())/c_0/c_0) << " kg" << std::endl << std::endl;

    proton.set_momentum(CartesianVector(0,0,0));
    proton.set_energy(1.6e-10);
    print_info(proton);

    proton.set_direction(UnitVector(1,0,0));
    print_info(proton);

    proton.set_energy(proton.restmass()*c_0*c_0);
    print_info(proton);

    proton.set_kinetic(0);
    print_info(proton);

    proton.set_energy(0);
    print_info(proton);

    return 0;
}