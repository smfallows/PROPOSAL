#include "PROPOSAL/Secondaries.h"
#include "PROPOSAL/particle/Particle.h"
#include "PROPOSAL/math/Vector3D.h"
#include "PROPOSAL/decay/DecayChannel.h"

#include <memory>
#include <vector>
#include <iostream>

using namespace PROPOSAL;

Secondaries::Secondaries() : primary_def_(nullptr) {}

Secondaries::Secondaries(std::shared_ptr<ParticleDef> p_def) {
    primary_def_ = p_def;
}

void Secondaries::reserve(size_t number_secondaries) {
    secondaries_.reserve(number_secondaries);
}

void Secondaries::push_back(const DynamicData& continuous_loss)
{
    secondaries_.push_back(continuous_loss);
}


void Secondaries::emplace_back(const int& type,const  Vector3D& position,
        const Vector3D& direction, const double& energy, const double& parent_particle_energy,
        const double& time, const double& distance)
{
    secondaries_.emplace_back(type, position, direction, energy, parent_particle_energy, time, distance);
}
void Secondaries::emplace_back(const int& type)
{
    secondaries_.emplace_back(type);
}

void Secondaries::push_back(const Particle& particle, const int& interaction_type, const double& energy_loss)
{
    DynamicData data(interaction_type);

    data.SetEnergy(energy_loss);
    data.SetPosition(particle.GetPosition());
    data.SetDirection(particle.GetDirection());
    data.SetTime(particle.GetTime());
    data.SetParentParticleEnergy(particle.GetEnergy());
    data.SetPropagatedDistance(particle.GetPropagatedDistance());

    secondaries_.push_back(data);
}

void Secondaries::append(Secondaries secondaries)
{
    secondaries_.insert(secondaries_.end(), secondaries.secondaries_.begin(), secondaries.secondaries_.end());
}

Secondaries Secondaries::Query(const int& interaction_type) const
{
    Secondaries sec;
    for (auto i : secondaries_) {
        if (interaction_type == i.GetTypeId())
            sec.push_back(i);
    }
    return sec;
}

Secondaries Secondaries::Query(const std::string& interaction_type) const
{
    Secondaries sec;
    for (auto i : secondaries_) {
        if (interaction_type == i.GetName())
            sec.push_back(i);
    }
    return sec;
}

Secondaries Secondaries::Query(const Geometry& geometry) const
{
    Secondaries sec;
    for (auto i : secondaries_) {
        if (geometry.IsInside(i.GetPosition(), i.GetDirection()))
            sec.push_back(i);
    }
    return sec;
}

void Secondaries::DoDecay()
{
    for (auto it = secondaries_.begin(); it != secondaries_.end(); ) {
        if (it->GetTypeId() == static_cast<int>(InteractionType::Decay)){
            Secondaries products = primary_def_->decay_table.SelectChannel().Decay(*primary_def_, *it);
            it = secondaries_.erase(it); // delete old decay
            for (auto p : products.GetSecondaries()) {
                it = secondaries_.insert(it, p); // and insert decayparticles inplace of old decay
                it++;
            }
        } else { it++; }
    }
}

std::vector<Vector3D> Secondaries::GetPosition() const
{
    std::vector<Vector3D> vec;
    for (auto i : secondaries_) vec.emplace_back(i.GetPosition());
    return vec;
}

std::vector<Vector3D> Secondaries::GetDirection() const
{
    std::vector<Vector3D> vec;
    for (auto i : secondaries_) vec.emplace_back(i.GetDirection());
    return vec;
}

std::vector<double> Secondaries::GetEnergy() const
{
    std::vector<double> vec;
    for (auto i : secondaries_) vec.emplace_back(i.GetEnergy());
    return vec;
}

std::vector<double> Secondaries::GetParentParticleEnergy() const
{
    std::vector<double> vec;
    for (auto i : secondaries_) vec.emplace_back(i.GetParentParticleEnergy());
    return vec;
}

std::vector<double> Secondaries::GetTime() const
{
    std::vector<double> vec;
    for (auto i : secondaries_) vec.emplace_back(i.GetTime());
    return vec;
}

std::vector<double> Secondaries::GetPropagatedDistance() const
{
    std::vector<double> vec;
    for (auto i : secondaries_) vec.emplace_back(i.GetPropagatedDistance());
    return vec;
}