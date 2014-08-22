// Reaktor is a C++ library for computational reaction modelling.
//
// Copyright (C) 2014 Allan Leal
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program. If not, see <http://www.gnu.org/licenses/>.

#include "ReactionUtils.hpp"

// Reaktor includes
#include <Reaktor/Common/Constants.hpp>
#include <Reaktor/Common/ScalarResult.hpp>
#include <Reaktor/Common/VectorResult.hpp>
#include <Reaktor/Core/Multiphase.hpp>
#include <Reaktor/Core/Reaction.hpp>
#include <Reaktor/Core/Species.hpp>

namespace Reaktor {

auto numSpecies(const Reaction& reaction) -> unsigned
{
	return reaction.species().size();
}

auto containsSpecies(const Reaction& reaction, const std::string& species) -> bool
{
	return indexSpecies(reaction, species) < numSpecies(reaction);
}

auto indexSpecies(const Reaction& reaction, const std::string& species) -> Index
{
	const auto& begin = reaction.species().begin();
	const auto& end = reaction.species().end();
	return std::find(begin, end, species) - begin;
}

auto stoichiometry(const Reaction& reaction, const std::string& species) -> double
{
	const Index index = indexSpecies(reaction, species);
	return index < numSpecies(reaction) ? reaction.stoichiometries()[index] : 0.0;
}

auto equilibriumConstant(const Multiphase& multiphase, const Reaction& reaction) -> EquilibriumConstant
{
	// The species in the chemical system
    const std::vector<Species>& species = multiphase.species();

    // The stoichiometries of the reacting species
    const std::vector<double> stoichiometries = reaction.stoichiometries();

    // The number of participating species in the reaction
    const unsigned num_species = numSpecies(reaction);

    // The universal gas constant (in units of J/(mol*K))
    const double R = universalGasConstant;

    // Collect the chemical potential functions of the reacting species
    std::vector<ChemicalPotential> mu;
    for(Index i : reaction.indices())
        mu.push_back(species[i].chemicalPotential());

    // Define the equilibrium constant function
    EquilibriumConstant kappa = [=](double T, double P)
    {
        double sum = 0.0;
        for(unsigned i = 0; i < num_species; ++i)
            sum += stoichiometries[i] * mu[i](T, P);
        return std::exp(-sum/(R*T));
    };

    return kappa;
}

auto equilibriumConstant(const Reaction& reaction, double T, double P) -> double
{
	return reaction.equilibriumConstant()(T, P);
}

auto rate(const Reaction& reaction, double T, double P, const Vector& n, const VectorResult& a) -> ScalarResult
{
	return reaction.rate()(T, P, n, a);
}

auto reactionQuotient(const Reaction& reaction, const VectorResult& a) -> ScalarResult
{
	const unsigned size = a.val.size();

	ScalarResult Q(1.0, zeros(size));

	const auto& stoichiometries = reaction.stoichiometries();
	const auto& indices = reaction.indices();

	for(unsigned i = 0; i < numSpecies(reaction); ++i)
	{
		const double vi = stoichiometries[i];
		const double ai = a.val[indices[i]];
		Q.val *= std::pow(ai, vi);
	}

	for(unsigned i = 0; i < numSpecies(reaction); ++i)
	{
		const double vi = stoichiometries[i];
		const double ai = a.val[indices[i]];
		Q.grad += Q.val * vi/ai * a.grad.row(indices[i]);
	}

	return Q;
}

} /* namespace Reaktor */
