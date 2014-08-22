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

#pragma once

// C++ includes
#include <vector>
#include <string>

// Reaktor includes
#include <Reaktor/Common/Index.hpp>
#include <Reaktor/Core/Functions.hpp>

namespace Reaktor {

// Forward declarations
class ScalarResult;
class VectorResult;
class Multiphase;
class Reaction;

/// Get the number of species in a reaction
/// @param reaction The reaction instance
auto numSpecies(const Reaction& reaction) -> unsigned;

/// Check if a reaction contains a species
/// @param reaction The reaction instance
/// @param species The name of the species
auto containsSpecies(const Reaction& reaction, const std::string& species) -> bool;

/// Get the index of a species in a reaction
/// @param reaction The reaction instance
/// @param species The name of the species
auto indexSpecies(const Reaction& reaction, const std::string& species) -> Index;

/// Get the stoichiometry of a species in a reaction
/// @param reaction The reaction instance
/// @param species The name of the species
/// @return The stoichiometry of the species if it participates
/// in the reaction, or zero otherwise.
auto stoichiometry(const Reaction& reaction, const std::string& species) -> double;

/// Create an equilibrium constant function for a reaction
///
/// The created function will use the chemical potential functions of the
/// reacting species to calculate the equilibrium constant of the reaction.
///
/// @param multiphase The multiphase system
/// @param reaction The reaction instance
auto equilibriumConstant(const Multiphase& multiphase, const Reaction& reaction) -> EquilibriumConstant;

/// Calculate the equilibrium constant of a reaction
/// @param reaction The reaction instance
/// @param T The temperature of the chemical system (in units of K)
/// @param P The pressure of the chemical system (in units of Pa)
auto equilibriumConstant(const Reaction& reaction, double T, double P) -> double;

/// Calculate the kinetic rate of the reaction
/// @param reaction The reaction instance
/// @param T The temperature of the chemical system (in units of K)
/// @param P The pressure of the chemical system (in units of Pa)
/// @param n The molar abundance of the species in the chemical system (in units of mol)
/// @param a The activities of every species in the chemical system and their molar derivatives
/// @return The rate of the reaction and its molar derivatives
auto rate(const Reaction& reaction, double T, double P, const Vector& n, const VectorResult& a) -> ScalarResult;

/// Calculate the reaction quotient of the reaction
///
/// The reaction quotient @f$ Q @f$ of a reaction is defined as:
/// @f[
///     Q=\prod_{i=1}^{N}a_{i}^{\nu_{i}},
/// @f]
/// where @f$ N @f$ denotes the number of species in the chemical system,
/// @f$ a_{i} @f$ the activity of the @f$ i @f$-th species, and
/// @f$ \nu_{i} @f$ the stoichiometry of the @f$ i @f$-th species in the
/// reaction:
/// @f[
///     0\rightleftharpoons\sum_{i=1}^{N}\nu_{i}\alpha_{i},
/// @f]
/// with @f$ \alpha_{i} @f$ denoting the @f$ i @f$-th species. The sign
/// convention for the stoichiometric coefficients is: *positive* for
/// products, *negative* for reactants.
///
/// @param reaction The reaction instance
/// @param a The activities of every species in the chemical system and their molar derivatives
auto reactionQuotient(const Reaction& reaction, const VectorResult& a) -> ScalarResult;

} /* namespace Reaktor */
